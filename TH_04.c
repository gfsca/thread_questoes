#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int nPorEstacao[5] = {0, 0, 0, 0, 0}, cursor = 0;
pthread_mutex_t estacao[5];
pthread_cond_t cheio[5];
pthread_cond_t vazio[5];
for(j = 0; j < 5; j++){
	pthread_mutex_t estacao[i] = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t cheio[i] = PTHREAD_COND_INITIALIZER;
	pthread_cond_t vazio[i] = PTHREAD_COND_INITIALIZER;
}

void *taxi(void *id)
{
	pthread_mutex_lock(estacao[i])
	while(1){
		if(nPorEstacao[cursor] < 2){
			nPorEstacao[cursor]++;
			//bota a thread para esperar
			nPorEstacao[cursor]--;
		}else{
			if(cursor == 4){
				if(nPorEstacao[cursor] > 1){
					cursor = 0;
				}
			}else{
				cursor++;
			}
		}
	}
}

int main(){
	pthread_t tx[10];
	pthread_mutex_t estacao[5];
	int *id[10], i;
	for(i = 0; i < 10; i++){
		id[i] = (int *) malloc(sizeof(int));
		*id[i] = i;
		pthread_create(&tx[i], NULL, taxi, (void *) id[i]);
	}
	pthread_exit(NULL);
}