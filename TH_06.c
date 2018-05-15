//header
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
//constantes
#define C 100
#define R 100
#define S 100
#define BUFFER_ROT 5
#define BUFFER_SER 10
//variaveis globais
int buffer_roteador[BUFFER_ROT];
int buffer_servidor[S][BUFFER_SER];
int counter_req = 0;

pthread_mutex_t mutex_roteador = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_servidor[S];
pthread_mutex_t contador_req;


void *cliente(void *threadid){
    int num,count = 0;
    for(int i = 0; i < R ; i++){
        scanf("%d", &num); 
        for(int i = 0; i < BUFFER_ROT; i++){
            if(buffer_roteador[i] == 0){
                pthread_mutex_lock(&mutex_roteador);
                buffer_roteador[i] = num;//preenche o buffer do roteador com um numero dado pelo cliente
                pthread_mutex_unlock(&mutex_roteador);
                i = BUFFER_ROT;
                count = 0;
            }
            else{
                count++;
            }
            if(count == BUFFER_ROT){//garante o loop "infinito" no buffer, até que coloque o "pacote" no roteador
                count = 0;
                i = 0;
            }
        }
    }
    pthread_exit(NULL);
}


void *roteador(){
    int num_servidor = randomize()%S, countr;//pega um servidor aleatório
    for (int i = 0; i < BUFFER_ROT; ++i){//itera pelo buffer do roteador
        if(buffer_roteador[i]>0){//se o buffer do roteador estiver preenchido, mandamos o pacote para um servidor aleatório
            for(int j = 0; j < BUFFER_SER;j++){
                if(buffer_servidor[num_servidor][j] == 0){

                    pthread_mutex_lock(&mutex_servidor[num_servidor]);
                    buffer_servidor[num_servidor][j] = buffer_roteador[i];//colocamos o pacote do roteador no servidor
                    pthread_mutex_unlock(&mutex_servidor[num_servidor]);

                    pthread_mutex_lock(&contador_req);
                    counter_req++;//como foi feita uma requisição, contamos ela para quando atingir o total de requisições/todos clientes, avisarmos ao servidor
                    pthread_mutex_unlock(&contador_req);

                    pthread_mutex_lock(&mutex_roteador);
                    buffer_roteador[i] = 0;//limpamos o buffer do roteador
                    pthread_mutex_unlock(&mutex_roteador);

                    countr = 0;
                }
                else
                    countr++;
                if(countr == BUFFER_SER){
                    countr = 0;
                    j = 0;
                }
            }
        }
    }
    if(R*C == counter_req)
    pthread_exit(NULL);
}

void *servidor(void *threadid){
    int id = *((int *)threadid);//número da thread
    int i;
    while(1){
        if(counter_req == R*C) pthread_exit(NULL);//se a quantidade de requisições já feitas for igual ao total de requisições (clientes * requisições), conforme o dito na questão
        i = (i + 1)%BUFFER_SER;
        if(buffer_servidor[id][i] != 0){
                pthread_mutex_lock(&mutex_servidor[id]);
                buffer_servidor[id][i] = 0;
                pthread_mutex_unlock(&mutex_servidor[id]);
        }
    }
    pthread_exit(NULL);
}

int randomize(){ // função retorna um número aleatório que vai até RAND_MAX, usar % para limitar seu range.
    srand((unsigned)time(NULL));
    return rand();
}


int main(){

    for (int i = 0; i < BUFFER_ROT; ++i){
        buffer_roteador[BUFFER_ROT] = 0;
    }
    for (int j = 0; j < S; ++j){   
        for (int i = 0; i < BUFFER_SER; ++i){
            buffer_servidor[S][BUFFER_SER] = 0;
        }
    }

    for (int i = 0; i < S; ++i)
        pthread_mutex_init(&mutex_servidor[i], NULL);
    
    //Declarando as threads e os identificadores
    pthread_t thread_servidores[S];
    pthread_t thread_clientes[C];
    pthread_t thread_roteador;
    int *taskids[S];
    int rc;

    for (int i = 0; i < S; ++i){
        taskids[i] = (int *) malloc(sizeof(int));
        *taskids[i] = i;
        rc = pthread_create(&thread_servidores[i], NULL, servidor, (void *) taskids[i]);
    }

    pthread_create(&thread_roteador, NULL, roteador, NULL);

    for (int i = 0; i < C; ++i){
        pthread_create(&thread_clientes[i], NULL, cliente, NULL);
    }

    //Dando join nas threads
    pthread_join(thread_roteador, NULL);
    for (int i = 0; i < C; ++i){
        pthread_join(thread_clientes[i], NULL);
    }
    for (int i = 0; i < S; ++i){
        pthread_join(thread_servidores[i], NULL);
    }

    pthread_exit(NULL);
}
