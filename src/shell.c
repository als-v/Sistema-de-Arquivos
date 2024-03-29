/**	
 * Code: shell.c
 * Descrição: Implementação de interface de shell que aceita comandos de usuário 
 * e, então, executa cada comando em um processo separado.
 * 
 * Autores: Lucas Souza Santos, Alisson da Silva Vieira
 * Data: 22/09/2019
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "src.c"

#define MAX_LINE 80 /* O comando de tamanho máximo */

struct fileSistem* fileSistem;

struct comando { /* armazena um comando e seu numero */
    char cmd[MAX_LINE/2 + 1];
    int numComando; 
};

struct fileSistem* inicia_sistema_arquivos(FILE* arq){
    return start(arq);
}

/* Função que executa o comando especificado pelo usuário */
int execucao(char str[MAX_LINE/2 + 1], struct comando *historico, int* histIndex, int* numComando) {
    char *args[MAX_LINE/2 + 1]; /* argumentos de linha de comando */
    int espera = 1; /* define se o pai esperará ou não o filho */
    char *token; /* token que armazena um argumento do comando por vez */

    /* armazena o comando no historico */
    strcpy(historico[*histIndex].cmd, str);
    historico[*histIndex].numComando = *numComando;
    (*numComando)++;

    if (*histIndex == 9){ /* é permitido armazenar apenas 10 comandos */
        *histIndex = 0;
    } else {
        (*histIndex)++; /* incrementa no índice do historico */
    }

    token = strtok(str, " ");
    args[0] = token; /* o comando vai para a primeira posição de args */

    int i = 1; /* ponteiro do args */
    do {
        token = strtok('\0', " ");  /* a pesquisa deve continuar no ponteiro anterior e buscar pelo espaço em branco. */
    
        if(token) /* se ainda há argumentos */
        {
            if(strcmp(token, "&") == 0){ /* caso possuir o argumento '&' */
                espera = 0;
            } else {
                args[i]= token; /* os argumentos vão para as demais posições de args */
                i++;
            }
        } 
    } while(token);

    args[i] = token; /* a última posição recebe NULL */

    int pid = fork();
    
    if(!pid) { /* se for o processo filho, executa o comando solicitado */
        int disco = 0; /* indica com qual disco está mexendo: 0 - real 1 - simulado */
        char teste[5];
        char teste1[100] = {0};
        int w, j;
        w = j = 0;
        if(!strcmp(args[0], "mkdir")){
            strncpy(teste, args[1], 3);
            teste[4] = '\0';
            if(!strcmp(teste, "dsc")){
                disco = 1; /* indica que se trata do disco simulado */
                memcpy(teste1, &args[1][4], strlen(args[1])-3);
                printf("esse %s\n", teste1);
                fileSistem->diretorio_atual = fileSistem->Bloco;
                cria_novo_diretorio(fileSistem, fileSistem->diretorio_atual, teste1);
            }
        } else if (!strcmp(args[0], "cd")){
            strncpy(teste, args[1], 3);
            teste[4] = '\0';
            if(!strcmp(teste, "dsc")){
                disco = 1; /* indica que se trata do disco simulado */
                for(w = 4, j = 0; w < strlen(args[1]); w++, j++){
                    teste1[j] = args[1][w];
                }
                teste1[j] = '\0';
                if(procurar_dir(args[1], fileSistem->diretorio_atual) == 1){
                    fileSistem->diretorio_atual = devolve_dir(args[1], fileSistem->diretorio_atual);
                }
            }
        } else if (!strcmp(args[0], "ls")){
            strncpy(teste, args[1], 3);
            teste[4] = '\0';

            print_D(fileSistem->diretorio_atual);
        }
        if(disco == 0){
            execvp(args[0], args); /* executa o comando no disco real */
        }
    }else{
        if (espera) {
            wait(NULL); /* Os processos serão executados concorrentemente */
        }
    }
    return 0;
}

int main(void) {
    struct comando historico[10]; /* cada posição do vetor é um comando */ 
    int numComando = 1; /* conta quantos comandos foram executados */
    int histIndex = 0; /* indice do histórico (vai de 0 a 9) */
    int should_run = 1; /* flag para determinar quando encerrar o programa */
    char str[MAX_LINE/2 + 1]; /* string que vai capturar a entrada do teclado ou o comando do histórico */

    char* nome = "disc.dsc";
    FILE* arquivo = fopen(nome, "wb");

    fileSistem = inicia_sistema_arquivos(arquivo);

    while (should_run) {
        print_D(fileSistem->diretorio_atual);
        printf("osh>");
        fflush(stdout);
        
        gets(str); /* captura os valores do teclado */

        if(strcmp(str, "exit") == 0) {
            should_run = 0; /* fim do programa */

        } else if (strcmp(str, "!!") == 0) {
            if(numComando == 1) { /* Ainda não há comandos no histórico */
                printf("Nenhum comando no histórico\n");
            } else {
                strcpy(str, historico[histIndex-1].cmd); /* string recebe comando mais recente do histórico */
                execucao(str, historico, &histIndex, &numComando); /* executa o comando mais recente do histórico */
            }

        } else if (str[0] == '!') {
            int comandoRequerido = 0; /* armazena o número do comando a ser executado no histórico */
            for(int cont = 1; str[cont] != '\0'; cont++) { /* Esse laço de repetição transforma os caracteres depois de '!' em um número inteiro */
                if(cont > 1) {
                    comandoRequerido *= 10;
                }
                comandoRequerido += (str[cont]-48); /* técnica pra capturar inteiro de char */
            }

            int haComando = 0;
            for(int j = 0; j < 10; j++) { /* verifica se há um comando correspondente no histórico de acordo com o número */
                if(historico[j].numComando == comandoRequerido) {
                    strcpy(str, historico[j].cmd);
                    haComando = 1;
                }
            }
            if(!haComando) {
                printf("Nenhum comando correspondente no histórico\n");
            } else {
                execucao(str, historico, &histIndex, &numComando); /* executa o comando do histórico */
            }

        } else if (strcmp(str, "history") == 0) { /* usuário quer ver o histórico */
            int contHist;
            for(contHist = histIndex-1; contHist >=0 ; contHist--) {
                printf("%d %s\n", historico[contHist].numComando, historico[contHist].cmd);
            }
            if(numComando > 10) {
                for(contHist = 9; contHist >= histIndex; contHist--) {
                    printf("%d %s\n", historico[contHist].numComando, historico[contHist].cmd);
                }
            }
        } else { /* Executa o comando digitado no teclado */
            execucao(str, historico, &histIndex, &numComando);
        }
    }
    return 0;
}