#include <unistd.h>
#include "estruturas/structures.h"
#include "funcoes/funct.h"

void start(FILE* file){
    struct fileSistem* fileSistem;
    struct Bloco* b;
    fileSistem = start_file_sistem(file);

    if (fileSistem == NULL){
        printf("Erro ao criar o sistema de arquivos!!\n");
    }

    char nome[100];
    char* identificacao;
    int op = 2;
    int a = 0;
    while(1){
        printf("Digite o nome do diretorio: ");
        gets(nome);
        cria_novo_diretorio(fileSistem, fileSistem->Bloco, nome);
        print_D(fileSistem->Bloco);
        //print_D(b);
    }
};