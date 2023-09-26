#include <stdio.h>
#include <stdlib.h>

typedef struct tnodo {
	double info;
	struct tnodo* sgte;
}nodo;

typedef nodo* st;

typedef struct tnodoC {
	char info;
	struct tnodoC* sgte;
}nodoC;

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
	int x = (*pila)->info;
	stC p = (*pila);

	(*pila) = p->sgte;	
	free(p);	
	return x;
}

void printStack(st s) {
  while (s->sgte != NULL) {
    printf("%f", s->info);
    printf("\n");
    s = s->sgte;
  }
}

void printStackC(stC s) {
  while (s->sgte != NULL) {
    printf("%c", s->info);
    printf("\n");
    s = s->sgte;
  }
}