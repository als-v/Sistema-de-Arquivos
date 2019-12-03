#include <stdio.h>

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
struct Bloco{
    char* nome;                         // nome
    char* identificacao;                // identificacao: "D": Diretorio e "A": Arquivo
    struct Bloco* diretorio_anterior;   // contem ponteiro para o diretorio anterior
    struct Bloco* subdiretorios;        // contem os subdiretorios
    struct Bloco* proxima_particao;     // contem o ponteiro das particoes
};