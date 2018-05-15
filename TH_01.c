#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define L 10
#define NUM_ARQUIVOS 10
#define NUM_THREADS 10

char end_arquivo[NUM_ARQUIVOS][255] // array com todos os arquivos que vão ser abertos, defini 255 caracteres p/ o tamanho do nome do arquivo aleatoriamente
char voos[L][25];
bool arqvs[NUM_ARQUIVOS];
pthread_mutex_t mymutex[L];



void * atualiza_linha(){
    int i,k;
    FILE *arqv;
    char string[25];
    for(i = 0; i < NUM_ARQUIVOS; i++){
        if(arqvs[i] == FALSE){
            arqv = fopen(end_arquivo[i][255],"r");
            while(fgets(string,25,arqv) != NULL){
            pthread_mutex_lock(&mymutex[string[0]]);//olhar se pode fazer isso
            fgets(string,25,arqv);
            voos[string[0]] = string;
            arqvs[i] = TRUE;
            //pode dar unlock aqui?
            //printa
            for(k=0,k<L,k++){
                if(k%6) printf(ANSI_COLOR_RED "" ANSI_COLOR_RESET);
                if(k%6) printf(ANSI_COLOR_GREEN "" ANSI_COLOR_RESET);
                if(k%6) printf(ANSI_COLOR_YELLOW "" ANSI_COLOR_RESET);
                if(k%6) printf(ANSI_COLOR_BLUE "" ANSI_COLOR_RESET);
                if(k%6) printf(ANSI_COLOR_MAGENTA "" ANSI_COLOR_RESET);
                if(k%6) printf(ANSI_COLOR_CYAN "" ANSI_COLOR_RESET);
            }
            sleep(2);
            pthread_mutex_unlock(&mymutex[numerodomutex]);
            }
        }
    } 
}

int main(){
    int j;
    pthread_t thread[NUM_THREADS]
    for(j = 0; j < NUM_ARQUIVOS;j++)arqvs[j] = FALSE;
    for(j = 0; j < L, j++) mymutex[j] = PTHREAD_MUTEX_INITIALIZER;
    for(j = 0;j < NUM_THREADS;j++) pthread_create(&thread[j], NULL, atualiza_linha, NULL);
    for(j = 0;j < NUM_THREADS;j++) pthread_join(thread[j],NULL)       
    return 0;
}