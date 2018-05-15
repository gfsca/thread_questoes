#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex[2];
int nPorTaxi[2] = {0, 0}, j = -1;
bool direcao = 0; //0 = esquerda; 1 = direita
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;

void *Filas(void *id)
{
	long tid = *((long *)id);
	while(1){
		j++;
		pthread_mutex_lock(&mutex[j]);
		if(direcao == 0){
			if(nPorTaxi[0] < 4){
				nPorTaxi[0]++;
				usleep(200000);
			}else{
				//mandar sinal que esta cheio
				//esperar os 500 ms
				// voltar o numero de pessoas no taxi para 0
			}
		}else{
			if(nPorTaxi[1] < 4){
				nPorTaxi[1]++;
				usleep(200000);
			}
		}
	}
	pthread_mutex_unlock(&mutex);
}

int main()
{
	pthread_t fila[3];
	int i;
	int *id[3];
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	for(i = 0; i < 3; i++){
		id[i] = (long *) malloc(sizeof(long));
		*id[i] = i;
		pthread_create(&fila[i], NULL, Filas, (void *) id[i]);
	}
	pthread_exit(NULL);
}