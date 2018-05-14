#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int nPorEstacao[5] = {0, 0, 0, 0, 0}, estTx[10], cursor = 0;
pthread_mutex_t estacao[5];

void *taxi(void *id)
{
	pthread_mutex_lock(estacao[cursor]);
	int tid = *((int *)id);
	while(1){
		if(nPorEstacao[cursor] < 2){
			estTx[tid] = cursor;
			nPorEstacao[cursor]++;
			pthread_mutex_unlock(estacao[estTx[tid]]);
			sleep(1);
			pthread_mutex_lock(estacao[estTx[tid]]);
			nPorEstacao[estTx[tid]]--;
		}else{
			if(cursor == 4){
				if(nPorEstacao[cursor] >= 2){
					cursor = 0;
				}
			}else{
				cursor++;
			}
		}
	}
	pthread_mutex_unlock(estacao[estTx[tid]]);
}

int main()
{
	pthread_t tx[10];
	int *id[10], i;
	int j;
	for(j = 0; j < 5; j++){
		pthread_mutex_t estacao[j] = PTHREAD_MUTEX_INITIALIZER;
	}
	for(i = 0; i < 10; i++){
		id[i] = (int *) malloc(sizeof(int));
		*id[i] = i;
		pthread_create(&tx[i], NULL, taxi, (void *) id[i]);
	}
	pthread_exit(NULL);
}