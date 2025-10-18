#ifndef NAVE_H_
#define NAVE_H_

#define VERDADEIRO 1
#define FALSO 0
#define QUANTIDADECAMINHOSRUA 2
#define QUANTIDADECAMINHOSCRUZAMENTO 4
#define QUANTIDADECAMINHOSINTERESSE 4
#define QUANTIDADECAMINHOSESPECIAL 4


extern int LINHAS;
extern int COLUNAS;

typedef struct {
    int Durabilidade;
    int DanoPorSetor;
    int AumentoPorPeca;

    int QuantidadePeca;
    int PossicaoLinha;
    int PossicaoColuna;
    short Consertado;
    
} nave;

void imprimeNave(nave* Nave);

void setNave(nave* Nave,int Linha,int Coluna);

int verificaNave(nave* Nave);

#endif

