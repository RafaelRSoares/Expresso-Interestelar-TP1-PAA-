#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include "gerarMapa.h"
#include "backtracking.h"
#define STRING 20

int LINHAS;
int COLUNAS;

int modoAnaliseAtivo = 0;
int totalChamadas = 0;
int nivelMaximo = 0;

void resetAnalise() {
    totalChamadas = 0;
    nivelMaximo = 0;
}

GtkBuilder *builder;
GtkWidget *window;
GtkStack *stack;

void mensagemN(char *text, char *text2){
    GtkMessageDialog *mensagem_dialogo = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "mensagem"));
    g_object_set(mensagem_dialogo, "text", text, NULL);
    g_object_set(mensagem_dialogo, "secondary_text", text2, NULL);
    gtk_widget_show_all(GTK_WIDGET(mensagem_dialogo));
    gtk_dialog_run(GTK_DIALOG(mensagem_dialogo));
    gtk_widget_hide(GTK_WIDGET(mensagem_dialogo));
}

void mensagemB(char *text, char *text2){
    GtkMessageDialog *mensagem_dialogo = GTK_MESSAGE_DIALOG(gtk_builder_get_object(builder, "mensagemboa"));
    g_object_set(mensagem_dialogo, "text", text, NULL);
    g_object_set(mensagem_dialogo, "secondary_text", text2, NULL);
    gtk_widget_show_all(GTK_WIDGET(mensagem_dialogo));
    gtk_dialog_run(GTK_DIALOG(mensagem_dialogo));
    gtk_widget_hide(GTK_WIDGET(mensagem_dialogo));
}

void imprimirListaUI(Percurso* lista){
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtk_builder_get_object(builder, "text_saida")));
    gtk_text_buffer_set_text(buffer, "", -1);
    Apontador Aux;
    Aux = lista->Primeiro->Prox;
    int Ajuda = 0;
    while(Aux != NULL){
        if(Ajuda == 1 || Aux->Prox == NULL) {
            Ajuda = 0;
            int sobrou = 4 - Aux->PecasColetadas;
            char texto[256];
            sprintf(texto, "linha: %d, Coluna: %d D: %d pecas restantes: %d\n", Aux->Linha, Aux->Coluna, Aux->Durabilidade, sobrou);
            GtkTextIter end;
            gtk_text_buffer_get_end_iter(buffer, &end);
            gtk_text_buffer_insert(buffer, &end, texto, -1);
            if(Aux->PecasColetadas== 4){
                sprintf(texto, "\nA jornada sera finalizada sem mais desafios\n");
                gtk_text_buffer_get_end_iter(buffer, &end);
                gtk_text_buffer_insert(buffer, &end, texto, -1);
                break;
            }
            Aux = Aux->Prox;
        } else if(Ajuda == 0){
            Ajuda = 1;
            Aux = Aux->Prox;
        }
    }
}

void imprimirPreVisualizacaoMapa(char* nome){
    GtkTextView *textView = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "text_mapa"));
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(textView);
    PangoFontDescription *font_desc = pango_font_description_from_string("Monospace 12");
    gtk_widget_override_font(GTK_WIDGET(textView), font_desc);
    pango_font_description_free(font_desc);
    gtk_text_buffer_set_text(buffer, "", -1);
    GtkTextIter end;
    FILE* arqEntrada;
    arqEntrada = fopen(nome, "r");
    int _;
    fscanf(arqEntrada,"%d %d %d", &_, &_, &_);
    fscanf(arqEntrada, "%d %d", &LINHAS, &COLUNAS);
    char texto[256];
    quadrante **Mapa;
    Mapa = malloc(LINHAS * sizeof(quadrante*));
    for (int i=0;i<LINHAS; i++){
        Mapa[i] = malloc(COLUNAS * sizeof (quadrante));
    }

    for(int i = 0; i < LINHAS; i++){
        for(int j = 0; j < COLUNAS; j++){
            fscanf(arqEntrada, " %c", &Mapa[i][j].Tipo);
        }
    }
    for(int i = 0; i < LINHAS; i++){
        for(int j = 0; j < COLUNAS; j++){
            sprintf(texto, "%c ", Mapa[i][j].Tipo);
            gtk_text_buffer_get_end_iter(buffer, &end);
            gtk_text_buffer_insert(buffer, &end, texto, -1);
        }
        gtk_text_buffer_get_end_iter(buffer, &end);
        gtk_text_buffer_insert(buffer, &end, "\n", -1);
    }
    fclose(arqEntrada);
    for (int i = 0; i < LINHAS; i++)
        free(Mapa[i]);
    free(Mapa);

}

