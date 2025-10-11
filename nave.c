#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "nave.h"

void imprimeNave(nave* Nave){
    printf("Durabilidade: %d| DanoPorSetor: %d| AumentoPorPeca: %d|\n",Nave->Durabilidade,Nave->DanoPorSetor,Nave->AumentoPorPeca);
    printf("QuantidadePeca: %d| Coordenadas: [%d][%d]| Consertado: %d|\n",Nave->QuantidadePeca,Nave->PossicaoLinha,Nave->PossicaoColuna,Nave->Consertado);
}

void setNave(nave* Nave,int Linha,int Coluna){
    Nave->PossicaoLinha = Linha;
    Nave->PossicaoColuna = Coluna;
    Nave->QuantidadePeca = 0;
    Nave->Consertado = FALSE;
}