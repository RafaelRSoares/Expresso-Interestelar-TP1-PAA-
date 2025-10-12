#ifndef BACKTRACKING_H_
#define BACKTRACKING_H_

#include "mapa.h"
#include "lista.h"

int movimentar(quadrante Mapa[][COLUNAS], nave* Nave,Percurso* lista,direcao DirecaoAnterior);

int verificaQuadrante();

void atualizaNave(nave* Nave, Informacoes* infos);

int percorreRua(quadrante Mapa[][COLUNAS],quadrante* celula,nave* Nave,Percurso* lista,direcao DirecaoAnterior);

int percorreCruzamento(quadrante Mapa[][COLUNAS],quadrante* celula,nave* Nave,Percurso* lista,direcao DirecaoAnterior);





//return 0 achou a saida
//return 1 deu ruim



#endif