void on_main_window_destroy(){
    gtk_main_quit();
}
void on_button_iniciar_clicked(){
    gtk_stack_set_visible_child_name(stack, "view_escolher_Operação");
}
void on_button_inserir_arquivo_clicked(){
    gtk_stack_set_visible_child_name(stack, "view_escolher_arquivo");
}
void on_button_gerar_mapa_clicked(){
    gtk_stack_set_visible_child_name(stack, "view_gerar_mapas");
}
void on_button_sair_clicked(){
    gtk_main_quit();
}
void on_button_ler_arquivo_clicked(){
    const char* file = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "arquivo")));
    FILE* arqEntrada;
    arqEntrada = fopen(file, "r");
    if(arqEntrada==NULL){
        mensagemN("Erro", "Não foi possivel ler o arquivo, confira se o nome esta correto");
        gtk_stack_set_visible_child_name(stack, "view_escolher_arquivo");
    return;
    }
    //nave do filme "Interestelar", pareceu que caberia bem
    nave Endurance; 
    fscanf(arqEntrada,"%d %d %d", &Endurance.Durabilidade, &Endurance.DanoPorSetor, &Endurance.AumentoPorPeca);
    fscanf(arqEntrada, "%d %d", &LINHAS, &COLUNAS);
    quadrante **Mapa;
    Mapa = malloc(LINHAS * sizeof(quadrante*));
    for (int i=0;i<LINHAS; i++){
        Mapa[i] = malloc(COLUNAS * sizeof (quadrante));
    }

    for(int i = 0; i < LINHAS; i++){
        for(int j = 0; j < COLUNAS; j++){
            fscanf(arqEntrada, " %c", &Mapa[i][j].Tipo);
        }
    }
    int pecasTotais = 0;
    for(int i = 0; i < LINHAS; i++){
        for(int j = 0; j < COLUNAS; j++){
            if(Mapa[i][j].Tipo == 'P'){
                pecasTotais+=1;
            }
        }
    }
    fclose(arqEntrada);
    resetAnalise();
    modoAnaliseAtivo = 1;
    Percurso percurso;
    inicializarPercurso(&percurso);
    setMapa(Mapa,&Endurance);
    mensagemB("Arquivo lido com sucesso", "Veja o resultado na tela a seguir");
    gtk_stack_set_visible_child_name(stack, "view_resultado");
    char texto[256];
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtk_builder_get_object(builder, "text_saida")));
    gtk_text_buffer_set_text(buffer, "", -1);
    GtkTextIter end;
    int resultado = movimentar(Mapa,&Endurance,&percurso,Nulo);
    if (resultado == 0){
    imprimirListaUI(&percurso);
    }
    g_print("%d\n", TodasAsPecasForamColetadas(&percurso));
    int verificacao = TodasAsPecasForamColetadas(&percurso);
    if(resultado == 1){
        sprintf(texto, "\nApesar da bravura a tripulacao falhou em sua jornada\n");
        gtk_text_buffer_get_end_iter(buffer, &end);
        gtk_text_buffer_insert(buffer, &end, texto, -1);}
    else if(resultado == 0 && verificacao == 0){
        sprintf(texto, "\nA tripulacao finalizou sua jornada\n");
        gtk_text_buffer_get_end_iter(buffer, &end);
        gtk_text_buffer_insert(buffer, &end, texto, -1);
    }

}

void on_button_dificuldades_clicked(){
    gtk_stack_set_visible_child_name(stack, "view_dificuldades");
}
void on_button_total_clicked(){
    gtk_stack_set_visible_child_name(stack, "view_parametros");
}
void on_button_facil_clicked(){
    char* nomeArquivo = gerarMapaUI(1);
    char texto[200];
    sprintf(texto, "O seu mapa na dificuldade fácil foi gerado com o nome: %s\nVeja sua pré visualização na tela seguinte", nomeArquivo);
    mensagemB("Mapa gerado", texto);
    gtk_stack_set_visible_child_name(stack, "view_pre_mapa");
    imprimirPreVisualizacaoMapa(nomeArquivo);
}
void on_button_medio_clicked(){
    char* nomeArquivo = gerarMapaUI(2);
    char texto[200];
    sprintf(texto, "O seu mapa na dificuldade médio foi gerado com o nome: %s\nVeja sua pré visualização na tela seguinte", nomeArquivo);
    mensagemB("Mapa gerado", texto);
    gtk_stack_set_visible_child_name(stack, "view_pre_mapa");
    imprimirPreVisualizacaoMapa(nomeArquivo);
}
void on_button_dificil_clicked(){
    char* nomeArquivo = gerarMapaUI(3);
    char texto[200];
    sprintf(texto, "O seu mapa na dificuldade difícil foi gerado com o nome: %s\nVeja sua pré visualização na tela seguinte", nomeArquivo);
    mensagemB("Mapa gerado", texto);
    gtk_stack_set_visible_child_name(stack, "view_pre_mapa");
    imprimirPreVisualizacaoMapa(nomeArquivo);
}

