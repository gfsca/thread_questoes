//header
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
//constantes
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define L 10
#define NUM_ARQUIVOS 10
#define NUM_THREADS 10
#define FALSE 0
#define TRUE 1
//variaveis globais
char end_arquivo[NUM_ARQUIVOS][255]; // array com todos os arquivos que vão ser abertos, defini 255 caracteres p/ o tamanho do nome do arquivo aleatoriamente
char voos[L][25];
int arqvs[NUM_ARQUIVOS];
pthread_mutex_t mymutex[L];

void *atualiza_linha(){
    FILE *arqv;
    char string[25];
    int numero;
    for(int i = 0; i < NUM_ARQUIVOS; i++){
        if(arqvs[i] == FALSE){//se nenhuma thread abriu esse arquivo, ele é aberto
            arqvs[i] = TRUE;//primeiramente indica que o arquivo já foi aberto/está aberto
            arqv = fopen(end_arquivo[i], "r");//abre o arquivo conforme o array de endereços que foi dado
            while(fgets(string, 25, arqv) != NULL){//puxa as linhas de dentro do arquivo até o fim do arquivo
                numero = (int) string[0];//
                pthread_mutex_lock(&mymutex[numero]);//olhar se pode fazer isso
                fgets(string, 25, arqv);
                for (int j = 0; j < 25; ++j){
                    voos[numero][j] = string[j];
                }
                for(int k = 0; k < L; k++){//printa colorido, seis cores diferentes
                    if(k%6 == 0) printf(ANSI_COLOR_RED "%s" ANSI_COLOR_RESET,voos[k]);
                    if(k%6 == 1) printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET,voos[k]);
                    if(k%6 == 2) printf(ANSI_COLOR_YELLOW "%s" ANSI_COLOR_RESET,voos[k]);
                    if(k%6 == 3) printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET,voos[k]);
                    if(k%6 == 4) printf(ANSI_COLOR_MAGENTA "%s" ANSI_COLOR_RESET,voos[k]);
                    if(k%6 == 5) printf(ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET,voos[k]);
                }
                sleep(2);
                pthread_mutex_unlock(&mymutex[numero]);
            }
        }
    }
    pthread_exit(NULL); 
}

int main(){
    char caracter;
    int j;
    for (int i = 0; i < NUM_ARQUIVOS; ++i){//pega o endereço de todos os N arquivos que devem ser abertos
        j = 0;
        printf("Digite todos os endereços de todos os arquivos que deverão ser abertos\n");
        while(scanf("%c", &caracter) != '\n'){
            end_arquivo[i][j] = caracter;
            j++;
        }

        
    }

    pthread_t thread[NUM_THREADS];

    for(int j = 0; j < NUM_ARQUIVOS; j++)
        arqvs[j] = FALSE;// essa variável serve para indicar se o arquivo já foi aberto ou não

    for(int j = 0; j < L; j++) // inicializa os mutexes 
        pthread_mutex_init(&mymutex[j], NULL);
    
    for(int j = 0; j < NUM_THREADS; j++)// cria as threads 
        pthread_create(&thread[j], NULL, atualiza_linha, NULL);
    
    for(int j = 0; j < NUM_THREADS; j++)// join nas threads
        pthread_join(thread[j],NULL);  
   
    pthread_exit(NULL);
}
