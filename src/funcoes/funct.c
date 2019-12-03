#ifndef FUNCT
#define FUNCT

#include <stdio.h>
#include "../estruturas/structures.h"

struct Bloco* cria_novo_bloco(struct fileSistem* fileSistem, char* nome, char* identificacao){
    if(fileSistem->superBloco->blocos_livres > 0){
        printf("Implementa\n");
    }else{
        printf("Erro na criacao de um novo diretorio/arquivo!\nO sistema nao possui mais espaco!\n");
        return NULL;
    }
};

#endif