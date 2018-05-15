//header
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
//constantes
#define C 1000
#define R 1000
#define S 1000
#define BUFFER_ROT 10
#define BUFFER_SER 10
#define I 1000000 //Numero maximo do identificador
//variaveis globais

int buffer_roteador[BUFFER_ROT] = 0;
int buffer_servidor[S][BUFFER_SER] = 0;
short int offset_roteador = 0;


void *cliente(){
    int num_ident, num_servidor;
    num_ident = randomize()%I;
    num_servidor = randomize()%S;
    if (num_servidor < BUFFER_ROT){
        offset_roteador++;
        buffer_roteador[offset_roteador] = num_servidor;   
    }
    else
        //espera liberar buffer
}


void *roteador(){
    for (int i = 0; i < BUFFER_ROT; ++i){
        //manda pro servidor
        buffer_roteador[i] = 0;
    }
}


void *servidor(void *threadid){
    for (int i = 0; i < buffer_servidor; ++i){
        buffer_servidor[*(int*) threadid][i] = 0;        
    }
}

int randomize(){ // função retorna um número aleatório que vai até RAND_MAX, usar % para limitar seu range.
    srand((unsigned)time(NULL));
    return rand();
}


int main(){
   
    pthread_create(pthread_t thread_roteador, NULL, roteador, NULL);

    for (int i = 0; i < S; ++i){
        taskids[i] = (int *) malloc(sizeof(int));
        *taskids[i] = i;
        pthread_create(pthread_t thread_servidores[i], NULL, servidor, (void *) taskids[i]);
    }

    for (int i = 0; i < C; ++i){
        pthread_create(pthread_t thread_clientes[i], NULL, cliente, NULL);
    }

    return 0
}
