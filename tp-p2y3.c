#include <stdio.h>
#include <stdlib.h>
#include "tp-aux.c"

// Parte 2

int pasarCadenaAEntero(char *cadena) {
    int entero = 0;
    for (unsigned i = 0; cadena[i]; i++) {
        entero += pasarCharAInt(cadena[i])*potencia(10, strlen(cadena)-(i+1));
    }
    return entero;
}

// Parte 3

int main() {
    printf("%d", pasarCadenaAEntero("5434545"));
}