#ifndef BACKTRACKING_H_
#define BACKTRACKING_H_

#include "mapa.h"
#include "lista.h"

/*Variáveis compartilhadas com a main. nunca usei extern antes, mas aparentmente funciona como se fosse
um ponteiro para uma variável definida em outro arquivo. Realmente não sei se está certo, mas funciona*/
extern int totalChamadas;
extern int nivelMaximo;
extern int modoAnaliseAtivo;


int movimentar(quadrante **Mapa, nave* Nave,Percurso* lista,direcao DirecaoAnterior);

void atualizaNave(nave* Nave, Informacoes* infos);

int percorreRua(quadrante **Mapa, quadrante* celula,nave* Nave,Percurso* lista,direcao DirecaoAnterior);

int percorreCruzamento(quadrante **Mapa, quadrante* celula,nave* Nave,Percurso* lista,direcao DirecaoAnterior);

int percorreInteresse(quadrante **Mapa, quadrante* celula,nave* Nave,Percurso* lista,direcao DirecaoAnterior);


#endif