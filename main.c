#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nave.h"
#include "mapa.h"
#include "lista.h"
#define STRING 20


int main(){
    printf("Digite o nome do arquivo: ");
    char nome[STRING];
    scanf("%s", nome);

    FILE* arqEntrada;
    arqEntrada = fopen(nome, "r");

    if(arqEntrada==NULL){
        printf("Erro ao ler o arquivo.");
        return 0;
    }

    nave NovaNave; 
    
    fscanf(arqEntrada,"%d %d %d", &NovaNave.Durabilidade, &NovaNave.DanoPorSetor, &NovaNave.AumentoPorPeca);
    fscanf(arqEntrada, "%d %d", &LINHAS, &COLUNAS);

    char NovoMapa[LINHAS][COLUNAS];

    int i, j;
    for(i = 0; i < LINHAS; i++){
        for(j = 0; j < COLUNAS; j++){
            fscanf(arqEntrada, "%c", &NovoMapa[i][j]);
        }
    }

}