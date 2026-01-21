#include "worki.h"
#include <list>

using namespace std;

/* Content ma head - wskaznik na siebie, oraz owner - biurko/worek, ten kto jest wlascicielem */
struct Content {
	Node *head = nullptr;
	worek *owner = nullptr;
	int total_items = 0;
};

Content* desk_content = nullptr;
int next_bag_id = 0;

list<przedmiot*> all_przedmioty;
list<worek*> all_worki;
list<Content*>all_contents;

/* tworzymy nowy Content, ustawaimy wlasciciela na siebie samego */
Content* create_content(worek* owner){
	Content* c = new Content();
	c->owner = owner;
	all_contents.push_back(c);
	return c;
}

/* upewniamy sie czy mamy zadeklarowane biurko, jak nie to tworzymy */
void ensure_init(){
	if(!desk_content)
		desk_content = create_content(nullptr);
}

/* update ilosci trzymanych elementow - przepychamy go dalej (np polaczone worki) */
void update_counts(Content* c, int delta){
	if(!c || delta == 0) 
		return;
	c->total_items += delta;
	if(c->owner && c->owner->node.parent_content)
		update_counts(c->owner->node.parent_content, delta);
}

/* odpinamy wierzcholek z polaczen - jak w liscie */
void detach_node(Node* n) {
	if(!n->parent_content)
		return;
	Content *c = n->parent_content;
	int delta = n->is_bag ? n->child_content->total_items : 1;
	update_counts(c, -delta);

	if(n->prev) n->prev->next = n->next;
	if(n->next) n->next->prev = n->prev;
	if(c->head == n) c->head = n->next;
	n->prev = nullptr;
	n->next = nullptr;
	n->parent_content = nullptr;
}

/* dodajemy wierzcholek w liscie podpinamy go pod Content, update ilosci elementow */
void attach_node(Node* n, Content *c) {
	n->next = c->head;
	n->prev = nullptr;
	if(c->head)
		c->head->prev = n;
	c->head = n;
	n->parent_content = c;

	int delta = n->is_bag ? n->child_content->total_items : 1;
	update_counts(c, delta);
}

/* tworzymy nowy przedmiot, przypinamy go do biurka */
przedmiot* nowy_przedmiot() {
	ensure_init();
	przedmiot* p = new przedmiot();

	p->node.is_bag = false;
	p->node.child_content = nullptr;

	all_przedmioty.push_back(p);

	attach_node(&p->node, desk_content);
	return p;
}

/* analogicznie nowy worek, podpinamy do biurka */
worek* nowy_worek() {
	ensure_init();
	worek *w = new worek();
	w->id = next_bag_id++;
	Content* inner = create_content(w);

	w->node.is_bag = true;
	w->node.child_content = inner;
	all_worki.push_back(w);
	attach_node(&w->node, desk_content);
	return w;
}

/* odpinamy z starej lokalizacji i podpianmy do nowe */
void wloz(przedmiot* co, worek* gdzie) {
	detach_node(&co->node);
	attach_node(&co->node, gdzie->node.child_content);
}

/* analogicznie jw. */
void wloz(worek* co, worek* gdzie) {
	detach_node(&co->node);
	attach_node(&co->node, gdzie->node.child_content);
}

/* odpinamy z starej lokalizacji, przypinamy do biurka */
void wyjmij(przedmiot *p) {
	detach_node(&p->node);
	attach_node(&p->node, desk_content);
}

/* analogicznie jw. */
void wyjmij(worek *w) {
	detach_node(&w->node);
	attach_node(&w->node, desk_content);
}

/* sprawdzamy w ktorym worku jestesmy, sprawdzamy parenta i zwracamy jego Id */
int w_ktorym_worku(przedmiot* p){
	Content* parent = p->node.parent_content;
	if(!parent || !parent->owner)
		return -1;
	return parent->owner->id;
}

/* analogicznie jw. */
int w_ktorym_worku(worek* w){
	Content* parent = w->node.parent_content;
	if(!parent || !parent->owner)
		return -1;
	return parent->owner->id;
}

/* sprawdzamy ile rzeczy podpietych pod nasz content */
int ile_przedmiotow(worek* w) {
	return w->node.child_content->total_items;
}

/* zamieniamy podpiecia contentow, zmieniamy podpiecie contentu biurka na worek i odwrotnie */
void na_odwrot(worek* w) {
	detach_node(&w->node);
	Content* old_desk = desk_content;
	Content* old_bag = w->node.child_content;
	desk_content = old_bag;
	desk_content->owner = nullptr;
	w->node.child_content = old_desk;
	w->node.child_content->owner = w;
	attach_node(&w->node, desk_content);
}

void gotowe(){
	// usuwamy wszystkie elementy, oraz czyscimy vectory, zerujemy zmienne
	for(auto* w : all_worki) delete w;
	for(auto* p : all_przedmioty) delete p;
	for(auto* c : all_contents) delete c;
	all_worki.clear();
	all_przedmioty.clear();
	all_contents.clear();
	desk_content = nullptr;
	next_bag_id = 0;
}

