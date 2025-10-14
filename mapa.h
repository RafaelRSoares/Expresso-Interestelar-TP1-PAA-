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
            curso CaminhosEspecial[QUANTIDADECAMINHOSESPECIAL];
            short Peca;
            short Saida;
        }Especial;
        
    };
} quadrante;


void imprimeMapa(quadrante **Mapa);
void imprimeMapaAdm(quadrante **Mapa);

void setQuadranteNula(quadrante* celula);
void setQuadranteRua(quadrante* celula, int i, int j);
void setQuadranteCruzamento(quadrante **Mapa, int i, int j);
void setQuadranteDeInteresse(quadrante **Mapa, int i, int j); 

void setMapa(quadrante **Mapa, nave* Nave);

int inverteDirecao(direcao Direcao);

int verificaQuadrante(quadrante* celula);
//return -1 é ripo nulo
// return 1 é tipo rua
//return 2 é tipo cruzamento

#endif