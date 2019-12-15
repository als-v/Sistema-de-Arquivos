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
    char dires[3][10] = {"Lanso", "a", "braba"};
    int i = 0;
    while(i < 3){
        // printf("Digite o nome do diretorio: ");
        // gets(nome);
        cria_novo_diretorio(fileSistem, fileSistem->Bloco, dires[i]);
        print_D(fileSistem->Bloco);
        //print_D(b);
        i++;
    }

    //testando remoção
    exclui_diretorio(fileSistem, fileSistem->Bloco->subdiretorios->prox->prox->diretorio);
    print_D(fileSistem->Bloco);
};