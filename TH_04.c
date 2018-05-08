#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int nPorEstacao[5] = {0, 0, 0, 0, 0};

void *taxi()
{
	int i;
	while(1){
		for(i = 0; i < 5;){
			if(nPorEstacao[i] < 2){
				nPorEstacao[i]++;
				//bota a thread para esperar
				nPorEstacao[i]--;
			}else{
				i++;
			}
		}
	}
}

int main(){
	int i;
	pthread_t tx[10];
	pthread_mutex_t estacao[5];
	for(i = 0; i < 5; i++){
		pthread_mutex_t estacao[i] = PTHREAD_MUTEX_INITIALIZER;
	}
	for(i = 0; i < 10; i++){
		int rc = pthread_create(&d[i], NULL, taxi, NULL);
	}
	pthread_exit(NULL);
}