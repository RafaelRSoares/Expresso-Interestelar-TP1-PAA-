#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gerarMapa();

int gerarNumeroAleatorio(int limite);

void gerarCaminhos(int altura, int largura, char mapa[altura][largura], int xInicial, int yInicial, int xFinal, int yFinal);

void ajustarCruzamentos(int altura, int largura, char mapa[altura][largura]);
