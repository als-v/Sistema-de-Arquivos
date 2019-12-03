#include "estruturas/structures.h"
#include "funcoes/funct.h"

void start(FILE* file){
    struct fileSistem* fileSistem;

    fileSistem = start_file_sistem(file);

    if (fileSistem == NULL){
        printf("Erro ao criar o sistema de arquivos!!\n");
    }

    char* nome;
    char* identificacao;
    int op;
    while(1){
        printf("Deseja fazer um novo diretorio ou um novo arquivo? (1 - diretorio|2 - arquivo): ");
        scanf("%d", &op);

        if(op == 1){
            identificacao = "D";
        }else if (op == 2){
            identificacao = "A";
        }else{
            printf("Erro, opcao invalida!");
            op = 3;
        }
        if(op != 3){
            printf("Digite o nome do diretorio/arquivo que quer fazer: ");
            scanf("%s", &nome);

            //cria_novo_bloco(fileSistem, nome, identificacao);
        }
    }

};