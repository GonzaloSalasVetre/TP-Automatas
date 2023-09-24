#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct s {
    int estadoFinal;
    int **tt;
    char *columnas;
} infoAutomata;

typedef struct nodo {
    char *info;
    struct nodo *sig;
} nodoL;

typedef nodoL* lista;

// Funciones Auxiliares ----------------------------------------------------------------------------

// Parte 2

int pasarCharAInt(char c) {
    return c-48;
}

int between(int n, int min, int max) {
    return n >= min && n <= max;
}

int potencia(int base, int exponente){
	if(exponente == 0) {
		return 1;
	}
    else {
		return base*potencia(base, exponente-1);
	}
}

int indiceColumnas(char c, char *columnas) {
    unsigned i;
    for (i = 0; columnas[i]; i++) {
        if (columnas[i] == c) {
            return i;
        }
    }
    return i-1;
}

void agregarElemento(lista *listaE, char *elemento) {
    lista aux = (nodoL *)malloc(sizeof(nodoL));
	aux->info = elemento;
	aux->sig = *listaE;
	*listaE = aux;
}

// Aca verifico si la palabra forma parte del lenguaje -----------------------------------------------

int esPalabra(char *cadena, infoAutomata automata) {

    int estado = 0;
    unsigned i;

    for(i=0; cadena[i]; i++) { // Acá hice un pequeño cambio para poder pasar la matriz como parametro
        estado = automata.tt[estado*strlen(automata.columnas) + indiceColumnas(cadena[i], automata.columnas)];
    }
    
    if(estado == automata.estadoFinal) {
        return 1;
    }

    return 0;
}


