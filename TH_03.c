#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int quantidade_jogadores;
int quantidade_rodadas;
int jogada[100];

pthread_barrier_t barrier;

void *pedra_papel_tesoura(void *threadid){
	for (int i = 0; i <quantidade_rodadas; ++i)	{
		jogada[*(int*) threadid] = randomize()%3;
		pthread_barrier_wait(&barrier);
	}

	//Liberando Thread
	pthread_exit(NULL);
}


//Printando Rodada
/*void printar_rodada(){

		printf("Rodada: %d\n", i);
		for (int j = 0; j < quantidade_jogadores; ++j){
			if (jogada[j] == 0)
				printf("Jogador %d: Pedra\n", j);
			if (jogada[j] == 1)
				printf("Jogador %d: Papel\n", j);
			if (jogada[j] == 2)
				printf("Jogador %d: Tesoura\n", j);
		}
		printf("\n\n");
}
*/

int randomize(){ // função retorna um número aleatório que vai até RAND_MAX, usar % para limitar seu range.
    srand((unsigned)time(NULL));
    return rand();
}


int main(){
	printf("Digite a quantidade de Jogadores\n");
	scanf("%d", &quantidade_jogadores);
	printf("Digite a quantidade de rodadas \n");
	scanf("%d", &quantidade_rodadas);

	pthread_t thread[quantidade_jogadores];
	int *taskids[quantidade_jogadores];
	int rc;

	//Criando Barreira
	pthread_barrier_init(&barrier, NULL, quantidade_jogadores);
	
	for (int i = 0; i < quantidade_jogadores; ++i){
		printf("Criando a thread %d \n", i); // Tirar depois!
		taskids[i] = (int *) malloc(sizeof(int));
		*taskids[i] = i;
		rc = pthread_create(&thread[i], NULL, pedra_papel_tesoura, (void *) taskids[i]);
		
		//Caso de erro na criação das threads!
		if (rc){
			printf("ERRO; codigo de retorno: %d\n", rc);
		exit(-1);
			}
	}

	for (int i = 0; i < quantidade_jogadores; ++i){
		pthread_join(thread[i], NULL);
	}

	pthread_barrier_destroy(&barrier);

	//Liberando Thread
	pthread_exit(NULL);

	printf("Funcionou krai e arthur eh viado\n");
	
	return 0;
}
