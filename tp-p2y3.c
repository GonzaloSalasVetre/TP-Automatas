#include <stdio.h>
#include <stdlib.h>
#include "tp-aux.c"
#include "pila.c"

int esSumaOResta(char c) {
    return c == '+' || c == '-';
}

int esMulODiv(char c) {
    return c == '*' || c == '/';
}

// Guarda operadores y numeros en pilas diferentes
void separarOpYNum(char *cadena, st *pilaNumeros, stC *pilaOperadores) {
    for (unsigned i = 0; cadena[i]; i++) {
        if (isdigit(cadena[i])) {
            double entero = 0;
            while (cadena[i] && isdigit(cadena[i])) {
                entero = entero*10 + pasarCharAInt(cadena[i]);
                i++;
            }
            push(&(*pilaNumeros), entero);
            i--;
        }
        else {
            pushC(&(*pilaOperadores), cadena[i]);
        }
    }
}

double operar(double a, double b, char op) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '/':
        return a / b;
    default:
        return  a * b;
    }
}

double calcularOperacion(st *pilaNumeros, stC *pilaOperadores) {
    char op = popC(&(*pilaOperadores));
    char sgteOp = (*pilaOperadores)->info;
    double segNum = pop(&(*pilaNumeros));
    if (esMulODiv(sgteOp))
        calcularOperacion(&(*pilaNumeros), &(*pilaOperadores));
    double priNum = pop(&(*pilaNumeros));
    double resultado = operar(priNum, segNum, op);
    push(&(*pilaNumeros), resultado);
    return resultado;
}

double calcularExpresion(st pilaNumeros, stC pilaOperadores) {
    while (pilaOperadores->sgte != NULL) {
        calcularOperacion(&pilaNumeros, &pilaOperadores);
    }
    return pilaNumeros->info;
}

int main() {
    st pilaNumeros = (st)malloc(sizeof(st));
    pilaNumeros->sgte = NULL;
    stC pilaOperadores = (stC)malloc(sizeof(stC));
    pilaOperadores->sgte = NULL;

    char *calculo = (char *)malloc(sizeof(char) * 100);

    fgets(calculo, 100, stdin);

    if(calculo[strlen(calculo)-1] == 10) { // Cuando se lee de la terminal a veces 
        calculo[strlen(calculo)-1] = '\0'; // se guarda un salto de linea
    }

    separarOpYNum(calculo, &pilaNumeros, &pilaOperadores);
    printf("%f", calcularExpresion(pilaNumeros, pilaOperadores));

    return 0;
}