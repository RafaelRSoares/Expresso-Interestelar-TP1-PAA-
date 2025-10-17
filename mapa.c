#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mapa.h"

void imprimeMapa(quadrante **Mapa){
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++)
            printf("%c",Mapa[i][j].Tipo);  
        printf("\n");
    }
}

void imprimeMapaAdm(quadrante **Mapa){
    printf("=======================================\n");
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++)
            printf("%c",Mapa[i][j].Tipo);  
        printf("\n");
    }
    printf("---------------------------------------\n");
    for (int i = 0; i < LINHAS; i++){
        printf("\nLINHA: %d\n",i);
        for (int j = 0; j < COLUNAS; j++){
            // Rua
            if (Mapa[i][j].Tipo == '-' || Mapa[i][j].Tipo == '|'){
                printf("Quadrante:{%d}{%d}-Tipo:%c Peca:[%d]-Saida:[%d]/ ",i,j,Mapa[i][j].Tipo,Mapa[i][j].Rua.Peca,Mapa[i][j].Rua.Saida); 
                for (int k = 0; k < QUANTIDADECAMINHOSRUA; k++)
                    printf("Dir-[%d] Ace-[%d]/",Mapa[i][j].Rua.CursoRua[k].Caminho,Mapa[i][j].Rua.CursoRua[k].Acesso);
                printf("\n");
            }
            //Cruzamento
            else if (Mapa[i][j].Tipo == '+'){
                printf("Quadrante:{%d}{%d}-Tipo:%c Peca:[%d]-Saida:[%d]/ ",i,j,Mapa[i][j].Tipo,Mapa[i][j].Cruzamento.Peca,Mapa[i][j].Cruzamento.Saida);
                for (int k = 0; k < QUANTIDADECAMINHOSCRUZAMENTO; k++)
                    printf("Dir-[%d] Ace-[%d]/",Mapa[i][j].Cruzamento.CursoCrusamento[k].Caminho,Mapa[i][j].Cruzamento.CursoCrusamento[k].Acesso);
                printf("\n");
            }
            //Interrese
            else if (Mapa[i][j].Tipo == '#'){      
                printf("Quadrante:{%d}{%d}-Tipo:%c Peca:[%d]-Saida:[%d]/ ",i,j,Mapa[i][j].Tipo,Mapa[i][j].Interesse.Peca,Mapa[i][j].Interesse.Saida);  
                for (int k = 0; k < QUANTIDADECAMINHOSINTERESSE; k++)
                    printf("Dir-[%d] Ace-[%d]/",Mapa[i][j].Interesse.CursoInteresse[k].Caminho,Mapa[i][j].Interesse.CursoInteresse[k].Acesso);
                printf("\n");
            }
            //Nulo
            else
                printf("Quadrante{%d}{%d}-nulo\n",i,j);
        }
    }
    printf("\n");
}

void setQuadranteNula(quadrante* celula){
    celula->Nula.Caminho = Nulo;
}

void setQuadranteRua(quadrante* celula){
    switch (celula->Tipo)
    {
        case  '-':// Não foi implementado caso seja um beco sem saida e nao esteja nas bordas da matriz. Tanto pra esq e dir tem que ter um caminho valido
            celula->Rua.CursoRua[0].Caminho = Oeste;
            celula->Rua.CursoRua[0].Acesso = VERDADEIRO;
            celula->Rua.CursoRua[1].Caminho = Leste;
            celula->Rua.CursoRua[1].Acesso = VERDADEIRO;
            celula->Rua.Peca = FALSO;
            celula->Rua.Saida = FALSO;
            break;
        case '|'://Mesmo caso da outra nao pode estar na borda e os dois caminhos sao validos
            celula->Rua.CursoRua[0].Caminho = Norte;
            celula->Rua.CursoRua[0].Acesso = VERDADEIRO;
            celula->Rua.CursoRua[1].Caminho = Sul;
            celula->Rua.CursoRua[1].Acesso = VERDADEIRO;
            celula->Rua.Peca = FALSO;
            celula->Rua.Saida = FALSO;
            break;
    }

}

