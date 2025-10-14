#ifndef BACKTRACKING_H_
#define BACKTRACKING_H_

#include "mapa.h"
#include "lista.h"

int movimentar(quadrante **Mapa, nave* Nave,Percurso* lista,direcao DirecaoAnterior);

void atualizaNave(nave* Nave, Informacoes* infos);

int percorreRua(quadrante **Mapa, quadrante* celula,nave* Nave,Percurso* lista,direcao DirecaoAnterior);

int percorreCruzamento(quadrante **Mapa, quadrante* celula,nave* Nave,Percurso* lista,direcao DirecaoAnterior);





//return 0 achou a saida
//return 1 deu ruim



#endif