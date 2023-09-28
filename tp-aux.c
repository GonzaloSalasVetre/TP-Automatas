#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct s {
    int estadoFinal;
    int **tt;
    char *columnas;
} infoAutomata;


// Parte 2

int pasarCharAInt(char c) {
    return c-48;
}

// Funciones Auxiliares ----------------------------------------------------------------------------

int between(int n, int min, int max) {
    return n >= min && n <= max;
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

// Aca verifico si la palabra forma parte del lenguaje -----------------------------------------------
// con la información del autómata

int esPalabra(char *cadena, infoAutomata automata) {
    int estado = 0;
    unsigned i;
    for(i=0; cadena[i]; i++) { // Acá hice un cambio porque me toma la matriz como un arreglo
        estado = automata.tt[estado*strlen(automata.columnas) + indiceColumnas(cadena[i], automata.columnas)];
    }
    if(estado == automata.estadoFinal) {
        return 1;
    }
    return 0;
}


