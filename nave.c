#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "nave.h"

void imprimeNave(nave* Nave){
    printf("Nave - DUR: %d| DPS: %d| APP: %d| ",Nave->Durabilidade,Nave->DanoPorSetor,Nave->AumentoPorPeca);
    printf("QuantPe: %d| Coord: [%d][%d]| Consertado: %d| -\n",Nave->QuantidadePeca,Nave->PossicaoLinha,Nave->PossicaoColuna,Nave->Consertado);
}

void setNave(nave* Nave,int Linha,int Coluna){
    Nave->PossicaoLinha = Linha;
    Nave->PossicaoColuna = Coluna;
    Nave->QuantidadePeca = 0;
    Nave->Consertado = FALSE;
}

int verificaNave(nave* Nave){
    if (Nave->QuantidadePeca >= 4)
        Nave->Consertado = TRUE;
    if (Nave->Durabilidade < 1)
        return 0;
    return 1;
}
