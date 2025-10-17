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
            curso CursoCrusamento[QUANTIDADECAMINHOSCRUZAMENTO];
            short Peca;
            short Saida;
        }Cruzamento;
        
        struct {
            curso CursoInteresse[QUANTIDADECAMINHOSINTERESSE];
            short Peca;
            short Saida;
        }Interesse;

        struct {
            curso CaminhosEspecial[QUANTIDADECAMINHOSESPECIAL];
            short Peca;
            short Saida;
        }Especial;
        
    };
} quadrante;


void imprimeMapa(quadrante **Mapa);
void imprimeMapaAdm(quadrante **Mapa);

int verificaQuadrante(quadrante* celula);
int inverteDirecao(direcao Direcao);

void setQuadranteNula(quadrante* celula);
void setQuadranteRua(quadrante* celula);
void setQuadranteCruzamento(quadrante **Mapa, int i, int j);
void setQuadranteDeInteresse(quadrante **Mapa, int i, int j); 

void setMapa(quadrante **Mapa, nave* Nave);

#endif