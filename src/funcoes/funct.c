#ifndef FUNCT
#define FUNCT

#include <stdio.h>
#include "../estruturas/structures.h"

struct Bloco* cria_novo_diretorio(struct fileSistem* fileSistem, struct Bloco* diretorio, char* nome){
    if(fileSistem->superBloco->blocos_livres > 0){
        // criando o novo bloco
        struct Bloco* novo_bloco = (struct Bloco*) malloc(sizeof(struct Bloco));
        novo_bloco->nome = nome;
        novo_bloco->identificacao = "D";
        novo_bloco->diretorio_anterior = diretorio;
        novo_bloco->subdiretorios = NULL;
        novo_bloco->proxima_particao = NULL;

        //atualizando o diretorio atual
        struct Bloco* teste;
        teste = diretorio->subdiretorios;
        if(teste == NULL){
            diretorio->subdiretorios = (struct Bloco*) malloc(sizeof(struct Bloco));
            diretorio->subdiretorios = novo_bloco;
        }else{
            while(teste != NULL){
                teste = teste->subdiretorios;
            }
            teste = (struct Bloco*) malloc(sizeof(struct Bloco));
            teste = novo_bloco;
        
            struct Bloco* teste2;
            teste2 = diretorio->subdiretorios;
            while(teste2->subdiretorios != NULL){
                teste2 = teste2->subdiretorios;
            }
            teste2 = teste;
        }
        return novo_bloco;
    }else{
        printf("Erro na criacao de um novo diretorio/arquivo!\nO sistema nao possui mais espaco!\n");
        return NULL;
    }
};

#endif