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
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++){
            switch (Mapa[i][j].Tipo)
            {
            case 'X': 
                printf("[%d][%d] Tipo: %c/ Saida: %d/\n",i,j,Mapa[i][j].Tipo);
                break;            
            case 'P':
                printf("[%d][%d] Tipo: %c/\n",i,j,Mapa[i][j].Tipo);
                break;
            case 'F':
                printf("[%d][%d] Tipo: %c/\n",i,j,Mapa[i][j].Tipo);
                break;
            case '-':
                printf("[%d][%d] Tipo: %c/ Peca: %d/ Saida: %d/ Curso: [%d][%d] / [%d][%d]\n",i,j,Mapa[i][j].Tipo,Mapa[i][j].Rua.Peca,Mapa[i][j].Rua.Saida,Mapa[i][j].Rua.CursoRua[0].Caminho,Mapa[i][j].Rua.CursoRua[0].Acesso,Mapa[i][j].Rua.CursoRua[1].Caminho,Mapa[i][j].Rua.CursoRua[1].Acesso);
                break;
            case '|':
                printf("[%d][%d] Tipo: %c/ Peca: %d/ Saida: %d/ Curso: [%d][%d] / [%d][%d]\n",i,j,Mapa[i][j].Tipo,Mapa[i][j].Rua.Peca,Mapa[i][j].Rua.Saida,Mapa[i][j].Rua.CursoRua[0].Caminho,Mapa[i][j].Rua.CursoRua[0].Acesso,Mapa[i][j].Rua.CursoRua[1].Caminho,Mapa[i][j].Rua.CursoRua[1].Acesso);
                break;
            case '+':
                printf("[%d][%d] Tipo: %c/ Peca: %d/ Saida: %d/\n",i,j,Mapa[i][j].Tipo,Mapa[i][j].Cruzamento.Peca,Mapa[i][j].Cruzamento.Saida);
                printf("Curso: [%d][%d] / [%d][%d] | [%d][%d] | [%d][%d]\n",Mapa[i][j].Cruzamento.CursoCrusamento[0].Caminho,Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso,Mapa[i][j].Cruzamento.CursoCrusamento[1].Caminho,Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso,Mapa[i][j].Cruzamento.CursoCrusamento[2].Caminho,Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso,Mapa[i][j].Cruzamento.CursoCrusamento[3].Caminho,Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso);
                break;
            case '.':
                printf("[%d][%d] Tipo: %c/ Direcao: %d/\n ",i,j,Mapa[i][j].Tipo,Mapa[i][j].Nula.Caminho);
                break;
            default:
                break;
            }
        }
    }
}


void setQuadranteNula(quadrante* celula){
    celula->Nula.Caminho = Nulo;
}

