#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tnodo {
	double info;
	struct tnodo* sgte;
}nodo;

typedef nodo* st;

typedef struct tnodoC {
	char info;
	struct tnodoC* sgte;
}nodoC;

typedef struct tnodoS {
    char *info;
    struct tnodoS *sgte;
} nodoS;

typedef nodoS* stS;

typedef nodoC* stC;

void push(st* pila,double x) {
	st p = (st)malloc(sizeof(nodo));
	p->info = x;
	p->sgte = *pila;
	*pila = p;
	return;
}

double pop(st* pila) {
	double x = (*pila)->info;
	st p = (*pila);
	(*pila) = p->sgte;	
	free(p);	
	return x;
}

void pushC(stC* pila,char x) {
	stC p = (stC)malloc(sizeof(nodoC));
	p->info = x;
	p->sgte = *pila;
	*pila = p;
}

char popC(stC* pila) {
	char x = (*pila)->info;
	stC p = (*pila);
	(*pila) = p->sgte;	
	free(p);	
	return x;
}

void pushS(stS* pila, char *s) {
	stS p = (stS)malloc(sizeof(nodoS));
	p->info = s;
	p->sgte = *pila;
	*pila = p;
	return;
}

char* popS(stS* pila) {
	char *x = (*pila)->info;
	stS p = (*pila);
	(*pila) = p->sgte;
	free(p);	
	return x;
}