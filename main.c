#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gerarMapa.h"
#include "backtracking.h"
#define STRING 20

int LINHAS;
int COLUNAS;

//Variáveis para análise
int modoAnaliseAtivo = 0;
int totalChamadas = 0;
int nivelMaximo = 0;

//Função para zear os contadores
void resetAnalise() {
    totalChamadas = 0;
    nivelMaximo = 0;
}

int main() {
    srand(time(NULL));
    int escolha = 0;
    int modoAnalise = 0; // 0 = normal, 1 = análise

    escolha = 1;
    while (escolha != 4) {
        printf("==== BEM-VINDO AO EXPRESSO INTERESTELAR ====\n");
        printf("Deseja:\n");
        printf("1 - Inserir e executar um novo arquivo\n");
        printf("2 - Gerar um mapa teste\n");
        printf("3 - Executar arquivo em modo de analise\n");
        printf("4 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        if (escolha == 4) {
            printf("Encerrando o programa...\n");
            break;
        }

        if (escolha == 1 || escolha == 3) {
            if (escolha == 3) {
                modoAnaliseAtivo = 1; // liga a flag
                resetAnalise();
                printf("[MODO DE ANALISE ATIVADO]\n");
        } else {
            modoAnaliseAtivo = 0; //desliga
        }

            char nome[STRING];
            printf("Digite o nome do arquivo: ");
            scanf("%s", nome);
            FILE* arqEntrada = fopen(nome, "r");
            if (arqEntrada == NULL) {
                printf("Erro ao ler o arquivo.\n");
                continue;
            }

            nave Endurance; 
            fscanf(arqEntrada, "%d %d %d", &Endurance.Durabilidade, &Endurance.DanoPorSetor, &Endurance.AumentoPorPeca);
            fscanf(arqEntrada, "%d %d", &LINHAS, &COLUNAS);

            quadrante **Mapa = malloc(LINHAS * sizeof(quadrante*));
            for (int i = 0; i < LINHAS; i++)
                Mapa[i] = malloc(COLUNAS * sizeof(quadrante));

            for (int i = 0; i < LINHAS; i++) {
                for (int j = 0; j < COLUNAS; j++) {
                    fscanf(arqEntrada, " %c", &Mapa[i][j].Tipo);
                }
            }
            fclose(arqEntrada);

            int pecasTotais = 0;
            for (int i = 0; i < LINHAS; i++)
                for (int j = 0; j < COLUNAS; j++)
                    if (Mapa[i][j].Tipo == 'P')
                        pecasTotais++;

            Percurso percurso;
            inicializarPercurso(&percurso);
            setMapa(Mapa, &Endurance);

            int resultado = movimentar(Mapa, &Endurance, &percurso, Nulo);
            if (resultado == 1)
                printf("\nApesar da bravura, a tripulacao falhou em sua jornada.\n");
            
            imprimirLista(&percurso);
            printf("\n");

            int verificacao = TodasAsPecasForamColetadas(&percurso);

            if (resultado == 0 && verificacao == 0)
                printf("A tripulacao finalizou sua jornada.\n\n");

            if (modoAnaliseAtivo == 1) {
                printf("=================== MODO DE ANALISE ===================\n");
                printf("Total de chamadas recursivas: %d\n", totalChamadas);
                printf("Nivel maximo de recursao: %d\n", nivelMaximo);
                printf("=======================================================\n\n");
            }

            for (int i = 0; i < LINHAS; i++)
                free(Mapa[i]);
            free(Mapa);


            break;
        }

        if (escolha == 2) {
            gerarMapa();
        }    

        break;
    }

    return 0;
}
