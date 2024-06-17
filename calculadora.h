#ifndef CALCULADORA_H
#define CALCULADORA_H

#define MAX_TAM 100

typedef struct {
    double itens[MAX_TAM];
    int topo;
} Pilha;

void inicializar(Pilha *s);
int vazio(Pilha *s);
int lotado(Pilha *s);
void empilhar(Pilha *s, double valor);
double desempilhar(Pilha *s);

#endif