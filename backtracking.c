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
    Nave->QuantidadePeca = infos->PecasColetadas;
}

int percorreRua(quadrante **Mapa,quadrante* celula,nave* Nave,Percurso* lista,direcao DirecaoAnterior){
    /*Caso de sucesso */
    //NÃO APAGAR - PEDRO
    // if (celula->Rua.Saida == VERDADEIRO){//retorna 0 se achou a saida
    //     return 0;
    // }

    // if (celula->Rua.Peca == VERDADEIRO){
    //     Nave->Durabilidade += Nave->AumentoPorPeca;
    //     Nave->QuantidadePeca++;
    //     celula->Rua.Peca = FALSO;
    // }
    
    if (DirecaoAnterior != Nulo && celula->Rua.Peca == FALSO){//Pelo visto quando acha a peça nao perde vida
        Nave->Durabilidade -= Nave->DanoPorSetor;
    }
    /*1° Caso de falha */
    if (verificaNave(Nave) == 0){//Nave nao tem durabilidade
        atualizaNave(Nave,lista->Ultimo);
        RemoverUlitmoPercruso(lista);
        // Desfazer o caminho
        return 1;
    }
    
    /*Pecorre os caminho possiveis pela rua*/
    for (int i = 0; i < QUANTIDADECAMINHOSRUA; i++){
        //se pode acessar aquele caimnho chama de novo
        //Mecher dentro desse if caso a vida da nave nao conte
        if (celula->Rua.CursoRua[i].Caminho != DirecaoAnterior && celula->Rua.CursoRua[i].Acesso == VERDADEIRO){
            if (Nave->Consertado == VERDADEIRO)
                celula->Rua.CursoRua[i].Acesso == FALSO;
            //se o proximo caminho retorna 0 achou a saida e vai retornando ai 
           
            inserePercurso(lista,Nave->PossicaoLinha,Nave->PossicaoColuna,Nave->Durabilidade,Nave->QuantidadePeca,Nave->Consertado);
           
            if (!movimentar(Mapa,Nave,lista,inverteDirecao(celula->Rua.CursoRua[i].Caminho))){
                return 0;
            }
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

int percorreCruzamento(quadrante **Mapa ,quadrante* celula,nave* Nave,Percurso* lista,direcao DirecaoAnterior){
    /*Caso de sucesso */
    //NÃO APAGAR - PEDRO
    // if (celula->Cruzamento.Saida == VERDADEIRO){//retorna 0 se achou a saida
    //     return 0;
    // }

    // if (celula->Cruzamento.Peca == VERDADEIRO){
    //     Nave->Durabilidade += Nave->AumentoPorPeca;
    //     Nave->QuantidadePeca++;
    //     celula->Cruzamento.Peca = FALSO;
    // }
    
    if (DirecaoAnterior != Nulo && celula->Cruzamento.Peca == FALSO){//Pelo visto quando acha a peça nao perde vida
        Nave->Durabilidade -= Nave->DanoPorSetor;
    }
    /*1° Caso de falha */
    if (verificaNave(Nave) == 0){//Nave nao tem durabilidade
        atualizaNave(Nave,lista->Ultimo);
        RemoverUlitmoPercruso(lista);
        // Desfazer o caminho
        return 1;
    }


    for (int i = 0; i < QUANTIDADECAMINHOSCRUZAMENTO; i++){
        //se pode acessar aquele caimnho chama de novo
        //Mecher dentro desse if caso a vida da nave nao conte
        if (celula->Cruzamento.CursoCrusamento[i].Caminho != DirecaoAnterior && celula->Cruzamento.CursoCrusamento[i].Acesso == VERDADEIRO){
            if (Nave->Consertado == VERDADEIRO)
                celula->Cruzamento.CursoCrusamento[i].Acesso == FALSO;
            //se o proximo caminho retorna 0 achou a saida e vai retornando ai 
            
            inserePercurso(lista,Nave->PossicaoLinha,Nave->PossicaoColuna,Nave->Durabilidade,Nave->QuantidadePeca,Nave->Consertado);
            
            if (!movimentar(Mapa,Nave,lista,inverteDirecao(celula->Cruzamento.CursoCrusamento[i].Caminho))){
                return 0;
            }
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

int percorreInteresse(quadrante **Mapa, quadrante* celula,nave* Nave,Percurso* lista,direcao DirecaoAnterior){
    /*Caso de sucesso */
    if (celula->Interesse.Saida == VERDADEIRO){//retorna 0 se achou a saida
        return 0;
    }

    if (celula->Interesse.Peca == VERDADEIRO){
        Nave->Durabilidade += Nave->AumentoPorPeca;
        Nave->QuantidadePeca++;
        celula->Interesse.Peca = FALSO;
    }
    
    if (DirecaoAnterior != Nulo && celula->Interesse.Peca == FALSO){//Pelo visto quando acha a peça nao perde vida
        Nave->Durabilidade -= Nave->DanoPorSetor;
    }
    /*1° Caso de falha */
    if (verificaNave(Nave) == 0){//Nave nao tem durabilidade
        atualizaNave(Nave,lista->Ultimo);
        RemoverUlitmoPercruso(lista);
        // Desfazer o caminho
        return 1;
    }
     
    for (int i = 0; i < QUANTIDADECAMINHOSINTERESSE; i++){
        //se pode acessar aquele caimnho chama de novo
        //Mecher dentro desse if caso a vida da nave nao conte
        if (celula->Interesse.CursoInteresse[i].Caminho != DirecaoAnterior && celula->Interesse.CursoInteresse[i].Acesso == VERDADEIRO){
            if (Nave->Consertado == VERDADEIRO)
                celula->Interesse.CursoInteresse[i].Acesso == FALSO;
            //se o proximo caminho retorna 0 achou a saida e vai retornando ai 
            
            inserePercurso(lista,Nave->PossicaoLinha,Nave->PossicaoColuna,Nave->Durabilidade,Nave->QuantidadePeca,Nave->Consertado);
                        
            if (!movimentar(Mapa,Nave,lista,inverteDirecao(celula->Interesse.CursoInteresse[i].Caminho))){
                return 0;
            }
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

int movimentar(quadrante **Mapa, nave* Nave,Percurso* lista,direcao DirecaoAnterior){
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
        Nave->PossicaoLinha++;
        break;
    case Sul:
        Nave->PossicaoLinha--;
        break;
    case Leste:
        Nave->PossicaoColuna--;
        break;
    case Oeste:
        Nave->PossicaoColuna++;
        break;
    }

    inserePercurso(lista,Nave->PossicaoLinha,Nave->PossicaoColuna,Nave->Durabilidade,Nave->QuantidadePeca,Nave->Consertado);
    
    int LinhaNave = Nave->PossicaoLinha;
    int ColunaNave = Nave->PossicaoColuna;
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
    case 3:
        resultado = percorreInteresse(Mapa, &Mapa[LinhaNave][ColunaNave], Nave, lista, DirecaoAnterior);
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