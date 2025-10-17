#include "gerarMapa.h"
#include "time.h"
#include <unistd.h>

void gerarMapa(){
    srand(time(NULL));
    static int contador = 1;
    char nomeArquivo[50];
    sprintf(nomeArquivo, "ArquivoGerado%d.txt", contador);
    contador++;
    FILE* file = fopen(nomeArquivo, "w");
    int altura, largura, pecas, durabilidade, custo, aumento, contadorPecas=0, linha, coluna, xInicial, yInicial, xFinal, yFinal, escolha, escolha2;
    if(file){
        printf("==== BEM VINDO A GERACAO DE MAPAS INTERESTELAR ====\n");
        printf("Gostaria de gerar o arquivo com base em dificuldades com parametros pre definidos ou configurar todos os parametros?\n");
        printf("1 - Dificuldades\n2 - Configuracao Total\nEscolha: ");
        scanf("%d", &escolha);
        if(escolha == 1){
            printf("Escolha a dificuldade:\n1 - Facil (Durabilidade alta / Mapa pequeno)\n2 - Medio (Durabilidade media / Mapa medio)\n3 - Dificil (Durabilidade baixa / Mapa grande)\nEscolha: ");
            scanf("%d", &escolha2);
            switch (escolha2)
            {
            case 1:
                altura = rand() % 3 + 6;
                largura =rand() % 3 + 6;
                pecas = rand() % 2 + 2;
                durabilidade = rand() % 11 + 50;
                break;
            case 2:
                altura = rand() % 3 + 10;
                largura =rand() % 3 + 10;
                pecas = rand() % 2 + 4;
                durabilidade = rand() % 11 + 35;
                break;
            case 3:
                altura = rand() % 3 + 14;
                largura =rand() % 3 + 14;
                pecas = rand() % 2 + 7;
                durabilidade = rand() % 11 + 25;
                break;
            default:
                break;
            }
            custo = 5;
            aumento = 10;
        }
        else{
        printf("Defina os parametros a seguir\n");
        printf("Qual deve ser a altura e largura do mapa (separados por espaco)?\n");
        scanf("%d %d", &altura, &largura);
        printf("Qual deve ser a quantidade de pecas?\n");
        scanf("%d", &pecas);
        printf("Qual deve ser o valor das variaves\nDurabilidade do expresso: ");
        scanf("%d", &durabilidade);
        printf("Custo para cada movimentacao: ");
        scanf("%d", &custo);
        printf("Aumento de durabilidade por peca: ");
        scanf("%d", &aumento);}
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
                    mapa[linha][coluna] = 'X';
                    xInicial = linha;
                    yInicial = coluna;    
                }
                else{
                    mapa[linha][coluna] = 'F'; 
                    xFinal = linha;
                    yFinal = coluna;  
                }
            }
            else{
                i--;
            }
        }
        int cordenadasXP[pecas], cordenadasYP[pecas];
        for(int i=0;i<pecas;i++){
            linha = gerarNumeroAleatorio(altura);
            coluna = gerarNumeroAleatorio(largura);
            if(mapa[linha][coluna] == '.'){
                mapa[linha][coluna] = 'P';
                cordenadasXP[i] = linha;
                cordenadasYP[i] = coluna;

            }
            else{
                i--;
            }
        }
        gerarCaminhos(altura, largura, mapa, xInicial, yInicial, xFinal, yFinal);
        for(int j=0;j<pecas;j++){
            gerarCaminhos(altura, largura, mapa, xInicial, yInicial, cordenadasXP[j], cordenadasYP[j]);
        }
        ajustarCruzamentos(altura, largura, mapa);

        //complicações e bônus
        int totalExtras = (altura * largura) / 10; //10% do mapa, pra não ser muito
        for (int k = 0; k < totalExtras; k++){
            linha = gerarNumeroAleatorio(altura);
            coluna = gerarNumeroAleatorio(largura);
            if(mapa[linha][coluna] == '.'){
                int tipoExtra = rand() % 4;
                switch (tipoExtra)
                {
                case 0: //Buraco de minhoca (benefico ou random)
                    mapa[linha][coluna] = 'W'; //"W" de Wormhole
                    break;
                case 1: //Asteroide (prejudicial)
                    mapa[linha][coluna] = 'A';
                    break;
                case 2: //Raio gama (gamma ray burst, insta-kill)
                    mapa[linha][coluna] = 'G';
                    break;
                case 3: //Estação de reabastecimento (ajuda)
                    mapa[linha][coluna] = 'R';
                    break;
                default:
                    break;
                }
            }
        }

        for(int i=0;i<altura;i++){
            for(int j=0;j<largura;j++){
                fprintf(file, "%c", mapa[i][j]);
            }fprintf(file, "\n");
        }
        
        fclose(file);
    }
    else{
        printf("Erro ao abrir o arquivo");
    }
}

