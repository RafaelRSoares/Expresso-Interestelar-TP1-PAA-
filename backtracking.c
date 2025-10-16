#include "backtracking.h"


void atualizaNave(nave* Nave, Informacoes* infos){
    Nave->PossicaoLinha = infos->Linha;
    Nave->PossicaoColuna = infos->Coluna;
    Nave->Durabilidade = infos->Durabilidade;
    Nave->QuantidadePeca = infos->PecasColetadas;
}

int percorreRua(quadrante **Mapa,quadrante* celula,nave* Nave,Percurso* lista,direcao DirecaoAnterior){
    /*Caso de sucesso */
    //NÃO APAGAR - PEDRO
    // if (celula->Rua.Saida == TRUE){//retorna 0 se achou a saida
    //     return 0;
    // }

    // if (celula->Rua.Peca == TRUE){
    //     Nave->Durabilidade += Nave->AumentoPorPeca;
    //     Nave->QuantidadePeca++;
    //     celula->Rua.Peca = FALSE;
    // }
    
    if (DirecaoAnterior != Nulo && celula->Rua.Peca == FALSE){//Pelo visto quando acha a peça nao perde vida
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
        if (celula->Rua.CursoRua[i].Caminho != DirecaoAnterior && celula->Rua.CursoRua[i].Acesso == TRUE){
            if (Nave->Consertado == TRUE)
                celula->Rua.CursoRua[i].Acesso == FALSE;
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
    // if (celula->Cruzamento.Saida == TRUE){//retorna 0 se achou a saida
    //     return 0;
    // }

    // if (celula->Cruzamento.Peca == TRUE){
    //     Nave->Durabilidade += Nave->AumentoPorPeca;
    //     Nave->QuantidadePeca++;
    //     celula->Cruzamento.Peca = FALSE;
    // }
    
    if (DirecaoAnterior != Nulo && celula->Cruzamento.Peca == FALSE){//Pelo visto quando acha a peça nao perde vida
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
        if (celula->Cruzamento.CursoCrusamento[i].Caminho != DirecaoAnterior && celula->Cruzamento.CursoCrusamento[i].Acesso == TRUE){
            if (Nave->Consertado == TRUE)
                celula->Cruzamento.CursoCrusamento[i].Acesso == FALSE;
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
    if (celula->Interesse.Saida == TRUE){//retorna 0 se achou a saida
        return 0;
    }

    if (celula->Interesse.Peca == TRUE){
        Nave->Durabilidade += Nave->AumentoPorPeca;
        Nave->QuantidadePeca++;
        celula->Interesse.Peca = FALSE;
    }
    
    if (DirecaoAnterior != Nulo && celula->Interesse.Peca == FALSE){//Pelo visto quando acha a peça nao perde vida
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
        if (celula->Interesse.CursoInteresse[i].Caminho != DirecaoAnterior && celula->Interesse.CursoInteresse[i].Acesso == TRUE){
            if (Nave->Consertado == TRUE)
                celula->Interesse.CursoInteresse[i].Acesso == FALSE;
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

int percorreEventoEspecial(quadrante **Mapa, quadrante* celula, nave* Nave, Percurso* lista, direcao DirecaoAnterior) {
    switch (celula->Tipo) {
        case 'B': // Buraco de minhoca
            printf("[!] Buraco de minhoca detectado! A nave foi teletransportada!\n");
            Nave->PossicaoLinha = rand() % LINHAS;
            Nave->PossicaoColuna = rand() % COLUNAS;
            break;

        case 'A': // Asteroide
            printf("[!] Campo de asteroides! Dano elevado!\n");
            Nave->Durabilidade -= (Nave->DanoPorSetor * 2);
            break;

        case 'G': // Raio gama
            printf("[X] Raio gama detectado! A nave foi destruída instantaneamente!\n");
            Nave->Durabilidade = 0;
            return 1; // fim da execução
            break;

        case 'R': // Reator de reparo
            printf("[+] Reator de reparo encontrado! Durabilidade aumentada!\n");
            Nave->Durabilidade += (Nave->AumentoPorPeca * 2);
            break;

        default:
            break;
    }

    if (verificaNave(Nave) == 0) {
        RemoverUlitmoPercruso(lista);
        return 1;
    }

    return movimentar(Mapa, Nave, lista, DirecaoAnterior);
}

int movimentar(quadrante **Mapa, nave* Nave,Percurso* lista,direcao DirecaoAnterior){
//modo analise
    static int nivelAtual = 0;

    // Contagem dinâmica de análise
    if (modoAnaliseAtivo) {
        totalChamadas++;
        nivelAtual++;
        if (nivelAtual > nivelMaximo)
            nivelMaximo = nivelAtual;
    }

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
    case 4:
        resultado = percorreEventoEspecial(Mapa, &Mapa[LinhaNave][ColunaNave], Nave, lista, DirecaoAnterior);
        break;
    default:
        resultado = 1;
        break;
    }

    if (modoAnaliseAtivo)
        nivelAtual--;

    return resultado;
}