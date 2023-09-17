#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct s {
    int estadoFinal;
    int **tt;
    char *columnas;
};

typedef struct s sistemaNumerico;

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


// Funciones Auxiliares ----------------------------------------------------------------------------

int pasarCharAInt(char c) {
    return c-48;
}

int between(int n, int min, int max) {
    return n >= min && n <= max;
}

int perteneceAOctal(char c) {
    return between(pasarCharAInt(c), 0, 7);
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

int esLetraHexa(char c) {
    return between(c, 65, 70);
}


// Aca verifico si la palabra forma parte del lenguaje -----------------------------------------------

int esPalabra(char *cadena, sistemaNumerico s) {

    int estado = 0;
    unsigned i;

    for(i=0; cadena[i]; i++) { // Acá hice un pequeño cambio para poder pasar la matriz como parametro
        estado = s.tt[estado*strlen(s.columnas) + indiceColumnas(cadena[i], s.columnas)];
    }
    
    if(estado == s.estadoFinal) {
        return 1;
    }

    return 0;
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


// Main -----------------------------------------------------------------------------------

int main() {

    sistemaNumerico decimal = {estadoFinalDecimales, ttDecimales, columnasDeDecimales};
    sistemaNumerico octal = {estadoFinalOctales, ttOctales, columnasDeOctales};
    sistemaNumerico hexadecimal = {estadoFinalHexa, ttHexa, columnasDeHexa};

    char *palabra = "0xAB234";
    char **listaDePalabras;

    // for(unsigned i = 0; palabra[i]; ){
    //     if(palabra[i] != '$') {

    //     }
    // }

    // printf("%d", decimal.tt[3][1]);
    // return 0;

    if(verificaDecimales(palabra) && esPalabra(palabra, decimal) || !strcmp(palabra, "0")) {
        printf("siii es decimal :)");
        return 0;
    }
    
    if (verificaOctales(palabra) && esPalabra(palabra, octal)) {
        printf("siii es octal :)");
        return 0;
    }

    if(verificaHexadecimales(palabra) && esPalabra(palabra, hexadecimal)) {
        printf("siii es hexa :)");
        return 0;
    }

    else {
        printf("no es palabra :(");
        return 0;
    }

    return 0;

}