void on_button_voltar_menu_clicked(){
    gtk_stack_set_visible_child_name(stack, "view_escolher_Operação");
}

void on_button_analise_clicked(){
    gtk_stack_set_visible_child_name(stack, "view_analise_funcao");
    char texto[256];
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(gtk_builder_get_object(builder, "text_analise")));
    gtk_text_buffer_set_text(buffer, "", -1);
    GtkTextIter end;
    sprintf(texto, "Total de chamadas recursivas: %d\n", totalChamadas);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, texto, -1);
    sprintf(texto, "Nivel maximo de recursao: %d\n", nivelMaximo);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_insert(buffer, &end, texto, -1); 
}

void on_button_voltar_menu2_clicked(){
    gtk_stack_set_visible_child_name(stack, "view_escolher_Operação");
}

void on_button_voltar_menu3_clicked(){
    gtk_stack_set_visible_child_name(stack, "view_escolher_Operação");
}

void on_button_enviar_parametros_clicked(){
    const char *altura_texto = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "altura")));
    int altura = atoi(altura_texto);
    const char *largura_texto = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "largura")));
    int largura = atoi(largura_texto);
    const char *pecas_texto = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "pecas")));
    int pecas = atoi(pecas_texto);
    const char *durabilidade_texto = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "durabilidade")));
    int durabilidade = atoi(durabilidade_texto);
    const char *movimentacao_texto = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "movimentacao")));
    int movimentacao = atoi(movimentacao_texto);
    const char *aumento_texto = gtk_entry_get_text(GTK_ENTRY(gtk_builder_get_object(builder, "aumento")));
    int aumento = atoi(aumento_texto);
    char* nomeArquivo = gerarMapaUI2(altura, largura, pecas, durabilidade, movimentacao, aumento);
    char texto[200];
    sprintf(texto, "O seu mapa foi gerado com o nome: %s\nVeja sua pré visualização na tela seguinte", nomeArquivo);
    mensagemB("Mapa gerado", texto);
    gtk_stack_set_visible_child_name(stack, "view_pre_mapa");
    imprimirPreVisualizacaoMapa(nomeArquivo);
}

int main(int argc, char **argv){
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("ui.glade");
    gtk_builder_add_callback_symbols(
        builder,
        "on_main_window_destroy",   G_CALLBACK(on_main_window_destroy),
        "on_button_iniciar_clicked",   G_CALLBACK(on_button_iniciar_clicked),
        "on_button_inserir_arquivo_clicked",   G_CALLBACK(on_button_inserir_arquivo_clicked),
        "on_button_gerar_mapa_clicked",   G_CALLBACK(on_button_gerar_mapa_clicked),
        "on_button_sair_clicked",   G_CALLBACK(on_button_sair_clicked),
        "on_button_ler_arquivo_clicked",   G_CALLBACK(on_button_ler_arquivo_clicked),
        "on_button_voltar_menu_clicked",    G_CALLBACK(on_button_voltar_menu_clicked),
        "on_button_dificuldades_clicked",   G_CALLBACK(on_button_dificuldades_clicked),
        "on_button_total_clicked",  G_CALLBACK(on_button_total_clicked),
        "on_button_facil_clicked",  G_CALLBACK(on_button_facil_clicked),
        "on_button_medio_clicked",  G_CALLBACK(on_button_medio_clicked),
        "on_button_dificil_clicked",    G_CALLBACK(on_button_dificil_clicked),
        "on_button_enviar_parametros_clicked", G_CALLBACK(on_button_enviar_parametros_clicked),
        "on_button_analise_clicked", G_CALLBACK(on_button_analise_clicked),
        "on_button_voltar_menu2_clicked", G_CALLBACK(on_button_voltar_menu2_clicked),
        "on_button_voltar_menu3_clicked", G_CALLBACK(on_button_voltar_menu3_clicked),
        NULL);
        gtk_builder_connect_signals(builder,NULL);
        stack = GTK_STACK(gtk_builder_get_object(builder, "stack"));
        window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
        gtk_widget_show_all(window);
        gtk_main();
    
    return 0;
}
