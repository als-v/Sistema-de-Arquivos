#ifndef FUNCTH
#define FUNCTH

#include <stdio.h>
#include "funct.c"

/* cria um novo diretorio */
void cria_novo_bloco(struct fileSistem* fileSistem, char* nome, char* identificacao);

/* atualiza o subdiretorio */
void add_diretorio(struct Bloco* diretorio, struct Bloco* novo_diretorio);

/* atualiza sistemas de arquivos */
void update(struct fileSistem* f, struct Bloco* bloco);

#endif