#ifndef NAVE_H_
#define NAVE_H_


#define TRUE 1
#define FALSE 0
#define QUANTIDADECAMINHOSRUA 2
#define QUANTIDADECAMINHOSCRUZAMENTO 4
#define QUANTIDADECAMINHOSESPECIAL 5
int LINHAS;
int COLUNAS;



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


#endif