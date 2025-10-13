#include "backtracking.h"
//modo analise
#ifdef ANALISE
int totalChamadas = 0;
int nivelMaximo = 0;
#endif


void atualizaNave(nave* Nave, Informacoes* infos){
    Nave->PossicaoLinha = infos->Linha;
    Nave->PossicaoColuna = infos->Coluna;
    Nave->Durabilidade = infos->Durabilidade;
    Nave->QuantidadePeca = infos->PecasRestantes;
}

int percorreRua(quadrante Mapa[][COLUNAS],quadrante* celula,nave* Nave,Percurso* lista,direcao DirecaoAnterior){
    printf("Chamanda Rua\n");
    /*Caso de sucesso */
    if (celula->Rua.Saida == TRUE){//retorna 0 se achou a saida
        return 0;
    }

    if (celula->Rua.Peca == TRUE){
        Nave->Durabilidade += Nave->AumentoPorPeca;
        Nave->QuantidadePeca++;
    }
    
    if (DirecaoAnterior != Nulo && celula->Rua.Peca == FALSE){//Pelo visto quando acha a peça nao perde vida
        Nave->Durabilidade -= Nave->DanoPorSetor;
    }
    /*1° Caso de falha */
    if (verificaNave(Nave) == 0){//Nave nao tem durabilidade
        // printf("Nave Quebrou [%d][%d]\n",Nave->PossicaoLinha,Nave->PossicaoColuna);
        atualizaNave(Nave,lista->Ultimo);
        RemoverUlitmoPercruso(lista);
        // Desfazer o caminho
        return 1;
    }
    
    /*Pecorre os caminho possiveis pela rua*/
    for (int i = 0; i < QUANTIDADECAMINHOSRUA; i++){
        //se pode acessar aquele caimnho chama de novo
        //Mecher dentro desse if caso a vida da nave nao conte
        if (celula->Rua.CursoRua[i].Caminho != DirecaoAnterior && celula->Rua.CursoRua[i].Acesso == TRUE){
            if (Nave->Consertado == TRUE)
                celula->Rua.CursoRua[i].Acesso == FALSE;
            //se o proximo caminho retorna 0 achou a saida e vai retornando ai 
            inserePercurso(lista,Nave->PossicaoLinha,Nave->PossicaoColuna,Nave->Durabilidade,Nave->QuantidadePeca,Nave->Consertado);
            printf("No for [%d][%d]\n",celula->Rua.CursoRua[i].Caminho,celula->Rua.CursoRua[i].Acesso);
            if (movimentar(Mapa,Nave,lista,inverteDirecao(celula->Rua.CursoRua[i].Caminho)) == 0)
                return 0;
            // se nao achou a saida tenta outro caminho 
            atualizaNave(Nave,lista->Ultimo);
            RemoverUlitmoPercruso(lista);    
        }

    }
    /*2° Caso de falha */
    //Nao tem caminhos percorriveis
    atualizaNave(Nave,lista->Ultimo);
    RemoverUlitmoPercruso(lista);    
    return 1;
    
}

int percorreCruzamento(quadrante Mapa[][COLUNAS],quadrante* celula,nave* Nave,Percurso* lista,direcao DirecaoAnterior){
    printf("Chamanda Cruzamento\n");
    /*Caso de sucesso */
    if (celula->Cruzamento.Saida == TRUE){//retorna 0 se achou a saida
        return 0;
    }

    if (celula->Cruzamento.Peca == TRUE){
        Nave->Durabilidade += Nave->AumentoPorPeca;
        Nave->QuantidadePeca++;
    }
    
    if (DirecaoAnterior != Nulo && celula->Cruzamento.Peca == FALSE){//Pelo visto quando acha a peça nao perde vida
        Nave->Durabilidade -= Nave->DanoPorSetor;
    }
    /*1° Caso de falha */
    if (verificaNave(Nave) == 0){//Nave nao tem durabilidade
        printf("Nave Quebrou [%d][%d]\n",Nave->PossicaoLinha,Nave->PossicaoColuna);
        atualizaNave(Nave,lista->Ultimo);
        RemoverUlitmoPercruso(lista);
        // Desfazer o caminho
        return 1;
    }


    for (int i = 0; i < QUANTIDADECAMINHOSCRUZAMENTO; i++){
        //se pode acessar aquele caimnho chama de novo
        //Mecher dentro desse if caso a vida da nave nao conte
        if (celula->Cruzamento.CursoCrusamento[i].Caminho != DirecaoAnterior && celula->Cruzamento.CursoCrusamento[i].Acesso == TRUE){
            if (Nave->Consertado == TRUE)
                celula->Cruzamento.CursoCrusamento[i].Acesso == FALSE;
            //se o proximo caminho retorna 0 achou a saida e vai retornando ai 
            
            inserePercurso(lista,Nave->PossicaoLinha,Nave->PossicaoColuna,Nave->Durabilidade,Nave->QuantidadePeca,Nave->Consertado);
            
            printf("No for [%d][%d]\n",celula->Cruzamento.CursoCrusamento[i].Caminho,celula->Cruzamento.CursoCrusamento[i].Acesso);
            if (movimentar(Mapa,Nave,lista,inverteDirecao(celula->Cruzamento.CursoCrusamento[i].Caminho)) == 0)
                return 0;
            // se nao achou a saida tenta outro caminho 
            atualizaNave(Nave,lista->Ultimo);
            RemoverUlitmoPercruso(lista);    
        }

    }
    /*2° Caso de falha */
    //Nao tem caminhos percorriveis
    atualizaNave(Nave,lista->Ultimo);
    RemoverUlitmoPercruso(lista);    
    return 1;


}

int movimentar(quadrante Mapa[][COLUNAS], nave* Nave,Percurso* lista,direcao DirecaoAnterior){
    printf("Chamanda movimentar\n");
    printf("Nave\n");
    imprimeNave(Nave);

//modo analise
#ifdef ANALISE
    static int nivelAtual = 0;
    totalChamadas++;
    nivelAtual++;
    if (nivelAtual > nivelMaximo)
        nivelMaximo = nivelAtual;
#endif

    /*Modifica a possicao da nave*/
    switch (DirecaoAnterior)
    {
    case Norte:
        //printf("norte\n");
        Nave->PossicaoLinha++;
        break;
    case Sul:
        //printf("sul\n");
        Nave->PossicaoLinha--;
        break;
    case Leste:
        //printf("leste\n");
        Nave->PossicaoColuna--;
        break;
    case Oeste:
        //printf("oeste\n");
        Nave->PossicaoColuna++;
        break;
    }

    inserePercurso(lista,Nave->PossicaoLinha,Nave->PossicaoColuna,Nave->Durabilidade,Nave->QuantidadePeca,Nave->Consertado);
    printf("Lista\n");
    imprimirLista(lista);
    
    int LinhaNave = Nave->PossicaoLinha;
    int ColunaNave = Nave->PossicaoColuna;
    printf("LinNave %d ColNave %d\n",LinhaNave,ColunaNave);
    /*verifica que tipo de quadrante ele esta*/
     int resultado;

    switch (verificaQuadrante(&Mapa[LinhaNave][ColunaNave]))
    {
    case 1:
        resultado = percorreRua(Mapa, &Mapa[LinhaNave][ColunaNave], Nave, lista, DirecaoAnterior);
        break;
    case 2:
        resultado = percorreCruzamento(Mapa, &Mapa[LinhaNave][ColunaNave], Nave, lista, DirecaoAnterior);
        break;
    default:
        resultado = 1;
        break;
    }

#ifdef ANALISE
    nivelAtual--;
#endif

    return resultado;
}