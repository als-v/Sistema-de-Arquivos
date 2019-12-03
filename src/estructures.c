#include <stdlib.h>
#include "estructures.h"

/* Funcao que inicia o arquivo */
struct superBloco* start_superbloco(FILE* file){
    struct superBloco* b = (struct superBloco*) malloc(sizeof(struct superBloco));
    
    b->tamanho_bloco = SIZE_BLOCO;
    b->numero_blocos = QNTD_BLOCO;
    b->blocos_livres = (QNTD_BLOCO/SIZE_BLOCO);

    return b;
};

/* printar super Bloco */
void print_SP(struct superBloco* b){
    printf("Tamanho do bloco: %d\nNumero de Blocos: %d\nBlocos Livres: %d\n\n", b->tamanho_bloco, b->numero_blocos, b->blocos_livres);
}

/* Funcao que inicia o bloco root */
struct Bloco* start_bloco(FILE* file){
    struct Bloco* b = (struct Bloco*) malloc(sizeof(struct Bloco));
    char* nome = "/";
    char* identificacao = "D";

    b->nome = nome;
    b->identificacao = identificacao;
    b->diretorio_anterior = NULL;
    b->subdiretorios = NULL;
    b->proxima_particao = NULL;

    return b;
}

/* printar todos os diretorios */
void print_D(struct Bloco* b){
    struct Bloco* aux;
    printf("Nome diretorio: %s\nIdentificacao: %s\n\n", b->nome, b->identificacao);

    aux = b->subdiretorios;
    while(aux != NULL){
        print_D(aux);
    }
}

/* Funcao inicializadora */
void start(FILE* file){
    struct superBloco* superBloco;
    struct Bloco* root;

    // inicia o arquivo
    superBloco = start_superbloco(file);
    print_SP(superBloco);

    // inicia o bloco
    root = start_bloco(file);
    print_D(root);

    // caso a criacao do primeiro diretorio deu certo
    if (root != NULL){
        superBloco->numero_blocos -= superBloco->tamanho_bloco;
        superBloco->blocos_livres--;
        print_SP(superBloco);
    }

}