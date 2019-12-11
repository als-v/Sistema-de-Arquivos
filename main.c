/**	
 * Code: main.c
 * Descrição: Implementação de um sistema de arquivos simulado
 * 
 * Autores: Lucas Souza Santos, Alisson da Silva Vieira
 * Data: 10/12/2019
 */

#include <stdio.h>
#include "src/src.c"

int main(){
    FILE* arquivo;
    char* nome = "disc.dsc";

    arquivo = fopen(nome, "wb");

    start(arquivo);

    return(0);
};