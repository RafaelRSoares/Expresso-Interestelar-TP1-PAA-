#include "backtracking.h"

extern int totalChamadas;
extern int nivelMaximo;
extern int modoAnaliseAtivo;

void atualizaNave(nave* Nave, Informacoes* infos){
    Nave->PossicaoLinha = infos->Linha;
    Nave->PossicaoColuna = infos->Coluna;
    Nave->Durabilidade = infos->Durabilidade;
    Nave->QuantidadePeca = infos->PecasColetadas;
}

int percorreRua(quadrante **Mapa,quadrante* celula,nave* Nave,Percurso* lista,direcao DirecaoAnterior){
    if (Nave->Consertado == FALSO){    
        if (DirecaoAnterior != Nulo && celula->Rua.Peca == FALSO){//Pelo visto quando acha a peça nao perde vida
            Nave->Durabilidade -= Nave->DanoPorSetor;
        }
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
                celula->Rua.CursoRua[i].Acesso = FALSO;
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
    if (Nave->Consertado == FALSO){ 
        if (DirecaoAnterior != Nulo && celula->Cruzamento.Peca == FALSO){//Pelo visto quando acha a peça nao perde vida
            Nave->Durabilidade -= Nave->DanoPorSetor;
        }
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
                celula->Cruzamento.CursoCrusamento[i].Acesso = FALSO;
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
    short aux = 0;
    if (Nave->Consertado == FALSO){
        if (celula->Interesse.Peca == VERDADEIRO){
            Nave->Durabilidade += Nave->AumentoPorPeca;
            Nave->QuantidadePeca++;
            celula->Interesse.Peca = FALSO;
            aux = 1;
        }    
        else if (DirecaoAnterior != Nulo && celula->Interesse.Peca == FALSO){//Pelo visto quando acha a peça nao perde vida
            Nave->Durabilidade -= Nave->DanoPorSetor;
        }
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
                celula->Interesse.CursoInteresse[i].Acesso = FALSO;
            
            //se o proximo caminho retorna 0 achou a saida e vai retornando ai 
            
            inserePercurso(lista,Nave->PossicaoLinha,Nave->PossicaoColuna,Nave->Durabilidade,Nave->QuantidadePeca,Nave->Consertado);
                        
            if (!movimentar(Mapa,Nave,lista,inverteDirecao(celula->Interesse.CursoInteresse[i].Caminho))){
                return 0;
            }
            // se nao achou a saida tenta outro caminho 
            atualizaNave(Nave,lista->Ultimo);
            RemoverUlitmoPercruso(lista);    
        }
        if (aux)
                celula->Interesse.Peca = VERDADEIRO;
    
    }
    /*2° Caso de falha */
    //Nao tem caminhos percorriveis
    atualizaNave(Nave,lista->Ultimo);
    RemoverUlitmoPercruso(lista);    
    return 1;
}

int percorreEventoEspecial(quadrante **Mapa, quadrante* celula, nave* Nave, Percurso* lista, direcao DirecaoAnterior) {
    if (celula->Especial.Efeito == TEMPORAL_ANOMALY)
        celula->Especial.Efeito = rand() % TEMPORAL_ANOMALY + 1;   
    
    
    switch (celula->Especial.Efeito) {
        case WORMHOLE: // Buraco de minhoca
            celula->Especial.Efeito = NORMAL;

            inserePercurso(lista,Nave->PossicaoLinha,Nave->PossicaoColuna,Nave->Durabilidade,Nave->QuantidadePeca,Nave->Consertado);

            if(!movimentar(Mapa, Nave, lista, Gargantua))
                return 0;


            atualizaNave(Nave,lista->Ultimo);
            RemoverUlitmoPercruso(lista);

            if (Nave->Consertado == FALSO){ 
                    if (DirecaoAnterior != Nulo && celula->Especial.Peca == FALSO){//Pelo visto quando acha a peça nao perde vida
                        Nave->Durabilidade -= Nave->DanoPorSetor;
                    }
                }
            /*1° Caso de falha */
            if (verificaNave(Nave) == 0){//Nave nao tem durabilidade
                atualizaNave(Nave,lista->Ultimo);
                RemoverUlitmoPercruso(lista);
                // Desfazer o caminho
                return 1;
            }


            for (int i = 0; i < QUANTIDADECAMINHOSESPECIAL; i++){
                //se pode acessar aquele caimnho chama de novo
                //Mecher dentro desse if caso a vida da nave nao conte
                if (celula->Cruzamento.CursoCrusamento[i].Caminho != DirecaoAnterior && celula->Cruzamento.CursoCrusamento[i].Acesso == VERDADEIRO){
                    if (Nave->Consertado == VERDADEIRO)
                        celula->Especial.CursoEspecial[i].Acesso = FALSO;
                    //se o proximo caminho retorna 0 achou a saida e vai retornando ai 
                    
                    inserePercurso(lista,Nave->PossicaoLinha,Nave->PossicaoColuna,Nave->Durabilidade,Nave->QuantidadePeca,Nave->Consertado);
                    
                    if (!movimentar(Mapa,Nave,lista,inverteDirecao(celula->Especial.CursoEspecial[i].Caminho))){
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
            break;


        case ASTEROIDE: // Asteroide
            Nave->Durabilidade -= (Nave->DanoPorSetor * 2);
            celula->Especial.Efeito = NORMAL;

            if (Nave->Consertado == FALSO){ 
                    if (DirecaoAnterior != Nulo && celula->Especial.Peca == FALSO){//Pelo visto quando acha a peça nao perde vida
                        Nave->Durabilidade -= Nave->DanoPorSetor;
                    }
                }
            /*1° Caso de falha */
            if (verificaNave(Nave) == 0){//Nave nao tem durabilidade
                atualizaNave(Nave,lista->Ultimo);
                RemoverUlitmoPercruso(lista);
                // Desfazer o caminho
                return 1;
            }


            for (int i = 0; i < QUANTIDADECAMINHOSESPECIAL; i++){
                //se pode acessar aquele caimnho chama de novo
                //Mecher dentro desse if caso a vida da nave nao conte
                if (celula->Cruzamento.CursoCrusamento[i].Caminho != DirecaoAnterior && celula->Cruzamento.CursoCrusamento[i].Acesso == VERDADEIRO){
                    if (Nave->Consertado == VERDADEIRO)
                        celula->Especial.CursoEspecial[i].Acesso = FALSO;
                    //se o proximo caminho retorna 0 achou a saida e vai retornando ai 
                    
                    inserePercurso(lista,Nave->PossicaoLinha,Nave->PossicaoColuna,Nave->Durabilidade,Nave->QuantidadePeca,Nave->Consertado);
                    
                    if (!movimentar(Mapa,Nave,lista,inverteDirecao(celula->Especial.CursoEspecial[i].Caminho))){
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

            break;

        case GAMMA: // Raio gama
            celula->Especial.Efeito = NORMAL;
            Nave->Durabilidade = 0;
            atualizaNave(Nave,lista->Ultimo);// verificar isso atualizaçao aqui
            RemoverUlitmoPercruso(lista);
            return 1; // fim da execução
            break;


        case REPAIR: // Reator de reparo
            Nave->Durabilidade += (Nave->AumentoPorPeca * 2);
            celula->Especial.Efeito = NORMAL;
            /*1° Caso de falha */
            if (verificaNave(Nave) == 0){//Nave nao tem durabilidade
                atualizaNave(Nave,lista->Ultimo);
                RemoverUlitmoPercruso(lista);
                // Desfazer o caminho
                return 1;
            }

            for (int i = 0; i < QUANTIDADECAMINHOSESPECIAL; i++){
                //se pode acessar aquele caimnho chama de novo
                //Mecher dentro desse if caso a vida da nave nao conte
                if (celula->Cruzamento.CursoCrusamento[i].Caminho != DirecaoAnterior && celula->Cruzamento.CursoCrusamento[i].Acesso == VERDADEIRO){
                    if (Nave->Consertado == VERDADEIRO)
                        celula->Especial.CursoEspecial[i].Acesso = FALSO;
                    //se o proximo caminho retorna 0 achou a saida e vai retornando ai 
                    
                    inserePercurso(lista,Nave->PossicaoLinha,Nave->PossicaoColuna,Nave->Durabilidade,Nave->QuantidadePeca,Nave->Consertado);
                    
                    if (!movimentar(Mapa,Nave,lista,inverteDirecao(celula->Especial.CursoEspecial[i].Caminho))){
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
            break;

        default://Normal
            if (Nave->Consertado == FALSO){ 
                    if (DirecaoAnterior != Nulo && celula->Especial.Peca == FALSO){//Pelo visto quando acha a peça nao perde vida
                        Nave->Durabilidade -= Nave->DanoPorSetor;
                    }
                }
                /*1° Caso de falha */
                if (verificaNave(Nave) == 0){//Nave nao tem durabilidade
                    atualizaNave(Nave,lista->Ultimo);
                    RemoverUlitmoPercruso(lista);
                    // Desfazer o caminho
                    return 1;
                }


                for (int i = 0; i < QUANTIDADECAMINHOSESPECIAL; i++){
                    //se pode acessar aquele caimnho chama de novo
                    //Mecher dentro desse if caso a vida da nave nao conte
                    if (celula->Cruzamento.CursoCrusamento[i].Caminho != DirecaoAnterior && celula->Cruzamento.CursoCrusamento[i].Acesso == VERDADEIRO){
                        if (Nave->Consertado == VERDADEIRO)
                            celula->Especial.CursoEspecial[i].Acesso = FALSO;
                        //se o proximo caminho retorna 0 achou a saida e vai retornando ai 
                        
                        inserePercurso(lista,Nave->PossicaoLinha,Nave->PossicaoColuna,Nave->Durabilidade,Nave->QuantidadePeca,Nave->Consertado);
                        
                        if (!movimentar(Mapa,Nave,lista,inverteDirecao(celula->Especial.CursoEspecial[i].Caminho))){
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
            break;
    }

    if (verificaNave(Nave) == 0) {
        atualizaNave(Nave,lista->Ultimo);// verificar isso atualizaçao aqui
        RemoverUlitmoPercruso(lista);
        return 1;
    }

    return movimentar(Mapa, Nave, lista, DirecaoAnterior);
}

int movimentar(quadrante **Mapa, nave* Nave,Percurso* lista,direcao DirecaoAnterior){
    //modo analise
    static int nivelAtual = 0;
    
    int LinhaNave;
    int ColunaNave;

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
    case Gargantua:
        LinhaNave = rand() % LINHAS;
        ColunaNave = rand() % COLUNAS;
        while (Mapa[LinhaNave][ColunaNave].Tipo == '.'){
            LinhaNave = rand() % LINHAS;
            ColunaNave = rand() % COLUNAS;
        }
        Nave->PossicaoLinha = LinhaNave;
        Nave->PossicaoColuna = ColunaNave;
    }
    inserePercurso(lista,Nave->PossicaoLinha,Nave->PossicaoColuna,Nave->Durabilidade,Nave->QuantidadePeca,Nave->Consertado);
    
    LinhaNave = Nave->PossicaoLinha;
    ColunaNave = Nave->PossicaoColuna;
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



