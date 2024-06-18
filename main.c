/* 
        gcc main.c calculadora.c -o calculadora
        ./calculadora

*/

#include <stdio.h>
#include <string.h>
#include "calculadora.h"

#define TAMANHO_MAXIMO 100
#define OPERADORES "+-*/^"

int main() {

    char posFix[] = "8 5 2 4 + * +"; //Insira a expressão aqui

    Expressao expr;
    strcpy(expr.posFixa, posFix);
    expr.Valor = getValor(expr.posFixa);
    strcpy(expr.inFixa, getFormaInFixa(expr.posFixa));

    printf("Expressao Infixa: %s\n", expr.inFixa);
    printf("Valor: %.2f\n", expr.Valor);

    return 0;
}