#ifndef FUNCT
#define FUNCT

#include <stdio.h>
#include "../estruturas/structures.h"

/* Funcao que atualiza o subdiretorio */
void add_diretorio(struct Bloco* diretorio, struct Bloco* novo_diretorio){
    struct Bloco* diretorio2 = diretorio;
    struct Subdiretorio* aux = diretorio2->subdiretorios;

    if (aux == NULL){
        struct Subdiretorio* sub = (struct Subdiretorio*) malloc(sizeof(struct Subdiretorio));
        sub->diretorio = novo_diretorio;
        sub->prox = NULL;
        sub->ant = NULL;

        diretorio2->subdiretorios = sub;
    }else{

        while(aux->prox != NULL){
            aux = aux->prox;
        }
        
        struct Subdiretorio* sub = (struct Subdiretorio*) malloc(sizeof(struct Subdiretorio));
        sub->diretorio = novo_diretorio;
        sub->prox = NULL;
        sub->ant = aux;

        aux = sub;
    }
    
};

/* Atualiza sistema de arquivos */
void update(struct fileSistem* f, struct Bloco* b){
    // atualizando super bloco
    f->superBloco->numero_blocos -= f->superBloco->tamanho_bloco;
    f->superBloco->blocos_livres--;

    // procurando posicao livre FAT e atualizando ela
    int pos = 0;
    struct fat* fat = f->fat;
    for(int i = 0; i< TOT_BLOCO; i++){
        if(fat->fat[i] == *"F"){
            pos = i;
            fat->fat[i] = *"D"; // D de diretorio
            break;
        }
    }

    if (pos > 0 && pos < TOT_BLOCO){
        // atualizando tabela
        struct TabelaBloco* aux = f->tabela;

        while(aux != NULL){
            aux = aux->prox;
        }

        aux = (struct TabelaBloco*) malloc(sizeof(struct TabelaBloco));
        aux->inicio_fat = pos;
        aux->nome = b->nome;
        aux->blocos = 1;
        aux->bytes = aux->blocos * SIZE_BLOCO;
        aux->prox = NULL;

        // atualizando a memoria
        struct Armazenamento* a = f->memoria;

        a->diretorios[pos] = *b;
    }
};

/* Funcao que cria um novo diretorio */
struct Bloco* cria_novo_diretorio(struct fileSistem* fileSistem, struct Bloco* diretorio, char* nome){
    if(fileSistem->superBloco->blocos_livres > 0){
        // criando o novo bloco
        char* nome2 = (char*) malloc(sizeof(char));
        nome2 = nome;
        char* ID = "D";
        struct Bloco* novo_bloco = (struct Bloco*) malloc(sizeof(struct Bloco));
        novo_bloco->nome = nome2;
        novo_bloco->identificacao = ID;
        novo_bloco->subdiretorios = NULL;
        novo_bloco->proxima_particao = NULL;

        // atualizando o diretorio atual
        add_diretorio(diretorio, novo_bloco);

        // atualiza fat/memoria
        update(fileSistem, novo_bloco);

        //return novo_bloco;
    }else{
        printf("Erro na criacao de um novo diretorio/arquivo!\nO sistema nao possui mais espaco!\n");
        return NULL;
    }
};

#endif