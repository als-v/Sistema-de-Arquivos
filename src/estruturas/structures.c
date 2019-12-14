#ifndef STRUCTURES
#define STRUCTURES

#include <stdio.h>
#include <stdlib.h>

#define QNTD_BLOCO 4096
#define SIZE_BLOCO 512
#define SIZE_DISCO (QNTD_BLOCO * SIZE_BLOCO)

/* Estrutura de um superbloco */
struct superBloco {
    int tamanho_bloco; // tamanho de cada bloco
    int numero_blocos; // numero total de blocos
    int blocos_livres; // quantidade de blocos livres
};

/* Estrutura do bloco */
struct Bloco {
    char* nome;                         // nome
    char* identificacao;                // identificacao: "D": Diretorio e "A": Arquivo
    struct Bloco* diretorio_anterior;   // contem ponteiro para o diretorio anterior
    struct Bloco* subdiretorios;        // contem os subdiretorios
    struct Bloco* proxima_particao;     // contem o ponteiro das particoes
};

struct subdiretorios{
    struct Bloco* blocos;
    struct Bloco proximo;
};

struct fat {
    int* id;
};

struct Memoria {
    struct superBloco* superBloco;
    struct Bloco* blocos;
};

/* Estrutura do Sistema de Arquivos */
struct fileSistem {
    struct Memoria* memoria;
};

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
};

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
};

/* printar todos os diretorios */
void print_D(struct Bloco* b){
    struct Bloco* aux;
    printf("Nome diretorio: %s\nIdentificacao: %s\n\n", b->nome, b->identificacao);

    aux = b->subdiretorios;
    while(aux != NULL){
        print_D(aux);
    }
};

/* Funcao inicializadora */
struct fileSistem* start_file_sistem(FILE* file){
    // inicia o sistema de arquivos
    struct fileSistem* fileSistem = (struct fileSistem*) malloc(sizeof(struct fileSistem));

    // inicia o super bloco
    fileSistem->superBloco = start_superbloco(file);
    print_SP(fileSistem->superBloco);

    // inicia o diretorio '/'
    fileSistem->Bloco = start_bloco(file);
    print_D(fileSistem->Bloco);

    if (fileSistem->Bloco != NULL){
        fileSistem->superBloco->numero_blocos -= fileSistem->superBloco->tamanho_bloco;
        fileSistem->superBloco->blocos_livres--;
        print_SP(fileSistem->superBloco);
    }
};

#endif