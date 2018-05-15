#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int nPorEstacao[5] = {0, 0, 0, 0, 0}, estTx[10], cursor = 0;
pthread_mutex_t estacao[5];

void *taxi(void *id)
{
	pthread_mutex_lock(&estacao[cursor]);
	long tid = *((long *)id);
	while(1){
		if(nPorEstacao[cursor] < 2){
			estTx[tid] = cursor;
			nPorEstacao[cursor]++;
			printf("estacao %d tem o taxi %ld\n", cursor, tid);
			pthread_mutex_unlock(&estacao[estTx[tid]]);
			sleep(2);
			pthread_mutex_lock(&estacao[estTx[tid]]);
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
		pthread_mutex_unlock(&estacao[estTx[tid]]);
	}
}

int main()
{
	pthread_t tx[10];
	int i;
	long *id[10];
	pthread_mutex_t estacao = PTHREAD_MUTEX_INITIALIZER;
	for(i = 0; i < 10; i++){
		id[i] = (long *) malloc(sizeof(long));
		*id[i] = i;
		pthread_create(&tx[i], NULL, taxi, (void *) id[i]);
	}
	pthread_exit(NULL);
}