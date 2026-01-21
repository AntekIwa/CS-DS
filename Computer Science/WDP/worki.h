#ifndef WORKI_H
#define WORKI_H
/* trzymamy wszystko jak liste dwukierunkowa, ale zeby moznabylo w O(1) przepinac to wszystko popodinamy pod Content a Content do worka/biurka
 * W ten sposob przepinamy tylko Content
 * przedmioty i worek to taka sama struktura tylko worek dodatkowo trzyma swoj indeks
*/
struct Content;

struct Node {
	Node *prev = nullptr;
	Node *next = nullptr;
	Content *parent_content = nullptr;
	Content *child_content = nullptr;
	bool is_bag = false;
};

struct przedmiot {
	Node node;
};

struct worek {
	Node node;
	int id = 0;
};

przedmiot *nowy_przedmiot();
worek *nowy_worek();
void wloz(przedmiot *co, worek *gdzie);
void wloz(worek *co, worek *gdzie);
void wyjmij(przedmiot *p);
void wyjmij(worek *w);
int w_ktorym_worku(przedmiot *p);
int w_ktorym_worku(worek *w);
int ile_przedmiotow(worek *w);
void na_odwrot(worek *w);
void gotowe();

#endif
