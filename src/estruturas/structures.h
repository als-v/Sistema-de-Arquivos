#ifndef STRUCTURES2
#define STRUCTURES2

#include <stdio.h>

#include "structures.c"

/* Funcao que inicia o arquivo */
struct superBloco* start_superbloco(FILE* file);

/* Funcao que inicia o bloco root */
struct Bloco* start_bloco(FILE* file);

/* Funcao que inicia a memoria */
struct Armazenamento* start_memoria(FILE* file);

/* Funcao que inicia a FAT */
struct fat* start_fat(FILE* file);

/* Funcao que inicia a tabela */
void start_tabela(FILE* file, struct fileSistem* fileSistem);

/* Funcao que inicia o vetor FAT */
void inicia_vetor_fat(struct fat* fat);

/* Funcao que inicia o vetor de blocos */
void inicia_vetor_armazenamento(struct Armazenamento* a);

/* printar super Bloco */
void print_S(struct superBloco* b);

/* printar todos os diretorios */
void print_D(struct Bloco* b);

/* printar a memoria */
void print_M(struct Armazenamento* m);

/* printar a FAT */
void print_F(struct fat* fat);

/* Funcao inicializadora */
struct fileSistem* start_file_sistem(FILE* file);

/* Procurar nome diretorio */
int procurar_dir(char* nome, struct Bloco* b);

/* Devolve diretorio*/
struct Bloco* devolve_dir(char* nome, struct Bloco* b);

#endif