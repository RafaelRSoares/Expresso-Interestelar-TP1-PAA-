#include "lista.h"

void inicializarPercurso(Percurso* lista){
    lista->Primeiro = (Apontador) malloc(sizeof(Informacoes));
    lista->Ultimo = lista->Primeiro;
    lista->Primeiro->Prox = NULL;
}

void inserePercurso(Percurso* lista, int linha, int coluna, int durabilidade, int pecasRestantes, short Consertado){
    lista->Ultimo->Prox = (Apontador) malloc(sizeof(Informacoes));
    lista->Ultimo = lista->Ultimo->Prox;
    lista->Ultimo->Linha = linha;
    lista->Ultimo->Coluna = coluna;
    lista->Ultimo->Durabilidade = durabilidade;
    lista->Ultimo->PecasRestantes = pecasRestantes;
    lista->Ultimo->Consertado = Consertado;
    lista->Ultimo->Prox = NULL;
}

void RemoverUlitmoPercruso(Percurso* lista){
    if(lista->Primeiro->Prox == NULL){
        return;
    }
    Apontador Aux, anterior;
    Aux = lista->Primeiro->Prox;
    anterior = NULL;
    while(Aux->Prox != NULL){
        anterior = Aux;
        Aux = Aux->Prox;
    }
    if(anterior == NULL){
        lista->Primeiro->Prox = NULL;
        lista->Ultimo = lista->Primeiro;
    }
    else{
        anterior->Prox = NULL;
        lista->Ultimo = anterior;
    }
    free(Aux);   
}

void imprimirLista(Percurso* lista){
    Apontador Aux;
    Aux = lista->Primeiro->Prox;
    while(Aux != NULL){
        printf("[%d][%d] Durabilidade: %d PecasRestantes: %d\n", Aux->Linha, Aux->Coluna, Aux->Durabilidade, Aux->PecasRestantes);
        Aux = Aux->Prox;
    }
}