#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tp-aux.c"
#include "pila.c"

const int estadoFinalDecimales = 2;
const char columnasDeDecimales[5] = {'+', '-', '0', 'd'}; // d -> digitos diferentes a cero
const int ttDecimales[4][4] = {
                                {1,1,3,2},
                                {3,3,3,2},
                                {3,3,2,2},
                                {3,3,3,3}
                              };

const int estadoFinalOctales = 1;
const char columnasDeOctales[3] = {'0', 'd'}; // d -> [1-7]
const int ttOctales[3][2] = {  
                        {1,2},
                        {1,1},
                        {2,2}
                      };

const int estadoFinalHexa = 3;
const char columnasDeHexa[4] = {'x', '0', 'd'}; // d -> [1-9A-F]
const int ttHexa[5][3] = {  
                        {4,1,4},
                        {2,4,4},
                        {4,3,3},
                        {4,3,3},
                        {4,4,4}
                      };


const infoAutomata decimal = {estadoFinalDecimales, ttDecimales, columnasDeDecimales};
const infoAutomata octal = {estadoFinalOctales, ttOctales, columnasDeOctales};
const infoAutomata hexadecimal = {estadoFinalHexa, ttHexa, columnasDeHexa};

// Funciones auxiliares de Parte 1

int perteneceAOctal(char c) {
    return between(pasarCharAInt(c), 0, 7);
}

int esLetraHexa(char c) {
    return between(c, 65, 70);
}

// Esta funcion lo que hace es guardar las palabras, separadas por el signo $, en una lista.
void separarPalabras(stS *listaDePalabras, char *cadena) {
    char *palabra = (char *)malloc(sizeof (char) * 50);
    memset(palabra, '\0', 50); // Sirve para vaciar la palabra
    unsigned j = 0;
    for(unsigned i = 0; cadena[i]; i++){
        if(cadena[i] == '$') {
            pushS(&(*listaDePalabras), strdup(palabra));
            memset(palabra, '\0', 50);
            j = 0;
        }
        else if(i+1 == strlen(cadena)) {
            palabra[j] = cadena[i];
            pushS(&(*listaDePalabras), strdup(palabra));
        }
        else {
            palabra[j] = cadena[i];
            j++;
        }
    }
    free(palabra);
}

// Acá verifica si los caracteres pertenecen al alfabeto del lenguaje --------------------------------
int verificaDecimales(char *s) {
	unsigned i;
	for(i=0;s[i];i++) {
	    if(!(s[i]=='+' || s[i]=='-' || isdigit(s[i]))) {
			return 0;
		}
	}
	return 1;
}

int verificaOctales(char *s) {
	unsigned i;
	for(i=0;s[i];i++) {
	    if(!(perteneceAOctal(s[i])) ) {
			return 0;
		}
	}
	return 1;
}

int verificaHexadecimales(char *s) {
    unsigned i;
	for(i=0;s[i];i++) {
	    if(!(s[i]=='x' || isdigit(s[i]) || esLetraHexa(s[i]))) {
			return 0;
		}
	}
	return 1;
}


// Verificar si las palabra pertenece a un sistema numérico

void perteneceAUnSistemaNumerico(char *cadena, unsigned *i, unsigned *j, unsigned *k, unsigned *l) { 
    if(verificaDecimales(cadena) && esPalabra(cadena, decimal) || !strcmp(cadena, "0")) {
        (*i)++;
        return;
    }
    if (verificaOctales(cadena) && esPalabra(cadena, octal)) {
        (*j)++;
        return;
    }
    if(verificaHexadecimales(cadena) && esPalabra(cadena, hexadecimal)) {
        (*k)++;
        return;
    }
    else {
        (*l)++;
        return;
    }
}


// Main -----------------------------------------------------------------------------------

int main() {

    unsigned cantDecimales = 0;
    unsigned cantOctales = 0;
    unsigned cantHexa = 0;
    unsigned cantNoPertenece = 0;

    char *palabra = (char *)malloc(sizeof(char) * 100);

    fgets(palabra, 100, stdin);

    if(palabra[strlen(palabra)-1] == 10) { // Cuando se lee de la terminal a veces 
        palabra[strlen(palabra)-1] = '\0'; // se guarda un salto de linea
    }

    stS listaDePalabras = (stS)malloc(sizeof(nodoS));
    listaDePalabras->info = NULL;
    listaDePalabras->sgte = NULL;

    printf(palabra);
    printf("\n");
    
    separarPalabras(&listaDePalabras, palabra);
    
	while(listaDePalabras->sgte != NULL){
        printf(listaDePalabras->info);
        printf("\n");
		perteneceAUnSistemaNumerico(popS(&listaDePalabras), &cantDecimales, &cantOctales, &cantHexa, &cantNoPertenece);
	}

    free(palabra);
    free(listaDePalabras);

    printf("Cantidad de numeros decimales: %d \n", cantDecimales);
    printf("Cantidad de numeros octales: %d \n", cantOctales);
    printf("Cantidad de numeros hexadecimales: %d \n", cantHexa);
    printf("Cantidad de palabras que no pertenecen al lenguaje: %d \n", cantNoPertenece);

    fclose(stdin);

    return 0;
}