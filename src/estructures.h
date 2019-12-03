#include <stdio.h>

#define QNTD_BLOCO 4096
#define SIZE_BLOCO 512
#define SIZE_DISCO (QNTD_BLOCO * SIZE_BLOCO)

/* Estrutura de um superbloco */
struct superBloco {
    // tamanho de cada bloco
    int tamanho_bloco;
    // numero total de blocos
    int numero_blocos;
    // quantidade de blocos livres
    int blocos_livres;
};

/* Funcao que inicia o arquivo */
void start(FILE* file){
    struct superBloco b;
    
    b.tamanho_bloco = SIZE_BLOCO;
    b.numero_blocos = QNTD_BLOCO;
    b.blocos_livres = QNTD_BLOCO;

    printf("Tamanho Bloco: %d\nNumero de blocos: %d\nBlocos livres: %d\n", b.tamanho_bloco, b.numero_blocos, b.blocos_livres);
};