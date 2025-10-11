#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"
#include "lista.h"
#define STRING 20


int main(){
    //printf("Digite o nome do arquivo: ");
    char nome[STRING];
    //scanf("%s", nome);
    strcpy(nome,"arquivo.txt");


    FILE* arqEntrada;
    arqEntrada = fopen(nome, "r");

    if(arqEntrada==NULL){
        printf("Erro ao ler o arquivo.");
        return 0;
    }

    nave Endurance; 
    
    fscanf(arqEntrada,"%d %d %d", &Endurance.Durabilidade, &Endurance.DanoPorSetor, &Endurance.AumentoPorPeca);
    fscanf(arqEntrada, "%d %d", &LINHAS, &COLUNAS);

    quadrante Mapa[LINHAS][COLUNAS];

    int i, j;
    for(i = 0; i < LINHAS; i++){
        for(j = 0; j < COLUNAS; j++){
            fscanf(arqEntrada, " %c", &Mapa[i][j].Tipo);
        }
    }
    fclose(arqEntrada);
    setMapa(Mapa,&Endurance);
    imprimeNave(&Endurance);
    imprimeMapaAdm(Mapa);

}