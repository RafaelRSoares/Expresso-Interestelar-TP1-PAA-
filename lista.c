#include "lista.h"

void inicializarPercurso(Percurso* lista){
    lista->Primeiro = (Apontador) malloc(sizeof(Informacoes));
    lista->Ultimo = lista->Primeiro;
    lista->Primeiro->Prox = NULL;
}

void inserePercurso(Percurso* lista, int linha, int coluna, int durabilidade, int pecasColePecasColetadas, short Consertado){
    lista->Ultimo->Prox = (Apontador) malloc(sizeof(Informacoes));
    lista->Ultimo = lista->Ultimo->Prox;
    lista->Ultimo->Linha = linha;
    lista->Ultimo->Coluna = coluna;
    lista->Ultimo->Durabilidade = durabilidade;
    lista->Ultimo->PecasColetadas = pecasColePecasColetadas;
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
    int Ajuda = 0;
    while(Aux != NULL){
        if(Ajuda == 1 || Aux->Prox == NULL) {
            Ajuda = 0;
            int sobrou = 4 - Aux->PecasColetadas;
            printf("linha: %d, Coluna: %d D: %d pecas restantes: %d\n", Aux->Linha, Aux->Coluna, Aux->Durabilidade, sobrou);
            if(sobrou == 0){
                printf("\nA jornada sera finalizada sem mais desafios\n");
                break;
            }
            Aux = Aux->Prox;
        } else if(Ajuda == 0){
            Ajuda = 1;
            Aux = Aux->Prox;
        }
    }
}

int TodasAsPecasForamColetadas(Percurso* lista) {
    Apontador Aux = lista->Primeiro->Prox;
    while (Aux != NULL) {
        if (Aux->PecasColetadas ==4) {
            return 1;
        }
        Aux = Aux->Prox;
    }
    return 0;
}
