#ifndef STRUCTURES2
#define STRUCTURES2

#include <stdio.h>

#include "structures.c"

/* Funcao que inicia o arquivo */
struct superBloco* start_superbloco(FILE* file);

/* printar super Bloco */
void print_SP(struct superBloco* b);

/* Funcao que inicia o bloco root */
struct Bloco* start_bloco(FILE* file);

/* printar todos os diretorios */
void print_D(struct Bloco* b);

/* Funcao inicializadora */
struct fileSistem* start_file_sistem(FILE* file);

#endif