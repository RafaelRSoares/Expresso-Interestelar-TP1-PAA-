#ifndef LISTA_H_
#define LISTA_H_
#include <stdlib.h>
#include <stdio.h>

typedef struct Informacoes* Apontador;
typedef struct Informacoes{
    int Linha;
    int Coluna;
    int Durabilidade;
    int PecasColetadas;
    short Consertado;
    Apontador Prox;
} Informacoes;

typedef struct{
    Apontador Primeiro;
    Apontador Ultimo;
} Percurso;

void inicializarPercurso(Percurso* lista);

void inserePercurso(Percurso* lista, int linha, int coluna, int durabilidade, int pecasColetadas, short Consertado);

void RemoverUlitmoPercruso(Percurso* lista);

void imprimirLista(Percurso* lista, int pecasTotais);

int TodasAsPecasForamColetadas(Percurso* lista, int pecasTotais);

#endif