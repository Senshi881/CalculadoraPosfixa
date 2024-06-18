#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include "calculadora.h"

#define TAMANHO_MAXIMO 100
#define OPERADORES "+-*/^"

// Estrutura da pilha
typedef struct {
    int topo;
    char *items[TAMANHO_MAXIMO];
} Pilha;

// Funções auxiliares para manipular a pilha
void inicializaPilha(Pilha *pilha) {
    pilha->topo = -1;
}

int pilhaVazia(Pilha *pilha) {
    return pilha->topo == -1;
}

int pilhaCheia(Pilha *pilha) {
    return pilha->topo == TAMANHO_MAXIMO - 1;
}

void empilhar(Pilha *pilha, char *item) {
    if (pilhaCheia(pilha)) {
        printf("Pilha está cheia\n");
        exit(1);
    }
    pilha->items[++(pilha->topo)] = strdup(item);
}

char *desempilha(Pilha *pilha) {
    if (pilhaVazia(pilha)) {
        printf("Pilha esta vazia\n");
        exit(1);
    }
    return pilha->items[(pilha->topo)--];
}

bool ehOperador(char operador) {
    return strchr(OPERADORES, operador) != NULL;
}

bool ehFuncao(char *funcao) {
    return (strcmp(funcao, "sen") == 0 || strcmp(funcao, "cos") == 0 ||
            strcmp(funcao, "tan") == 0 || strcmp(funcao, "log") == 0);
}

float avaliarPosfixa(char *posFixada) {
    Pilha pilha;
    inicializaPilha(&pilha);
    char *token = strtok(posFixada, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            empilhar(&pilha, token);
        }
        else if (ehOperador(token[0]) && strlen(token) == 1) {
            float b = atof(desempilha(&pilha));
            float a = atof(desempilha(&pilha));
            float result;
            switch (token[0]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
                case '^':
                    result = powf(a, b);
                    break;
                default:
                    result = 0.0;
                    break;
            }
            char resultStr[32];
            snprintf(resultStr, sizeof(resultStr), "%f", result);
            empilhar(&pilha, resultStr);
        } else if (ehFuncao(token)) {
            float valor = atof(desempilha(&pilha));
            float result;
            float rad = valor * (3.141592 / 180);
            if (strcmp(token, "sen") == 0) {
                result = sinf(rad);
            } else if (strcmp(token, "cos") == 0) {
                result = cosf(rad);
            } else if (strcmp(token, "tan") == 0) {
                result = tanf(rad);
            } else if (strcmp(token, "log") == 0) {
                result = log10f(valor);
            } else {
                result = 0.0;
            }
            char resultStr[32];
            snprintf(resultStr, sizeof(resultStr), "%f", result);
            empilhar(&pilha, resultStr);
        }
        token = strtok(NULL, " ");
    }
    return atof(desempilha(&pilha));
}

char *getFormaInFixa(char *Str) {
    static char infix[512];
    Pilha pilha;
    inicializaPilha(&pilha);

    char *token = strtok(Str, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            empilhar(&pilha, token);
        } else if (ehOperador(token[0]) && strlen(token) == 1) {
            char *b = desempilha(&pilha);
            char *a = desempilha(&pilha);
            char expr[512];
            snprintf(expr, sizeof(expr), "(%s %c %s)", a, token[0], b);
            empilhar(&pilha, expr);
            free(a);
            free(b);
        } else if (ehFuncao(token)) {
            char *a = desempilha(&pilha);
            char expr[512];
            snprintf(expr, sizeof(expr), "%s(%s)", token, a);
            empilhar(&pilha, expr);
            free(a);
        }
        token = strtok(NULL, " ");
    }
    strcpy(infix, desempilha(&pilha));
    return infix;
}

float getValor(char *Str) {
    char postfix[512];
    strcpy(postfix, Str);  
    return avaliarPosfixa(postfix);
}