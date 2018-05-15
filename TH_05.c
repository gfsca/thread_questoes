#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
int nPorTaxi[2] = {0, 0}; //array que salva no indice 0 a quantidade de pessoas que estao no taxi na direcao 0, e salva 1 no indice 1 a quantidade de pessoas que estao no taxi na direcao 1
int direcao = 0; //0 = indica a direcao de um taxi(para intuicao, imagine 0 como sendo esquerda). 1 = mesma coisa de quando eh 0, mas imagine como sendo a direcao direita
int N; //numero de pessoas que existe em cada uma das filas

void *Filas(void *id) //estrutura das threads nas quais controlamos quando os taxis vao sair e chegar, assim como organizar a entrada das pessoas
{
	long tid = *((long *)id);
	int nFila = N;
	while(nFila > 0){ // uma fila(thread) ira rodar ate que ainda existam pessoas nela
		pthread_mutex_lock(&mutex);
		printf("Fila %ld tem %d pessoas\n", tid, nFila); //efeito de debug e para mostrar o funcionamento
		if(direcao == 0){	//inicialmente a direcao eh 0 e ira sendo modificada para a direcao oposta a cada iteracao
			if(nPorTaxi[0] < 4){	//aqui vamos verificar se o numero de pessoas em um taxi eh igual a 4, caso seja menos, vamos incrementar o numero de pessoas no determinado taxi, modificar a direcao e ainda decrementar as pessoas na thread(fila)
				direcao = 1;
				nPorTaxi[0]++;
				nFila--;
				pthread_mutex_unlock(&mutex);
				sleep(1);	//delay para que a pessoa embarquem no taxi
				pthread_mutex_lock(&mutex);
			}else{
				pthread_mutex_unlock(&mutex);
				sleep(3);	//delay para que um taxi cheio saia e outro vazio tome seu lugar
				pthread_mutex_lock(&mutex);
				nPorTaxi[0] = 0;
			}
		}else{
			if(nPorTaxi[1] < 4){
				direcao = 0;
				nPorTaxi[1]++;
				nFila--;
				pthread_mutex_unlock(&mutex);
				sleep(1);
				pthread_mutex_lock(&mutex);
			}else{
				pthread_mutex_unlock(&mutex);
				sleep(3);
				pthread_mutex_lock(&mutex);
				nPorTaxi[1] = 0;
			}
		}
		pthread_mutex_unlock(&mutex);
	}
	pthread_exit(NULL);
}

int main()
{
	printf("Digite o numero de pessoas que terá em cada fila: ");
	scanf("%d", &N);
	pthread_t fila[3];
	int i;
	long int *id[3];	//esse id serve para identificar cada uma das filas
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	for(i = 0; i < 3; i++){	//inicializacao das threads
		id[i] = (long *) malloc(sizeof(long));
		*id[i] = i;
		pthread_create(&fila[i], NULL, Filas, (void *) id[i]);
	}
	pthread_exit(NULL);
}