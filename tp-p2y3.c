#include <stdio.h>
#include <stdlib.h>
#include "tp-aux.c"
#include "pila.c"

// Parte 2

// int pasarCadenaAEntero(char *cadena) {
//     int entero = 0;
//     for (unsigned i = 0; cadena[i]; i++) {
//         entero += pasarCharAInt(cadena[i])*potencia(10, strlen(cadena)-(i+1));
//     }
//     return entero;
// }

// Parte 3

void evaluar(char *cadena, st *pilaNumeros, stC *pilaOperadores) {
    for (unsigned i = 0; cadena[i]; i++) {
        if (isdigit(cadena[i])) {
            int entero = 0;
            while (cadena[i] && isdigit(cadena[i])) {
                entero = entero*10 + pasarCharAInt(cadena[i]);
                i++;
            }
            push(&(*pilaNumeros), entero);
            printf("%d \n", entero);
            i--;
        }
        else {
            pushC(&(*pilaOperadores), cadena[i]);
            printf("%c \n", cadena[i]);
        }
        
    }
}

int main() {
    st pilaNumeros = (st)malloc(sizeof(st));
    pilaNumeros->sgte = NULL;
    stC pilaOperadores = (stC)malloc(sizeof(stC));
    pilaOperadores->sgte = NULL;

    evaluar("12+2+3", &pilaNumeros, &pilaOperadores);

    printStack(pilaNumeros);
    printStackC(pilaOperadores);

    return 0;
}