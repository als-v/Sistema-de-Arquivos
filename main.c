#include <stdio.h>
#include "src/estructures.c"

int main(){
    FILE* arquivo;
    char* nome = "disc.dsc";

    arquivo = fopen(nome, "wb");
    
    start(arquivo);

    return(0);
};