void setQuadranteRua(quadrante* celula,int i, int j){
    switch (celula->Tipo)
    {
        case  '-':// Não foi implementado caso seja um beco sem saida e nao esteja nas bordas da matriz. Tanto pra esq e dir tem que ter um caminho valido
            celula->Rua.CursoRua[0].Caminho = Oeste;
            celula->Rua.CursoRua[0].Acesso = TRUE;
            celula->Rua.CursoRua[1].Caminho = Leste;
            celula->Rua.CursoRua[1].Acesso = TRUE;
            break;
        case '|'://Mesmo caso da outra nao pode estar na borda e os dois caminhos sao validos
            celula->Rua.CursoRua[0].Caminho = Norte;
            celula->Rua.CursoRua[0].Acesso = TRUE;
            celula->Rua.CursoRua[1].Caminho = Sul;
            celula->Rua.CursoRua[1].Acesso = TRUE;
            break;
        default:
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

        if((i != 0 && i != LINHAS - 1) && (j != 0 && j != COLUNAS - 1)){//Nao for nas bordas
            //Norte
            if (Mapa[i - 1][j].Tipo != '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso = TRUE;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso = FALSE;
            //Sul    
            if (Mapa[i + 1][j].Tipo != '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso = TRUE;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso = FALSE;
            //Leste
            if (Mapa[i][j + 1].Tipo != '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso = TRUE;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso = FALSE;
            //Oeste
            if (Mapa[i][j - 1].Tipo != '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso = TRUE;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso = FALSE;
        }

        else if (i == 0){ // se for na borda de cima
            //Norte
            Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso = FALSE;

            //Sul    
            Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso = TRUE;
            
            //Leste    
            if (j == COLUNAS - 1 || Mapa[i][j + 1].Tipo == '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso = FALSE;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso = TRUE;

            //Oeste
            if (j == 0 || Mapa[i][j - 1].Tipo == '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso = FALSE;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso = TRUE;
        }

        else if (i == LINHAS - 1){ //se for na borda de baixo
            //Norte
            Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso = TRUE;

            //Sul
            Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso = FALSE;           

            //Leste
            if (j == COLUNAS - 1 || Mapa[i][j + 1].Tipo == '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso = FALSE;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso = TRUE;

            //Oeste
            if (j == 0 || Mapa[i][j - 1].Tipo == '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso = FALSE;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso = TRUE;
        }

        else if (j == COLUNAS - 1) { //se for na borda da direita
            //Norte
            if (i == 0 || Mapa[i - 1][j].Tipo == '0')
                Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso = FALSE;
            else 
                Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso = TRUE;
            
            //Sul
            if (i == LINHAS - 1 || Mapa[i + 1][j].Tipo == '0')
                Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso = FALSE;
            else 
                Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso = TRUE;
            
            //Leste
            Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso = FALSE;
            
            //Oeste
            Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso = TRUE;
        }

        else if (j == 0){// se for na borda da esquerda
            //Norte
            if (i == 0 || Mapa[i - 1][j].Tipo == '0')
                Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso = FALSE;
            else 
                Mapa[i][j].Cruzamento.CursoCrusamento[0].Acesso = TRUE;

            //Sul
            if (i == LINHAS - 1 || Mapa[i - 1][j].Tipo == '.')
                Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso = FALSE;
            else
                Mapa[i][j].Cruzamento.CursoCrusamento[1].Acesso = TRUE;


            //Leste
            Mapa[i][j].Cruzamento.CursoCrusamento[2].Acesso = TRUE;

            //Oeste
            Mapa[i][j].Cruzamento.CursoCrusamento[3].Acesso = FALSE;
        }
        break;
    
    default:
        break;
    }
}

void setQuadranteDeInteresse(quadrante **Mapa, int i, int j){  
    int count = 0;
    char AuxTipo = Mapa[i][j].Tipo;
    if((i != 0 && i != LINHAS - 1) && (j != 0 && j != COLUNAS - 1)){//Nao for nas bordas
        for (int k = -1; k < 2; k++){//Conta quantos caminhos tem em volta de um quadrante
            for (int t = -1; t < 2; t++){
                if ((k + t == 1 || k + t == -1) && Mapa[i + k][j + t].Tipo != '.'){
                    count++;
                }
            }
        }
        if (count == 2){//pode ser uma rua ou "curva"
            if (Mapa[i - 1][j].Tipo != '.' && Mapa[i + 1][j].Tipo != '.'){
                Mapa[i][j].Tipo = '|';
                setQuadranteRua(&Mapa[i][j],i,j);
                if (AuxTipo == 'P'){
                    Mapa[i][j].Rua.Peca = TRUE;
                    Mapa[i][j].Rua.Saida = FALSE;
                }
                else if (AuxTipo == 'F'){
                    Mapa[i][j].Rua.Saida = TRUE;
                    Mapa[i][j].Rua.Peca = FALSE;
                }
                else if (AuxTipo == 'X'){
                    Mapa[i][j].Rua.Peca = FALSE;
                    Mapa[i][j].Rua.Saida = FALSE;
                }
            }
            else if (Mapa[i][j + 1].Tipo != '.' && Mapa[i][j - 1].Tipo != '.'){
                Mapa[i][j].Tipo = '-';
                setQuadranteRua(&Mapa[i][j],i,j);
                if (AuxTipo == 'P'){
                    Mapa[i][j].Rua.Peca = TRUE;
                    Mapa[i][j].Rua.Saida = FALSE;
                }
                else if (AuxTipo == 'F'){
                    Mapa[i][j].Rua.Saida = TRUE;
                    Mapa[i][j].Rua.Peca = FALSE;
                }
                else if (AuxTipo == 'X'){
                    Mapa[i][j].Rua.Peca = FALSE;
                    Mapa[i][j].Rua.Saida = FALSE;
                }
            }
            
            if (((Mapa[i - 1][j].Tipo == '.' || Mapa[i + 1][j].Tipo == '.') && (Mapa[i - 1][j].Tipo != Mapa[i + 1][j].Tipo)) ||
                ((Mapa[i][j - 1].Tipo == '.' || Mapa[i][j + 1].Tipo == '.') && (Mapa[i][j - 1].Tipo != Mapa[i][j + 1].Tipo)))
            {    
                Mapa[i][j].Tipo = '+';
                setQuadranteCruzamento(Mapa,i,j);
                if (AuxTipo == 'P'){
                    Mapa[i][j].Cruzamento.Peca = TRUE;
                    Mapa[i][j].Cruzamento.Saida = FALSE;
                } 
                else if (AuxTipo == 'F'){
                    Mapa[i][j].Cruzamento.Saida = TRUE;
                    Mapa[i][j].Cruzamento.Peca = FALSE;
                }
                else if (AuxTipo == 'X'){
                    Mapa[i][j].Cruzamento.Peca = FALSE;
                    Mapa[i][j].Cruzamento.Saida = FALSE;
                }
            }
             
        }
        else if (count == 3 || count == 4){
            Mapa[i][j].Tipo = '+';
            setQuadranteCruzamento(Mapa,i,j);
            if (AuxTipo == 'P'){
                Mapa[i][j].Cruzamento.Peca = TRUE;
                Mapa[i][j].Cruzamento.Saida = FALSE;
            } 
            else if (AuxTipo == 'F'){
                Mapa[i][j].Cruzamento.Saida = TRUE;
                Mapa[i][j].Cruzamento.Peca = FALSE;
            }
            else if (AuxTipo == 'X'){
                Mapa[i][j].Cruzamento.Peca = FALSE;
                Mapa[i][j].Cruzamento.Saida = FALSE;
            }
        }
    }   

    else if (((i == 0 && j == 0) || (i == 0 && j == COLUNAS - 1)) || ((i == LINHAS - 1 && j == 0) || (i == LINHAS - 1 && j == COLUNAS - 1))){
        //Se estao nas quinas da matriz é um Cruzamento
        Mapa[i][j].Tipo = '+';
        setQuadranteCruzamento(Mapa,i,j);
        if (AuxTipo == 'P'){
            Mapa[i][j].Cruzamento.Peca = TRUE;
            Mapa[i][j].Cruzamento.Saida = FALSE;
        } 
        else if (AuxTipo == 'F'){
            Mapa[i][j].Cruzamento.Saida = TRUE;
            Mapa[i][j].Cruzamento.Peca = FALSE;
        }
        else if (AuxTipo == 'X'){
            Mapa[i][j].Cruzamento.Peca = FALSE;
            Mapa[i][j].Cruzamento.Saida = FALSE;
        }
    }

    else{//se estao nas boras da matriz
        //caso seja um cruzamento +
        if ((i == 0 && Mapa[i + 1][j].Tipo != '.') || (i == LINHAS - 1 && Mapa[i - 1][j].Tipo !='.')){
            Mapa[i][j].Tipo = '+';
            setQuadranteCruzamento(Mapa,i,j);
            if (AuxTipo == 'P'){
                Mapa[i][j].Cruzamento.Peca = TRUE;
                Mapa[i][j].Cruzamento.Saida = FALSE;
            } 
            else if (AuxTipo == 'F'){
                Mapa[i][j].Cruzamento.Saida = TRUE;
                Mapa[i][j].Cruzamento.Peca = FALSE;
            }
            else if (AuxTipo == 'X'){
                Mapa[i][j].Cruzamento.Peca = FALSE;
                Mapa[i][j].Cruzamento.Saida = FALSE;
            }
        }
        else if ((i == 0 && Mapa[i + 1][j].Tipo == '.') || (i == LINHAS - 1 && Mapa[i - 1][j].Tipo =='.')){
            Mapa[i][j].Tipo = '|';
            setQuadranteRua(&Mapa[i][j],i,j);
            if (AuxTipo == 'P'){
                Mapa[i][j].Rua.Peca = TRUE;
                Mapa[i][j].Rua.Saida = FALSE;
            }
            else if (AuxTipo == 'F'){
                Mapa[i][j].Rua.Saida = TRUE;
                Mapa[i][j].Rua.Peca = FALSE;
            }
            else if (AuxTipo == 'X'){
                Mapa[i][j].Rua.Peca = FALSE;
                Mapa[i][j].Rua.Saida = FALSE;
            }
        }

        //caso seja um cruzamento +
        else if ((j == 0 && Mapa[i][j + 1].Tipo != '.') || (j == COLUNAS - 1 && Mapa[i][j - 1].Tipo != '.')){
            Mapa[i][j].Tipo = '+';
            setQuadranteCruzamento(Mapa,i,j);
            if (AuxTipo == 'P'){
                Mapa[i][j].Cruzamento.Peca = TRUE;
                Mapa[i][j].Cruzamento.Saida = FALSE;
            } 
            else if (AuxTipo == 'F'){
                Mapa[i][j].Cruzamento.Saida = TRUE;
                Mapa[i][j].Cruzamento.Peca = FALSE;
            }
            else if (AuxTipo == 'X'){
                Mapa[i][j].Cruzamento.Peca = FALSE;
                Mapa[i][j].Cruzamento.Saida = FALSE;
            }
        }
        else if ((j == 0 && Mapa[i][j + 1].Tipo == '.') || (j == COLUNAS - 1 && Mapa[i][j - 1].Tipo == '.')){
            Mapa[i][j].Tipo = '-';
            setQuadranteRua(&Mapa[i][j],i,j);
            if (AuxTipo == 'P'){
                Mapa[i][j].Rua.Peca = TRUE;
                Mapa[i][j].Rua.Saida = FALSE;
            }
            else if (AuxTipo == 'F'){
                Mapa[i][j].Rua.Saida = TRUE;
                Mapa[i][j].Rua.Peca = FALSE;
            }
            else if (AuxTipo == 'X'){
                Mapa[i][j].Rua.Peca = FALSE;
                Mapa[i][j].Rua.Saida = FALSE;
            }
        }

    }
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
                setQuadranteRua(&Mapa[i][j],i,j);
                Mapa[i][j].Rua.Peca = FALSE;
                Mapa[i][j].Rua.Saida = FALSE;
                break;
            case '|':
                setQuadranteRua(&Mapa[i][j],i,j);
                Mapa[i][j].Rua.Peca = FALSE;
                Mapa[i][j].Rua.Saida = FALSE;
                break;
            case '+':
                setQuadranteCruzamento(Mapa,i,j);
                Mapa[i][j].Cruzamento.Peca = FALSE;
                Mapa[i][j].Cruzamento.Saida = FALSE;
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