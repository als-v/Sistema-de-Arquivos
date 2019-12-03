#include <stdio.h>
#include "src/src.c"

int main(){
    FILE* arquivo;
    char* nome = "disc.dsc";

    arquivo = fopen(nome, "wb");
    
    start(arquivo);

    return(0);
};