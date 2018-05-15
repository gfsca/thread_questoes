#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

//Variaveis globais
int quantidade_jogadores;
int quantidade_rodadas;
int jogada[10000];

//Declarando barreira
pthread_barrier_t barrier;

//Thread pedra papel e tesoura
void *pedra_papel_tesoura(void *threadid){
	int id = *((int *)threadid);
	for (int i = 0; i <quantidade_rodadas; ++i)	{
		//Recebendo um valor aleatorio que equivalerá a pedra papel ou tesoura
		jogada[id] = randomize()%3;
		if (jogada[id] == 0)
			printf("Jogador %d: Pedra\n", id);

		if (jogada[id] == 1)
			printf("Jogador %d: Papel\n", id);

		if (jogada[id] == 2)
			printf("Jogador %d: Tesoura\n", id);

		//Barreira para esperar todas as threads acabarem a rodada
		pthread_barrier_wait(&barrier);
	}

	//Liberando Thread
	pthread_exit(NULL);
}

//Função para pegar um numero aleatorio atravez do clock do PC
int randomize(){ // função retorna um número aleatório que vai até RAND_MAX, usar % para limitar seu range.
    srand((unsigned)time(NULL));
    return rand();
}


int main(){
	//Recebendo a quantidade de jogadores e a quantidade de rodadas
	printf("Digite a quantidade de Jogadores\n");
	scanf("%d", &quantidade_jogadores);
	printf("Digite a quantidade de rodadas \n");
	scanf("%d", &quantidade_rodadas);

	//Declarando as threads e os identificadores
	pthread_t thread[quantidade_jogadores];
	int *taskids[quantidade_jogadores];
	int rc;

	//Criando Barreira
	pthread_barrier_init(&barrier, NULL, quantidade_jogadores);
	
	//Criando as threads
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

	//Dando join nas threads
	for (int i = 0; i < quantidade_jogadores; ++i){
		pthread_join(thread[i], NULL);
	}

	//Destruindo a barreira
	pthread_barrier_destroy(&barrier);

	//Liberando Thread
	pthread_exit(NULL);

}
