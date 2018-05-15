#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex[2];
int nPorTaxi[2] = {0, 0}, j = -1;
bool direcao = 0; //0 = esquerda; 1 = direita

void *Filas(void *id)
{
	long tid = *((long *)id);
	while(1){
		j++;
		pthread_mutex_lock(&mutex[j]);
		if(direcao == 0){
			if(nPorTaxi[0] < 4){
				nPorTaxi[0]++;
				sleep(1);
			}
		}
		if(j == 2)
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