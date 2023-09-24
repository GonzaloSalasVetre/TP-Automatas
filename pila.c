#include <stdio.h>
#include <stdlib.h>

typedef struct tnodo {
	int info;
	struct tnodo* sgte;
}nodo;

typedef nodo* st;

typedef struct tnodoC {
	char info;
	struct tnodoC* sgte;
}nodoC;

typedef nodoC* stC;

void push(st* pila,int x) {
	st p = (st)malloc(sizeof(nodo));

	p->info = x;
	p->sgte = *pila;

	*pila = p;
	return;
}

int pop(st* pila) {
	int x = (*pila)->info;
	st p = (*pila);

	(*pila) = p->sgte;	
	free(p);	
	return x;
}

void pushC(stC* pila,int x) {
	stC p = (stC)malloc(sizeof(nodoC));

	p->info = x;
	p->sgte = *pila;

	*pila = p;
}

int popC(stC* pila) {
	int x = (*pila)->info;
	stC p = (*pila);

	(*pila) = p->sgte;	
	free(p);	
	return x;
}

void printStack(st s) {
  while (s->sgte != NULL) {
    printf("%d", s->info);
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