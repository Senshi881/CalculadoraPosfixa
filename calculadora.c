#include <stdio.h>
#include <stdlib.h>

#include "calculadora.h"

void inicializar(Pilha *s){
    s->topo = -1;
}
int vazio(Pilha *s){
    return s->topo == -1;
}
int lotado(Pilha *s){
    return s->topo == MAX_TAM - 1;
}

void empilhar(Pilha *s, double valor){
    if (lotado(s)) {
        printf("\n*ERRO PILHA CHEIA*");
        exit(EXIT_FAILURE);
    }
    s->itens[++s->topo] = valor;
}

double desempilhar(Pilha *s){
    if(vazio(s)){
        printf("\n*ERRO PILHA VAZIA*");
        exit(EXIT_FAILURE);
    }
    return s->itens[s->topo--];
}