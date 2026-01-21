#include "zbior_ary.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h> 

static long long g_q = 0; 

/* ---- implementacja wektora ----- */
static void z_init(zbior_ary* z){ /* size - ile uzywamy pamieci, cap - maksymalna pojemnosc aktualna wektora */
    z->data = NULL; 
    z->size = 0; 
    z->cap = 0;
}

static int next_cap(int c){ /* jesli pojemnosc jest zamala, to zwiekszamy na kolejna potege dwojki - log2 powiekszen */
    if(c < 8) return 8; 
    long long n = c + c/2 + 1; 
    if(n > 2147483640) n = 2147483640; 
    return (int)n; 
}
static void z_reserve(zbior_ary* z, int need){ /*rezerwujemy sobie pamiec zgodnie z wyzszym pomyslem */
    if(need <= z->cap) return;
    int nc = z->cap; 
    while(nc < need) nc = next_cap(nc);
    Segment* p = (Segment*)realloc(z->data, (size_t)nc * sizeof(Segment));
    z->data = p; 
    z->cap = nc;
}
static void z_push(zbior_ary* z, Segment s){
    if(z->size == z->cap) z_reserve(z, z->size ? z->size*2 : 8); // jak zamala pojemnosc to zwiekszamy
    z->data[z->size++] = s; // mozemy przypisac pod adresem size nowa wartosc
}
static void z_push_merged(zbior_ary* z, Segment s){
    if(z->size > 0){
        Segment* last = &z->data[z->size-1]; // moze mozemy zmerge'owac z ostatnim przedzialem
        if(last->r == s.r && s.a <= last->b + 1){
            if(s.b > last->b) last->b = s.b;
            return;
        }
    }
    z_push(z, s);
}

/* ------- implementacja zbiorow ---------- */
static int cmp_seg(Segment A, Segment B){ // porownujemy przedzialy do ustawiania ich w dobrej kolejnosci
    if(A.r != B.r) return A.r < B.r ? -1 : 1;
    if(A.a != B.a) return A.a < B.a ? -1 : 1;
    if(A.b != B.b) return A.b < B.b ? -1 : 1;
    return 0;
}

zbior_ary ciag_arytmetyczny(int a, int q, int b){
/* 
trzymamy przedzialy skompresowane - stale przesuniecie przedzialy trzymamy 
[1, x] - oznacza wsystkie liczby od 1 do x, ale po przemnozeniu przez q daje nam dobry ciag 
*/

    if(!g_q) g_q = q;
    zbior_ary Z; 
    z_init(&Z);
    long long r = a % g_q; 
    if(r < 0) r += g_q;
    long long t0 = (a - r)/g_q, t1 = (b - r)/g_q; 
    if(t0 > t1){
        long long t = t0;
        t0 = t1;
        t1 = t;
    }
    z_push(&Z, (Segment){t0, t1, r});
    return Z;
}

zbior_ary singleton(int a){
/* w zasadzie to samo co z zbiorem, ale koniec = poczatek przedzialu */
    zbior_ary Z; 
    z_init(&Z);
    long long r = a%g_q; 
    if(r < 0) r += g_q;
    long long t = (a - r)/g_q;
    z_push(&Z, (Segment){t, t, r});
    return Z;
}

bool nalezy(zbior_ary A, int x){
/* binsearch, wyszukujemy czy mamy przedzial ktory zawiera x, i daje dobra reszte z dzielenia */
    if(A.size == 0) return false;
    long long q = g_q;
    long long r = x%q; 
    if(r < 0) r+=q;
    long long t = (x - r)/q;
    int L = 0, R = A.size - 1;
    while(L <= R){
        int M = L + (R - L)/2;
        Segment s = A.data[M];
        if(s.r < r || (s.r == r && s.b < t)) L = M + 1;
        else if(s.r > r || (s.r == r && s.a > t)) R = M - 1;
        else return true;
    }
    return false;
}

unsigned moc(zbior_ary A){
/* sumujemy dlugosci przedzialow */
    unsigned int total = 0;
    for(int i = 0; i < A.size; i++) total += (unsigned int)(A.data[i].b - A.data[i].a + 1);
    return (unsigned)total;
}

unsigned ary(zbior_ary A){
/* ciagi trzymamy jak najbardziej skompresowane i poloczne, zatem odpowiedz to poprostu size */
    return (unsigned)A.size; 
}

zbior_ary suma(zbior_ary A, zbior_ary B){
    zbior_ary C;
    z_init(&C);
    int i = 0, j = 0; 
    while (i < A.size || j < B.size){
        if (i < A.size && j < B.size){
            int comp = cmp_seg(A.data[i], B.data[j]);  //porownujemy ktory wczesniejszy
            if (comp < 0) z_push_merged(&C, A.data[i++]);
            else if (comp > 0) z_push_merged(&C, B.data[j++]); //merge'ujemy odpowiednie
            else { //jak to samo to dodajemy tylko jeden
                z_push_merged(&C, A.data[i]);
                i++;
                j++;
            }
        }
        else if (i < A.size) z_push_merged(&C, A.data[i++]);
        else z_push_merged(&C, B.data[j++]);
    }
    return C;
}

zbior_ary iloczyn(zbior_ary A, zbior_ary B){
    zbior_ary C;
    z_init(&C);
    int i = 0, j = 0; 
    while (i < A.size && j < B.size) { 
        Segment a = A.data[i];
        Segment b = B.data[j];
        if (a.r < b.r) i++; // rozne reszty mod, napewno sie nie pokrywaja, przesuwamy odpowiednie wskazniki by uzyskac ta sama reszte 
        else if (a.r > b.r) j++;
        else {
            long long l = (a.a > b.a) ? a.a : b.a;  // bierzemy czesc wspolna
            long long r = (a.b < b.b) ? a.b : b.b; 
            if (l <= r) z_push(&C, (Segment){l, r, a.r});
            if (a.b < b.b) i++; 
            else j++;
        }
    }
    return C;
}

zbior_ary roznica(zbior_ary A, zbior_ary B){
    zbior_ary C;
    z_init(&C);
    int i = 0, j = 0; 
    while (i < A.size) {
        Segment x = A.data[i];
        while (j < B.size && (x.r > B.data[j].r || (x.r == B.data[j].r && x.a > B.data[j].b))) j++; //przesuwamy poki rozna reszta, badz dopoki nie dojdziemy do nakladajacych sie przedzialow
        long long l = x.a, r = x.b;
        while (j < B.size && x.r == B.data[j].r && r >= B.data[j].a) { // mamy nakladajacy sie przedzial, odpowiednio go ucinamy
            long long br = B.data[j].b; 
            long long bl = B.data[j].a;
            if (bl > l) z_push(&C, (Segment){l, bl - 1, x.r});
            if (br + 1 > l) l = br + 1;
            if (l > r) break;
            j++;
        }
        if (l <= r) z_push(&C, (Segment){l, r, x.r});
        i++;
    }
    return C;
}
