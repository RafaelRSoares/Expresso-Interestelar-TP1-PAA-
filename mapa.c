#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mapa.h"

void imprimeMapa(quadrante Mapa[][COLUNAS]){
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++)
            printf("%c",Mapa[i][j].Tipo);  
        printf("\n");
    }
}
void imprimeMapaAdm(quadrante Mapa[][COLUNAS]){
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++){
            switch (Mapa[i][j].Tipo)
            {
            case 'X':    
                printf("%c",Mapa[i][j].Tipo);                    
                break;            
            case 'P':
                printf("%c",Mapa[i][j].Tipo);    
                break;
            case 'F':
                printf("%c",Mapa[i][j].Tipo);    
                break;
            case '-':
                printf("%c",Mapa[i][j].Tipo);            
                break;
            case '|':
                printf("%c",Mapa[i][j].Tipo);    
                break;
            case '+':
                printf("%c",Mapa[i][j].Tipo);    
                break;
            case '.':
                printf("%d",Mapa[i][j].Nula.Caminho);
                break;
            default:
                printf("%c",Mapa[i][j].Tipo);    
                break;
            }
        }
        printf("\n");
    }
}

void setQuadranteNula(quadrante* celula){
    celula->Nula.Caminho = Nulo;
}

void setQuadranteRua(quadrante* celula,int i, int j){
    switch (celula->Tipo)
    {
        case  '-':// Não foi implementado caso seja um beco sem saida e nao esteja nas bordas da matriz. Tanto pra esq e dir tem que ter um caminho valido
            celula->Rua.Peca = FALSE;
            celula->Rua.Saida = FALSE;
            celula->Rua.CursoRua[0].Caminho = Oeste;
            celula->Rua.CursoRua[0].Acesso = TRUE;
            celula->Rua.CursoRua[1].Caminho = Leste;
            celula->Rua.CursoRua[1].Acesso = TRUE;
            break;
        case '|'://Mesmo caso da outra nao pode estar na borda e os dois caminhos sao validos
            celula->Rua.Peca = FALSE;
            celula->Rua.Saida = FALSE;
            celula->Rua.CursoRua[0].Caminho = Norte;
            celula->Rua.CursoRua[0].Acesso = TRUE;
            celula->Rua.CursoRua[1].Caminho = Sul;
            celula->Rua.CursoRua[1].Acesso = TRUE;
            break;
        default:
            break;
    }

}

void setMapa(quadrante Mapa[][COLUNAS],nave* Nave){
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++){
            switch (Mapa[i][j].Tipo)
            {
            case 'X':
                printf("X\n");
                setNave(Nave,i,j);    
                break;            
            case 'P':
                printf("P\n");
                break;
            case 'F':
                printf("F\n");
                break;
            case '-':
                printf("-\n");
                setQuadranteRua(&Mapa[j][i],i,j);
                break;
            case '|':
                printf("|\n");
                setQuadranteRua(&Mapa[j][i],i,j);
                break;
            case '+':
                printf("+\n");
                break;
            default:
                printf(".\n");
                setQuadranteNula(&Mapa[i][j]);
                break;
            }
        }
    }
}