void setQuadranteCruzamento(quadrante **Mapa, int i, int j){
    switch (Mapa[i][j].Tipo)
    {
    case '+':  
        Mapa[i][j].Cruzamento.CursoCrusamento[0].Caminho = Norte;
        Mapa[i][j].Cruzamento.CursoCrusamento[1].Caminho = Sul;
        Mapa[i][j].Cruzamento.CursoCrusamento[2].Caminho = Leste;
        Mapa[i][j].Cruzamento.CursoCrusamento[3].Caminho = Oeste;
        Mapa[i][j].Cruzamento.Peca = FALSO;
        Mapa[i][j].Cruzamento.Saida = FALSO;

        if((i != 0 && i != LINHAS - 1) && (j != 0 && j != COLUNAS - 1)){//Nao for nas bordas
            //Norte
            if (Mapa[i - 1][j].Tipo != '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso = VERDADEIRO;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso = FALSO;
            //Sul    
            if (Mapa[i + 1][j].Tipo != '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso = VERDADEIRO;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso = FALSO;
            //Leste
            if (Mapa[i][j + 1].Tipo != '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso = VERDADEIRO;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso = FALSO;
            //Oeste
            if (Mapa[i][j - 1].Tipo != '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso = VERDADEIRO;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso = FALSO;
        }

        else if (i == 0){ // se for na borda de cima
            //Norte
            Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso = FALSO;

            //Sul    
            Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso = VERDADEIRO;
            
            //Leste    
            if (j == COLUNAS - 1 || Mapa[i][j + 1].Tipo == '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso = FALSO;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso = VERDADEIRO;

            //Oeste
            if (j == 0 || Mapa[i][j - 1].Tipo == '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso = FALSO;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso = VERDADEIRO;
        }

        else if (i == LINHAS - 1){ //se for na borda de baixo
            //Norte
            Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso = VERDADEIRO;

            //Sul
            Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso = FALSO;           

            //Leste
            if (j == COLUNAS - 1 || Mapa[i][j + 1].Tipo == '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso = FALSO;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso = VERDADEIRO;

            //Oeste
            if (j == 0 || Mapa[i][j - 1].Tipo == '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso = FALSO;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso = VERDADEIRO;
        }

        else if (j == COLUNAS - 1) { //se for na borda da direita
            //Norte
            if (i == 0 || Mapa[i - 1][j].Tipo == '0')
                Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso = FALSO;
            else 
                Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso = VERDADEIRO;
            
            //Sul
            if (i == LINHAS - 1 || Mapa[i + 1][j].Tipo == '0')
                Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso = FALSO;
            else 
                Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso = VERDADEIRO;
            
            //Leste
            Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso = FALSO;
            
            //Oeste
            Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso = VERDADEIRO;
        }

        else if (j == 0){// se for na borda da esquerda
            //Norte
            if (i == 0 || Mapa[i - 1][j].Tipo == '0')
                Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso = FALSO;
            else 
                Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso = VERDADEIRO;

            //Sul
            if (i == LINHAS - 1 || Mapa[i - 1][j].Tipo == '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso = FALSO;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso = VERDADEIRO;


            //Leste
            Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso = VERDADEIRO;

            //Oeste
            Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso = FALSO;
        }
        break;
    
    }
}

void setQuadranteDeInteresse(quadrante **Mapa, int i, int j){  
    /*Set das direçoes*/
    Mapa[i][j].Interesse.CursoInteresse[0].Caminho = Norte;
    Mapa[i][j].Interesse.CursoInteresse[1].Caminho = Sul;
    Mapa[i][j].Interesse.CursoInteresse[2].Caminho = Leste;
    Mapa[i][j].Interesse.CursoInteresse[3].Caminho = Oeste;

    /*Set de saida e se tem peça*/
    switch (Mapa[i][j].Tipo)
    {
    case 'F':
        Mapa[i][j].Interesse.Saida = VERDADEIRO;
        Mapa[i][j].Interesse.Peca = FALSO;
        break;
    case 'P':
        Mapa[i][j].Interesse.Saida = FALSO;
        Mapa[i][j].Interesse.Peca = VERDADEIRO;
        break;
    case 'X':
        Mapa[i][j].Interesse.Saida = FALSO;
        Mapa[i][j].Interesse.Peca = FALSO;
        break;
    }
    Mapa[i][j].Tipo = '#';

    /*Sets dos acessos*/

    /*Quando nao é um quadrante nas bordas*/
    Mapa[i][j].Interesse.CursoInteresse[0].Acesso = FALSO;
    Mapa[i][j].Interesse.CursoInteresse[1].Acesso = FALSO;
    Mapa[i][j].Interesse.CursoInteresse[2].Acesso = FALSO;
    Mapa[i][j].Interesse.CursoInteresse[3].Acesso = FALSO;

    if((i != 0 && i != LINHAS - 1) && (j != 0 && j != COLUNAS - 1)){
        //Norte
        if (Mapa[i - 1][j].Tipo != '.' &&  Mapa[i - 1][j].Tipo != '-')
            Mapa[i][j].Interesse.CursoInteresse[0].Acesso = VERDADEIRO;
        //Sul
        if (Mapa[i + 1][j].Tipo != '.' &&  Mapa[i + 1][j].Tipo != '-')
            Mapa[i][j].Interesse.CursoInteresse[1].Acesso = VERDADEIRO;
        //Leste
        if (Mapa[i][j + 1].Tipo != '.' &&  Mapa[i - 1][j].Tipo != '|')
            Mapa[i][j].Interesse.CursoInteresse[2].Acesso = VERDADEIRO;
        //Oeste
        if (Mapa[i][j - 1].Tipo != '.' &&  Mapa[i - 1][j].Tipo != '|')
            Mapa[i][j].Interesse.CursoInteresse[3].Acesso = VERDADEIRO;
    return;
    }

    /*Quando é um quadrante nas bordas*/
    Mapa[i][j].Interesse.CursoInteresse[0].Acesso = VERDADEIRO;
    Mapa[i][j].Interesse.CursoInteresse[1].Acesso = VERDADEIRO;
    Mapa[i][j].Interesse.CursoInteresse[2].Acesso = VERDADEIRO;
    Mapa[i][j].Interesse.CursoInteresse[3].Acesso = VERDADEIRO;
        
    //Norte
    if (i == 0 || (Mapa[i - 1][j].Tipo == '.' || Mapa[i - 1][j].Tipo == '-'))
        Mapa[i][j].Interesse.CursoInteresse[0].Acesso = FALSO;
    //Sul
    if (i == LINHAS - 1 || (Mapa[i + 1][j].Tipo == '.' || Mapa[i + 1][j].Tipo == '-'))
        Mapa[i][j].Interesse.CursoInteresse[1].Acesso = FALSO;
    //Leste
    if (j == COLUNAS - 1 || (Mapa[i][j + 1].Tipo == '.' || Mapa[i][j + 1].Tipo == '|'))
        Mapa[i][j].Interesse.CursoInteresse[2].Acesso = FALSO;
    //Oeste
    if (j == 0 || (Mapa[i][j - 1].Tipo == '.' || Mapa[i][j - 1].Tipo == '|'))
        Mapa[i][j].Interesse.CursoInteresse[3].Acesso = FALSO;
    
}

void setMapa(quadrante **Mapa,nave* Nave){
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++){
            switch (Mapa[i][j].Tipo)
            {
            case 'X':
                setQuadranteDeInteresse(Mapa,i,j);
                setNave(Nave,i,j);    
                break;            
            case 'P':
                setQuadranteDeInteresse(Mapa,i,j);
                break;
            case 'F':
                setQuadranteDeInteresse(Mapa,i,j);
                break;
            case '-':
                setQuadranteRua(&Mapa[i][j]);
                break;
            case '|':
                setQuadranteRua(&Mapa[i][j]);
                break;
            case '+':
                setQuadranteCruzamento(Mapa,i,j);
                break;
            default:
                setQuadranteNula(&Mapa[i][j]);
                break;
            }
        }
    }
}

int verificaQuadrante(quadrante* celula){
    switch (celula->Tipo)
    {
    case '-':
        return 1;
    case '|':
        return 1;
    case '+':
        return 2;    
    case '#':
        return 3;
    default:
        return -1;
        break;
    }
}

int inverteDirecao(direcao Direcao){
    switch (Direcao)
    {
    case Norte:
        return Sul;
    case Sul:
        return Norte;
    case Leste:
        return Oeste;
    case Oeste:
        return Leste;
    default:
        return Nulo;
        break;
    }
}