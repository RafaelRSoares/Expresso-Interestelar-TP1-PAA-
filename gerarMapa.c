#include "gerarMapa.h"
#include "time.h"

void gerarMapa(){
    srand(time(NULL));
    FILE* file = fopen("ArquivoGerado.txt", "w");
    int altura, largura, pecas, durabilidade, custo, aumento, contadorPecas=0, linha, coluna;
    if(file){
        printf("Para gerar o mapa precisamos definir alguns parametros\n");
        printf("Qual deve ser a altura e largura do mapa (separados por espaco)?\n");
        scanf("%d %d", &altura, &largura);
        printf("Qual deve ser a quantidade de pecas?\n");
        scanf("%d", &pecas);
        printf("Qual deve ser o valor das variaves\nDurabilidade do expresso: ");
        scanf("%d", &durabilidade);
        printf("Custo para cada movimentacao: ");
        scanf("%d", &custo);
        printf("Aumento de durabilidade por peca: ");
        scanf("%d", &aumento);
        fprintf(file, "%d %d %d\n", durabilidade, custo, aumento);
        fprintf(file, "%d %d\n",  altura, largura);
        char mapa[altura][largura];
        char opcoes[] = {'-', '|', '+'};
        for(int i=0;i<altura;i++){
            for(int j=0;j<largura;j++){
                mapa[i][j] = '.';
            }
        }
        for(int i=0;i<2;i++){
            linha = gerarNumeroAleatorio(altura);
            coluna = gerarNumeroAleatorio(largura);
            if(mapa[linha][coluna] == '.'){
                if(i == 0){
                    mapa[linha][coluna] = 'X';}
                else{
                    mapa[linha][coluna] = 'F'; 
                }
            }
            else{
                i--;
            }
        }
        for(int i=0;i<pecas;i++){
            linha = gerarNumeroAleatorio(altura);
            coluna = gerarNumeroAleatorio(largura);
            if(mapa[linha][coluna] == '.'){
                mapa[linha][coluna] = 'P';
            }
            else{
                i--;
            }
        }
        for(int i=0;i<altura;i++){
            for(int j=0;j<largura;j++){
                fprintf(file, "%c", mapa[i][j]);
            }fprintf(file, "\n");
        }
        for(int i=0;i<altura;i++){
            for(int j=0;j<largura;j++){
                printf("%c", mapa[i][j]);
            }printf("\n");
        }
        fclose(file);
    }
    else{
        printf("Erro ao abrir o arquivo");
    }
}

int gerarNumeroAleatorio(int limite){
    return rand() % limite;
}