#include <unistd.h>
#include "estruturas/structures.h"
#include "funcoes/funct.h"

struct fileSistem* start(FILE* file){
    struct fileSistem* fileSistem;
    struct Bloco* b;
    fileSistem = start_file_sistem(file);

    if (fileSistem == NULL){
        printf("Erro ao criar o sistema de arquivos!!\n");
    }

    return fileSistem;
    /* to testando o shell (comentei por isso)
    char nome[100];
    char* identificacao;
    int op = 2;
    int a = 0;
    char dires[8][10] = {"Lanso", "a", "braba", "desafio", "doido", "memo", "alek", "garaio"};
    int i = 0;
    while(i < 8){
        // printf("Digite o nome do diretorio: ");
        // gets(nome);
        cria_novo_diretorio(fileSistem, fileSistem->Bloco, dires[i]);
        print_D(fileSistem->Bloco);
        print_S(fileSistem->superBloco);
        //print_D(b);
        i++;
    }

    //testando remoção
    exclui_diretorio(fileSistem, fileSistem->Bloco->subdiretorios->diretorio);
    print_D(fileSistem->Bloco);
    */
};