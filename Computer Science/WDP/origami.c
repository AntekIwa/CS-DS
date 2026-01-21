/*
 * Zadanie origami WDP*
 * Antoni Iwanowski
 * O(2^n)
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//epsilion do porownywania
#define EPS 1e-6

// struct do trzymania punktu
typedef struct {
    double x, y;
} Point;

// structy - prostokat, kolo, zgiecie - uzywamy wczesniej zdefiniowanego punktu
typedef struct {
    Point P1, P2;
} Rect;

typedef struct {
    double r;
    Point center;
} Circle;

typedef struct {
    Point P1, P2;
    int k;
} Fold;

// typy kartek dla wygody korzystania
typedef enum {TYPE_RECT, TYPE_CIRCLE, TYPE_FOLD} Type;

// struct dla kartki, przyjmuje jeden z mozliwych typow i trzyma dla  niego odpowiednie informacje
typedef struct {
    Type type;
    union {
        Rect rect;
        Circle circle;
        Fold fold;
    } info;
} Card;

Card *cards; // globalna tablica trzymajaca kartki

double product(Point p1, Point p2, Point p){ // iloczyn wektorowy
    double ax = p2.x - p1.x;
    double ay = p2.y - p1.y;
    double bx = p.x - p1.x;
    double by = p.y - p1.y;
    return ax * by - ay * bx;
}

Point reflection(Point l1, Point l2, Point p){ // odbijamy punkt wzgledem prostej (odbicia)
    double A = l1.y - l2.y;
    double B = l2.x - l1.x;
    double C = -A * l1.x - B * l1.y;
    // Wartość równania prostej po podstawieniu współrzędnych punktu P
    double val = A * p.x + B * p.y + C;
    // Kwadrat długości wektora normalnego [A, B] (mianownik)
    double len_sq = A * A + B * B;

    double factor = (2 * val) / len_sq;
    Point ref;
    ref.x = p.x - A * factor;
    ref.y = p.y - B * factor;
    return ref;
}

int count_layers(int card_idx, Point p){
    /* rekurencyjna funkcja do liczenia warstw
     * sprawdzamy czym jest nasza kartka - jak kolo/prostokat to zwykly check czy zawieramy sie w nim
     * jak zgiecie to musimy sprawdzic ktora strona - jak lewa to zabrana zostala z tamtad kartka - zatem 0
     * jak prawa to sprawdzamy czy bylo cos przed zgieciem - wywolujemy sie rekurencyjnie po obu stronach zgiecia i sprawdzamy dalej
     */
    Card *act = &cards[card_idx];
    if(act->type == TYPE_RECT){
        if((p.x >= act->info.rect.P1.x - EPS) && (p.y >= act->info.rect.P1.y - EPS) &&
           (p.x <= act->info.rect.P2.x + EPS) && (p.y <= act->info.rect.P2.y + EPS)) return 1;
        return 0;
    }
    else if(act->type == TYPE_CIRCLE){
        double dx = p.x - act->info.circle.center.x;
        double dy = p.y - act->info.circle.center.y;
        if(dx * dx + dy * dy <= (act->info.circle.r + EPS) * (act->info.circle.r + EPS)) return 1;
        return 0;
    }
    else if(act->type == TYPE_FOLD){
        Fold *f = &act->info.fold;
        double site = product(f->P1, f->P2, p);
        if(site < -EPS) return 0;
        else if(site <= EPS) return count_layers(f->k, p);
        else{
            Point ref = reflection(f->P1, f->P2, p);
            return count_layers(f->k, p) + count_layers(f->k, ref);
        }
    }
    return 0;
}

int main(){
    int n,q;
    scanf("%d %d", &n, &q);
    cards = (Card*)malloc((size_t)n * sizeof(Card));
    for(int i = 0; i < n; i++){
        char typ;
        if(scanf(" %c", &typ)){}
        if(typ == 'P'){
            cards[i].type = TYPE_RECT;
            scanf("%lf %lf %lf %lf", &cards[i].info.rect.P1.x, &cards[i].info.rect.P1.y, &cards[i].info.rect.P2.x, &cards[i].info.rect.P2.y);
        }
        else if(typ == 'K'){
            cards[i].type = TYPE_CIRCLE;
            scanf("%lf %lf %lf", &cards[i].info.circle.center.x, &cards[i].info.circle.center.y, &cards[i].info.circle.r);
        }
        else if(typ == 'Z'){
            cards[i].type = TYPE_FOLD;
            int orgin;
            scanf("%d %lf %lf %lf %lf", &orgin, &cards[i].info.fold.P1.x, &cards[i].info.fold.P1.y, &cards[i].info.fold.P2.x, &cards[i].info.fold.P2.y);
            cards[i].info.fold.k = orgin - 1;
        }
    }
    for(int i = 0; i < q; i++){
        int k;
        Point p;
        scanf("%d %lf %lf", &k, &p.x, &p.y);
        printf("%d\n", count_layers(k - 1, p));
    }
    free(cards);
    return 0;
}