void gerarCaminhos(int altura, int largura, char mapa[altura][largura], int xInicial, int yInicial, int xFinal, int yFinal) {
    int x = xInicial, y = yInicial;
    int prioridade = rand() % 2;
    while (x != xFinal || y != yFinal) {
        
        int moveu = 0;

        if (prioridade == 0){
        if (x < xFinal && x + 1 < altura && (mapa[x+1][y] == '.' || mapa[x+1][y] == 'P' || mapa[x+1][y] == 'F' || mapa[x+1][y] == '|' || mapa[x+1][y] == '-' || mapa[x+1][y] == '+')) {
            x++;
            if (mapa[x][y] == '.'){
            mapa[x][y] = '|';}
            moveu = 1;
        } 
        else if (x > xFinal && x - 1 >= 0 && (mapa[x-1][y] == '.' || mapa[x-1][y] == 'P' || mapa[x-1][y] == 'F' || mapa[x-1][y] == '|' || mapa[x-1][y] == '-' || mapa[x-1][y] == '+')) {
            x--;
            if (mapa[x][y] == '.'){
            mapa[x][y] = '|';}
            moveu = 1;
        } 
        else if (y < yFinal && y + 1 < largura && (mapa[x][y+1] == '.' || mapa[x][y+1] == 'P' || mapa[x][y+1] == 'F' || mapa[x][y+1] == '|' || mapa[x][y+1] == '-' || mapa[x][y+1] == '+')) {
            y++;
            if (mapa[x][y] == '.'){
            mapa[x][y] = '-';}
            moveu = 1;
        } 
        else if (y > yFinal && y - 1 >= 0 && (mapa[x][y-1] == '.' || mapa[x][y-1] == 'P' || mapa[x][y-1] == 'F'|| mapa[x][y-1] == '|' || mapa[x][y-1] == '-' || mapa[x][y-1] == '+')) {
            y--;
            if (mapa[x][y] == '.'){
            mapa[x][y] = '-';}
            moveu = 1;
        }
    }
        else{
        if (y < yFinal && y + 1 < largura && (mapa[x][y+1] == '.' || mapa[x][y+1] == 'P'|| mapa[x][y+1] == 'F' || mapa[x][y+1] == '|' || mapa[x][y+1] == '-' || mapa[x][y+1] == '+')) {
            y++;
            if (mapa[x][y] == '.'){
            mapa[x][y] = '-';}
            moveu = 1;
        } 
        else if (y > yFinal && y - 1 >= 0 && (mapa[x][y-1] == '.' || mapa[x][y-1] == 'P'|| mapa[x][y-1] == 'F' || mapa[x][y-1] == '|' || mapa[x][y-1] == '-' || mapa[x][y-1] == '+')) {
            y--;
            if (mapa[x][y] == '.'){
            mapa[x][y] = '-';}
            moveu = 1;
        } 
        else if (x < xFinal && x + 1 < altura && (mapa[x+1][y] == '.' || mapa[x+1][y] == 'P' || mapa[x+1][y] == 'F' || mapa[x+1][y] == '|' || mapa[x+1][y] == '-' || mapa[x+1][y] == '+')) {
            x++;
            if (mapa[x][y] == '.'){
            mapa[x][y] = '|';}
            moveu = 1;
        } 
        else if (x > xFinal && x - 1 >= 0 && (mapa[x-1][y] == '.' || mapa[x-1][y] == 'P'|| mapa[x-1][y] == 'F'|| mapa[x-1][y] == '|' || mapa[x-1][y] == '-' || mapa[x-1][y] == '+')) {
            x--;
            if (mapa[x][y] == '.'){
            mapa[x][y] = '|';}
            moveu = 1;
        }
        if (moveu == 0){
        break;
        }
    }
}
}


void ajustarCruzamentos(int altura, int largura, char mapa[altura][largura]) {
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {

            int temVertical = 0, temHorizontal = 0;

            if (i > 0 && (mapa[i - 1][j] == '|' || mapa[i - 1][j] == '+' || mapa[i - 1][j] == 'X' || mapa[i - 1][j] == 'F' || mapa[i - 1][j] == 'P'))
                temVertical = 1;
            if (i < altura - 1 && (mapa[i + 1][j] == '|' || mapa[i + 1][j] == '+' || mapa[i + 1][j] == 'X' || mapa[i + 1][j] == 'F' || mapa[i + 1][j] == 'P'))
                temVertical = 1;

            if (j > 0 && (mapa[i][j - 1] == '-' || mapa[i][j - 1] == '+' || mapa[i][j - 1] == 'X' || mapa[i][j - 1] == 'F' || mapa[i][j - 1] == 'P'))
                temHorizontal = 1;
            if (j < largura - 1 && (mapa[i][j + 1] == '-' || mapa[i][j + 1] == '+' || mapa[i][j + 1] == 'X' || mapa[i][j + 1] == 'F' || mapa[i][j + 1] == 'P'))
                temHorizontal = 1;


            if ((mapa[i][j] == '-' || mapa[i][j] == '|') && temVertical && temHorizontal) {
                mapa[i][j] = '+';
            }
        }
    }
}

int gerarNumeroAleatorio(int limite){
    return rand() % limite;
}