#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gerarMapa();

char* gerarMapaUI(int escolha, int escolha3);

char* gerarMapaUI2(int altura,  int largura, int pecas, int durabilidade, int movimentacao, int aumento, int escolha3);

int gerarNumeroAleatorio(int limite);

void gerarCaminhos(int altura, int largura, char mapa[altura][largura], int xInicial, int yInicial, int xFinal, int yFinal);

void ajustarCruzamentos(int altura, int largura, char mapa[altura][largura]);
