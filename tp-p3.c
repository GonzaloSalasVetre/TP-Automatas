#include <stdio.h>
#include <stdlib.h>
#include "tp-aux.c"
#include "pila.c"

const int estadoFinalCalc = 1;
const char columnasDeCalc[6] = {'+', '-', '*', '/', 'd'}; // d -> [1-9]
const int ttCalculo[3][5] = {
                                {2,2,2,2,1},
                                {0,0,0,0,1},
                                {2,2,2,2,2}
                              };


const infoAutomata calculoMatematico = {estadoFinalCalc, ttCalculo, columnasDeCalc};

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
        else pushC(&(*pilaOperadores), cadena[i]);
    }
}

double operar(double a, double b, char op) {
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '/':
        if (b == 0) printf("\nNo se puede dividir por cero!\n\n");
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

double realizarCalculo(st pilaNumeros, stC pilaOperadores) {
    while (pilaOperadores->sgte != NULL) {
        calcularOperacion(&pilaNumeros, &pilaOperadores);
    }
    return pilaNumeros->info;
}

int verificaCalculo(char *s) {
    unsigned i;
	for(i=0;s[i];i++) {
	    if(!(esSumaOResta(s[i]) || esMulODiv(s[i]) || isdigit(s[i]))) {
			return 0;
		}
	}
	return 1;
}

int main() {
    st pilaNumeros = (st)malloc(sizeof(nodo));
    pilaNumeros->sgte = NULL;
    stC pilaOperadores = (stC)malloc(sizeof(nodoC));
    pilaOperadores->sgte = NULL;

    char *calculo = (char *)malloc(sizeof(char) * 100);

    fgets(calculo, 100, stdin);

    // Cuando se lee de la terminal a veces se guarda un salto de linea
    if(calculo[strlen(calculo)-1] == 10) calculo[strlen(calculo)-1] = '\0';

    if (verificaCalculo(calculo) && esPalabra(calculo, calculoMatematico)) {
        separarOpYNum(calculo, &pilaNumeros, &pilaOperadores);
        printf("\nEl resultado es: ");
        printf("%f\n", realizarCalculo(pilaNumeros, pilaOperadores));
    }
    else {
        printf("No es un calculo matematico");
    }

    free(pilaNumeros);
    free(pilaOperadores);
    free(calculo);

    fclose(stdin);

    return 0;
}