#ifndef STRUCTURES
#define STRUCTURES

#include <stdio.h>
#include <stdlib.h>

#define QNTD_BLOCO 4096
#define SIZE_BLOCO 512
#define TOT_BLOCO (QNTD_BLOCO/SIZE_BLOCO)
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
    struct Subdiretorio* subdiretorios; // contem os subdiretorios
    struct Bloco* proxima_particao;     // contem o ponteiro das particoes
};

/* Estrutura de subdiretorio */
struct Subdiretorio {
    struct Bloco* diretorio;
    struct Subdiretorio* prox;
    struct Subdiretorio* ant;
};

/* Estrutura da tabela dos blocos*/
struct TabelaBloco {
    int inicio_fat;
    char* nome;
    int bytes;
    int blocos;
    struct TabelaBloco* prox;
    struct TabelaBloco* ant;
};

/* Estrutura da memoria */
struct Armazenamento {
    struct Bloco* diretorios;
};

/* Estrutura da FAT */
struct fat {
    char* fat;
};

/* Estrutura do Sistema de Arquivos */
struct fileSistem {
    struct superBloco* superBloco;
    struct Bloco* Bloco;
    struct Bloco* diretorio_atual;
    struct Armazenamento* memoria;
    struct fat* fat;
    struct TabelaBloco* tabela;
};

/* Funcao que inicia o arquivo */
struct superBloco* start_superbloco(FILE* file){
    struct superBloco* b = (struct superBloco*) malloc(sizeof(struct superBloco));
    
    b->tamanho_bloco = SIZE_BLOCO;
    b->numero_blocos = QNTD_BLOCO;
    b->blocos_livres = TOT_BLOCO;

    return b;
};

/* Funcao que inicia o bloco root */
struct Bloco* start_bloco(FILE* file){
    struct Bloco* b = (struct Bloco*) malloc(sizeof(struct Bloco));
    char* nome = "/dsc";
    char* identificacao = "D";

    b->nome = nome;
    b->identificacao = identificacao;
    b->diretorio_anterior = NULL;
    b->subdiretorios = NULL;
    b->proxima_particao = NULL;

    return b;
};

// /* Funcao que inicia o vetor de blocos */
// void inicia_vetor_armazenamento(struct Armazenamento* a){
//     for(int i = 0; i < TOT_BLOCO; i++){
//         a->diretorios[i] = NULL;
//     }
// }

/* Funcao que inicia a memoria */
struct Armazenamento* start_memoria(FILE* file){
    struct Armazenamento* memoria = (struct Armazenamento*) malloc(sizeof(struct Armazenamento));
    
    // vetor da quantidade max de blocos
    memoria->diretorios = (struct Bloco*) calloc(TOT_BLOCO, sizeof(struct Bloco));

    //inicia_vetor_armazenamento(memoria);

    return memoria;
};

/* Funcao que inica o vetor FAT */
void inicia_vetor_fat(struct fat* fat){
    char* R = (char*) malloc(sizeof(char));
    char* F = (char*) malloc(sizeof(char));
    R = "R";
    F = "F";
    fat->fat[0] = *"R";     // pode ser que de errado e caso der, apenas
    //fat->fat[1] = *"R";     // referencio a variavel ja criada acima

    for(int i = 1; i < TOT_BLOCO; i++){
        fat->fat[i] = *"F";
    }
};

/* Funcao que inicia a FAT */
struct fat* start_fat(FILE* file){
    struct fat* fat = (struct fat*) malloc(sizeof(struct fat));
    fat->fat = (char*) calloc(TOT_BLOCO, sizeof(char));
    inicia_vetor_fat(fat);

    return fat;
};

/* funcao que inicia o referenciamento */
void start_tabela(FILE* file, struct fileSistem* f){
    struct TabelaBloco* tabela = (struct TabelaBloco*) malloc(sizeof(struct TabelaBloco));
    tabela->nome = f->Bloco->nome;
    tabela->blocos = 1;
    tabela->bytes = tabela->blocos * SIZE_BLOCO;
    tabela->prox = NULL;
    tabela->ant = NULL;
    tabela->inicio_fat = 0;

    f->memoria->diretorios[tabela->inicio_fat] = *f->Bloco;

    f->tabela = tabela;
}

/* printar super Bloco */
void print_S(struct superBloco* b){
    printf("Tamanho do bloco: %d\nNumero de Blocos: %d\nBlocos Livres: %d\n\n", b->tamanho_bloco, b->numero_blocos, b->blocos_livres);
};

/* printar todos o diretorio */
void print_D(struct Bloco* b){
    struct Subdiretorio* aux = b->subdiretorios;

    printf("Diretorio atual:\n     Nome: %s\n     Identificacao: %s\n", b->nome, b->identificacao);
    if(aux == NULL){
        printf("Sem subdiretorios\n\n");
    }else{
        printf("Subdiretorios:\n");
        print_D(aux->diretorio);
    }
};

/* printar a memoria */
void print_M(struct Armazenamento* m){
    struct Armazenamento* aux;
    struct Bloco* aux2;
    aux = m;
    aux2 = &m->diretorios[0];
    int i = 1;
    while(i < TOT_BLOCO){
        printf("NOME: %s\n", aux2->nome);
        aux2 = &m->diretorios[i];
        i++;
    }
};

/* printar a FAT */
void print_F(struct fat* fat){
    for(int i = 0; i < TOT_BLOCO; i++){
        printf("Caracter: %c\n", fat->fat[i]);
    }
};

/* Funcao inicializadora */
struct fileSistem* start_file_sistem(FILE* file){
    // inicia o sistema de arquivos
    struct fileSistem* fileSistem = (struct fileSistem*) malloc(sizeof(struct fileSistem));

    // inicia o super bloco
    fileSistem->superBloco = start_superbloco(file);
    print_S(fileSistem->superBloco);

    // inicia o diretorio '/'
    fileSistem->Bloco = start_bloco(file);
    
    print_D(fileSistem->Bloco);

    // inicia a memoria
    fileSistem->memoria = start_memoria(file);
    //print_M(fileSistem->memoria);

    // inicia a fat
    fileSistem->fat = start_fat(file);
    //printar_F(fileSistem->fat);

    // inicia a tabela
    if (fileSistem->Bloco != NULL){
        if (fileSistem->superBloco->blocos_livres > 0){
            // atualizo os blocos livres e numero de blocos
            fileSistem->superBloco->numero_blocos -= fileSistem->superBloco->tamanho_bloco;
            fileSistem->superBloco->blocos_livres--;

            print_S(fileSistem->superBloco);

            // root agora e meu novo diretorio atual
            fileSistem->diretorio_atual = fileSistem->Bloco;

            // crio minha tabela de blocos
            start_tabela(file, fileSistem);
        }
    }

    return fileSistem;
};

#endif