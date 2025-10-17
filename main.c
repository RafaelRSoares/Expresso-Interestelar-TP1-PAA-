#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerarMapa.h"
#include "backtracking.h"
#define STRING 20

int LINHAS;
int COLUNAS;

//#define ANALISE

#ifdef ANALISE
extern int totalChamadas;
extern int nivelMaximo;
#endif

int main(){
    int escolha;
    while (escolha != 3){
        printf("==== BEM VINDO AO EXPRESSO INTERESTELAR ====\n");
        printf("Deseja: \n");
        printf("1 - Inserir e executar um novo arquivo\n");
        printf("2 - Gerar um mapa teste\n");
        printf("3 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        if(escolha == 1){
            char nome[STRING];
            printf("Digite o nome do arquivo: ");
            scanf("%s", nome);
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

            quadrante **Mapa;
            Mapa = malloc(LINHAS * sizeof(quadrante*));
            for (int i=0;i<LINHAS; i++){
                Mapa[i] = malloc(COLUNAS * sizeof (quadrante));
            }

            for(int i = 0; i < LINHAS; i++){
                for(int j = 0; j < COLUNAS; j++){
                    fscanf(arqEntrada, " %c", &Mapa[i][j].Tipo);
                }
            }

            int pecasTotais = 0;
            for(int i = 0; i < LINHAS; i++){
                for(int j = 0; j < COLUNAS; j++){
                    if(Mapa[i][j].Tipo == 'P'){
                        pecasTotais+=1;
                    }
                }
            }

            fclose(arqEntrada);

            Percurso percurso;
            inicializarPercurso(&percurso);
            setMapa(Mapa,&Endurance);

            // imprimeMapaAdm(Mapa);
            // printf("======================================================\n");
            // printf("\n%d\n\n",movimentar(Mapa,&Endurance,&percurso,Nulo));
            // printf("======================================================\n");

            int resultado = movimentar(Mapa,&Endurance,&percurso,Nulo);
            if(resultado == 1){
            printf("\nApesar da bravura a tripulacao falhou em sua jornada\n");
            }

            printf("\n");
            imprimirLista(&percurso);

            printf("\n");
            int verificacao = TodasAsPecasForamColetadas(&percurso);

            if(resultado == 0 && verificacao == 0){
                printf("A tripulacao finalizou sua jornada\n\n");
            }
            // else if(resultado == 0 && verificacao == 1){
            //     printf("A jornada sera finalizada sem mais desafios\n\n");
            // }

            //liberar memoria
            for(int i=0;i<LINHAS; i++){
                free(Mapa[i]);
            }
            free(Mapa);
        }

        if(escolha == 2){
            gerarMapa();

        #ifdef ANALISE
        printf("\n=================== MODO DE ANALISE ===================\n");
        printf("Total de chamadas recursivas: %d\n", totalChamadas);
        printf("Nivel maximo de recursao: %d\n", nivelMaximo);
        printf("=======================================================\n");
    #endif
    }
    }
    return 0;
}