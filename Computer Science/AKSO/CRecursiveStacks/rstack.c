#include "rstack.h"
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>
#include <ctype.h>

// typy i struktury uzyte w rozwiazaniu
typedef enum {
    ELEM_VALUE,
    ELEM_RSTACK
} elem_type_t;

typedef struct {
    elem_type_t type;
    union {
        uint64_t value;
        struct rstack *rs;
    } data;
} elem_t;

struct rstack {
    size_t ref_count; // calkowita liczba referencji
    size_t internal_count; // referencje z wewnatrz innych stosow
    size_t capacity; // pojemnosc
    size_t size; // rozmiar
    elem_t *elements; // tablica elementow

    bool marked; // flaga dla garbage collector
    bool writing_in_progress; // flaga O(1) do cykli przy zapisie
    uint64_t visit_mark; // czy odwiedzony (funkcje przeszukujace)

    struct rstack *gc_next; // lista robocza dla O(N) gc
    struct rstack *prev; // wskazniki przod tyl na globalnej liscie
    struct rstack *next;
};

static rstack_t *global_stacks = nullptr;
static uint64_t current_visit_mark = 0;

// garbage collector - mark and sweep w czasie O(N)
static void run_garbage_collection(void) {
    rstack_t *curr = global_stacks;
    rstack_t *worklist = nullptr;

    // 1. odznacz wszystkie i znajdz korzenie
    while (curr) {
        curr->marked = false;
        if (curr->ref_count > curr->internal_count) {
            curr->marked = true;
            curr->gc_next = worklist;
            worklist = curr;
        }
        curr = curr->next;
    }

    // 2. liniowe przejscie grafu (zamiast O(N^2))
    while (worklist) {
        rstack_t *node = worklist;
        worklist = node->gc_next;

        for (size_t i = 0; i < node->size; i++) {
            if (node->elements[i].type == ELEM_RSTACK) {
                rstack_t *child = node->elements[i].data.rs;
                if (!child->marked) {
                    child->marked = true;
                    child->gc_next = worklist;
                    worklist = child;
                }
            }
        }
    }

    // 3. usuwanie referencji z martwych stosow
    curr = global_stacks;
    while (curr) {
        if (!curr->marked) {
            for (size_t i = 0; i < curr->size; i++) {
                if (curr->elements[i].type == ELEM_RSTACK) {
                    curr->elements[i].data.rs->ref_count--;
                    curr->elements[i].data.rs->internal_count--;
                }
            }
        }
        curr = curr->next;
    }

    // 4. usuwanie martwych z pamieci
    curr = global_stacks;
    rstack_t *prev = nullptr;
    while (curr) {
        if (!curr->marked) {
            rstack_t *to_del = curr;
            if (prev) {
                prev->next = curr->next;
                if (curr->next) curr->next->prev = prev;
                curr = curr->next;
            } else {
                global_stacks = curr->next;
                if (global_stacks) global_stacks->prev = nullptr;
                curr = global_stacks;
            }
            free(to_del->elements);
            free(to_del);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
}


// funkcje dla stosow
// tworzy nowy pusty stos i wrzuca go na liste
rstack_t* rstack_new(void) {
    rstack_t* rs = malloc(sizeof(rstack_t));
    if (rs == nullptr) {
        errno = ENOMEM;
        return nullptr;
    }
    rs->ref_count = 1;
    rs->internal_count = 0;
    rs->size = 0;
    rs->capacity = 0;
    rs->elements = nullptr;

    rs->marked = false;
    rs->writing_in_progress = false;
    rs->visit_mark = 0;
    rs->gc_next = nullptr;

    rs->prev = nullptr;
    rs->next = global_stacks;
    if (global_stacks) global_stacks->prev = rs;
    global_stacks = rs;
    return rs;
}

// zmniejsza licznik referencji stosu
void rstack_delete(rstack_t* rs) {
    if (rs == nullptr) return;
    rs->ref_count--;
    run_garbage_collection();
}

// podwaja tablice elementow w razie potrzeby
static int ensure_capacity(rstack_t* rs) {
    if (rs->capacity > rs->size) return 0;
    size_t new_capacity = (rs->capacity == 0) ? 4 : 2 * rs->capacity;
    elem_t *new_elements = reallocarray(rs->elements, new_capacity,
                                        sizeof(elem_t));
    if (new_elements == nullptr) {
        errno = ENOMEM;
        return -1;
    }
    rs->elements = new_elements;
    rs->capacity = new_capacity;
    return 0;
}

// wrzuca zwykla liczbe na stos
int rstack_push_value(rstack_t* rs, uint64_t value) {
    if (rs == nullptr) { errno = EINVAL; return -1; }
    if (ensure_capacity(rs) == -1) return -1;
    rs->elements[rs->size].data.value = value;
    rs->elements[rs->size].type = ELEM_VALUE;
    rs->size++;
    return 0;
}

// wrzuca wewnetrzny stos na stos i uaktualnia refy
int rstack_push_rstack(rstack_t* rs, rstack_t* other) {
    if (rs == nullptr || other == nullptr) {
        errno = EINVAL;
        return -1;
    }
    if (ensure_capacity(rs) == -1) return -1;
    rs->elements[rs->size].data.rs = other;
    rs->elements[rs->size].type = ELEM_RSTACK;
    rs->size++;
    other->ref_count++;
    other->internal_count++;
    return 0;
}

// zdejmuje z wierzcholka
void rstack_pop(rstack_t* rs) {
    if (rs == nullptr || rs->size == 0) return;
    elem_t top_elem = rs->elements[rs->size - 1];
    rs->size--;
    if (top_elem.type == ELEM_RSTACK) {
        top_elem.data.rs->ref_count--;
        top_elem.data.rs->internal_count--;
        run_garbage_collection();
    }
}


// rstack empty
// sprawdza rekurencyjnie zawartosc galezi omijajac cykle
static bool rstack_empty_recursive(rstack_t* rs, uint64_t mark) {
    if (rs == nullptr || rs->size == 0) return true;
    if (rs->visit_mark == mark) return true;
    rs->visit_mark = mark;
    for (size_t i = 0; i < rs->size; i++) {
        if (rs->elements[i].type == ELEM_RSTACK) {
            if (!rstack_empty_recursive(rs->elements[i].data.rs, mark)) {
                return false;
            }
        }
        else if (rs->elements[i].type == ELEM_VALUE) return false;
    }
    return true;
}

// zewnetrzny interfejs rstack_empty
bool rstack_empty(rstack_t* rs) {
    if (rs == nullptr) return true;
    current_visit_mark++;
    return rstack_empty_recursive(rs, current_visit_mark);
}

// rstack front
// szuka z wierzcholka w glab uzywajac rekurencji
static bool rstack_front_recursive(rstack_t *rs, uint64_t mark,
                                   uint64_t *found_value) {
    if (rs == nullptr || rs->size == 0) return false;
    if (rs->visit_mark == mark) return false;
    rs->visit_mark = mark;
    for (size_t i = rs->size; i > 0; i--) {
        elem_t *elem = &rs->elements[i - 1];
        if (elem->type == ELEM_VALUE) {
            *found_value = elem->data.value;
            return true;
        }
        else if (elem->type == ELEM_RSTACK) {
            if (rstack_front_recursive(elem->data.rs, mark, found_value)) {
                return true;
            }
        }
    }
    return false;
}

// zewnetrzny interfejs rstack_front
result_t rstack_front(rstack_t *rs) {
    result_t result = { .flag = false, .value = 0 };
    if (rs == nullptr) return result;
    current_visit_mark++;
    if (rstack_front_recursive(rs, current_visit_mark, &result.value)) {
        result.flag = true;
    }
    return result;
}

// read & write z plikami
// wnetrze write z szybka flaga do ciec
static bool rstack_write_recursive(rstack_t *rs, FILE *file) {
    if (rs == nullptr || rs->size == 0) return false;
    if (rs->writing_in_progress) return true; // uciecie cyklu

    rs->writing_in_progress = true;

    for (size_t i = 0; i < rs->size; i++) {
        elem_t *elem = &rs->elements[i];
        if (elem->type == ELEM_VALUE) {
            if (fprintf(file, "%" PRIu64 "\n", elem->data.value) < 0) {
                rs->writing_in_progress = false;
                return true;
            }
        } else if (elem->type == ELEM_RSTACK) {
            if (rstack_write_recursive(elem->data.rs, file)) {
                rs->writing_in_progress = false;
                return true;
            }
        }
    }

    rs->writing_in_progress = false; // powrot ze sciezki
    return false;
}

// otwiera i zamyka plik, zapisuje od dolu stosu
int rstack_write(char const *path, rstack_t *rs) {
    if (path == nullptr || rs == nullptr) { errno = EINVAL; return -1; }
    FILE *f = fopen(path, "w");
    if (f == nullptr) return -1;
    rstack_write_recursive(rs, f);
    if (fclose(f) == EOF) return -1;
    return 0;
}

// czyta liczby i sklada w calosc weryfikujac wejscie
rstack_t *rstack_read(char const *path) {
    if (path == nullptr) {
        errno = EINVAL;
        return nullptr;
    }
    FILE *f = fopen(path, "r");
    if (f == nullptr) return nullptr;
    rstack_t *rs = rstack_new();
    if (rs == nullptr) {
        fclose(f);
        return nullptr;
    }
    char buffer[256];
    while (fscanf(f, "%255s", buffer) == 1) {
        for (int i = 0; buffer[i] != '\0'; i++) {
            if (!isdigit((unsigned char)buffer[i])) {
                errno = EINVAL;
                rstack_delete(rs);
                fclose(f);
                return nullptr;
            }
        }
        char *endptr;
        errno = 0;
        uint64_t val = strtoull(buffer, &endptr, 10);
        if (errno != 0 || endptr == buffer || *endptr != '\0') {
            errno = EINVAL;
            rstack_delete(rs);
            fclose(f);
            return nullptr;
        }
        if (rstack_push_value(rs, val) == -1) {
            rstack_delete(rs);
            fclose(f);
            return nullptr;
        }
    }
    if (ferror(f)) {
        rstack_delete(rs);
        fclose(f);
        return nullptr;
    }
    fclose(f);
    return rs;
}
