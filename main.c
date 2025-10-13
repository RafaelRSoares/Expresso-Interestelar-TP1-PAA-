#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "backtracking.h"
#define STRING 20

//#define ANALISE

#ifdef ANALISE
extern int totalChamadas;
extern int nivelMaximo;
#endif

int main(){
    //printf("Digite o nome do arquivo: ");
    char nome[STRING];
    //scanf("%s", nome);
    strcpy(nome,"arquivo2.txt");


    FILE* arqEntrada;
    arqEntrada = fopen(nome, "r");

    if(arqEntrada==NULL){
        printf("Erro ao ler o arquivo.");
        return 0;
    }
    //nave do filme "Interestelar", pareceu que caberia bem
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

    Percurso percurso;
    
    inicializarPercurso(&percurso);
    setMapa(Mapa,&Endurance);
    
    imprimeMapaAdm(Mapa);
    imprimeNave(&Endurance);
    printf("======================================================\n");

    printf("\n%d\n\n",movimentar(Mapa,&Endurance,&percurso,Nulo));

    printf("======================================================\n");
    imprimirLista(&percurso);
    imprimeNave(&Endurance);
    //imprimeMapaAdm(Mapa);

    #ifdef ANALISE
    printf("\n=================== MODO DE ANALISE ===================\n");
    printf("Total de chamadas recursivas: %d\n", totalChamadas);
    printf("Nivel maximo de recursao: %d\n", nivelMaximo);
    printf("=======================================================\n");
#endif

    return 0;
}