/*

    gcc -o calculadora main.c calculadora.c -lm
    ./calculadora

      */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "calculadora.h"

double notacaoPosFixa(char *expressao) {
    Pilha s;
    inicializar(&s);
    char *obtido = strtok(expressao, " ");

    while (obtido != NULL){
        if(isdigit(*obtido) || (*obtido == '-' && isdigit(*(obtido + 1)))){
            empilhar(&s, atof(obtido));
        } else{
            double val2 = desempilhar(&s);
            double val1 = desempilhar(&s);
            switch (*obtido){
                case '+': empilhar(&s, val1 + val2); break;
                case '-': empilhar(&s, val1 - val2); break;
                case '*': empilhar(&s, val1 * val2); break;
                case '/': 
                    if(val2 == 0){
                        printf("\n*ERRO:DIVISAO POR ZERO*");
                        exit(EXIT_FAILURE);
                    }
                    empilhar(&s, val1 / val2); 
                    break;
                case '^': empilhar(&s, pow(val1, val2)); break;
                case 'r': empilhar(&s, sqrt(val2)); break; // Raiz quadrada
                case 's': empilhar(&s, sin(val2)); break; // Seno
                case 'c': empilhar(&s, cos(val2)); break; // Cosseno
                case 't': empilhar(&s, tan(val2)); break; // Tangente
                case 'l': empilhar(&s, log10(val2)); break; // Logaritmo base 10
                default:
                    printf("\n*ERRO: OPERADOR INVALIDO %c*", *obtido);
                    exit(EXIT_FAILURE);
            }
        }
        obtido = strtok(NULL, " ");
    }

    return desempilhar(&s);
}

int main(){
    char expressao[MAX_TAM];

    printf("\nDigite a notacao pos-fixada ou digite 'sair' para cancelar: ");
    while (fgets(expressao, MAX_TAM, stdin) != NULL){
        expressao[strcspn(expressao, "\n")] = 0;
        if(strcmp(expressao, "sair") == 0){
            break;
        }

        double resultado = notacaoPosFixa(expressao);
        printf("\nResultado: %lf", resultado);

        printf("\nDigite a notacao pos-fixada ou digite 'sair' para cancelar: ");
    }

    return 0;
}