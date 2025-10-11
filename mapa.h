#ifndef MAPA_H_
#define MAPA_H_

#include "nave.h"

typedef enum  {
    Nulo = 0,
    Norte = 1,
    Sul = 2,
    Leste = 3,
    Oeste = 4
}direcao; // Caso a direção seja 0 o caminho nao esta disponivel para passar


typedef struct {
    direcao Caminho;
    short Acesso;
}curso;

typedef struct {
    char Tipo;
    union {       
        struct {
           direcao Caminho; 
        }Nula;
        
        struct {
            curso CursoRua[QUANTIDADECAMINHOSRUA];
            short Peca;
            short Saida;
        }Rua;
        
        struct {
            curso Caminhos[QUANTIDADECAMINHOSCRUZAMENTO];
            short Peca;
            short Saida;
        }Cruzamento;
        
        struct {
            curso Caminhos[QUANTIDADECAMINHOSESPECIAL];
            short Peca;
            short Saida;
        }Especial;
        
    };
} quadrante;

void imprimeMapa(quadrante Mapa[][COLUNAS]);
void imprimeMapaAdm(quadrante Mapa[][COLUNAS]);

void setQuadranteNula(quadrante* celula);
void setQuadranteRua(quadrante* celula, int i, int j);
void setQuadranteCruzamento(quadrante Mapa[][COLUNAS], int i, int j);


void setMapa(quadrante Mapa[][COLUNAS], nave* Nave);



#endif