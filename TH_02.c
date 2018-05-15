//header
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <stdlib.h>

#define I 100

//Variaveis Globais
double matriz_1[I][I], matriz_2[I], matriz_result[I], matriz_temp[I];
int num, quant_threads;

//Declarando Barreira
pthread_barrier_t barreira;

//Função Maior
double maior(double x, double y){
    if(x>y)
        return x;
    else
        return y;
}

//Estrutura
typedef struct{
    int num;
    int var[500];
}inf;


void *calcula(void *numero){
    inf *estrutura = (inf *)calcula;
    for (int i = 0; i < I; ++i){
        for (int j = 0; j < estrutura->num; ++j){
            int temp = estrutura->var[j];
            double soma = 0;
            
            for (int k = 0; k < num; ++k){
                if(k != temp)
                    soma = soma + matriz_1[temp][k]*matriz_result[k];
            }
                
            soma = (matriz_2[temp] - soma) / matriz_1[temp][temp];
            matriz_temp[temp] = soma;
        }
        
        pthread_barrier_wait(&barreira);

        for (int j = 0; j < num; ++j){
            matriz_result[j] = matriz_temp[j];
        }
    }

    pthread_exit(NULL);
}


int main(){
    printf("Digite o tamanho da matriz NxN: \n");
    scanf("%d", &n);
    printf("Digite a matriz\n");
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n; ++j){
            scanf("%d" ,&a[i][j]);
        }
        
        scanf("%d" ,&matriz_2[i]);    
        matriz_result[i] = 1;
    }
    
    int maior = 0;
    for(int i = 0; i < n; ++i){
        int teste = 0;
        if(matriz_1[i][i] == 0){
            printf("ERRO, Não eh possivel concluir a operação");
            pthread_exit(NULL);
        }
        for(int j = 0; j < n; j++){
            if(i != j)
                teste = teste + fabs(matriz_1[i][j])/fabs(matriz_1[i][i]);
        }
        
        maior = maior(maior, teste);
    }
    
    if(maior >= 1){
        printf("ERRO, Não eh possivel concluir a operação");
        pthread_exit(NULL);
    }
    
    printf("Digite o numero de numero de threads\n");
    scanf("%d" ,&num_threads);
    
    int div = num/num_threads;
    int rem = num%num_threads;
    int cnt = 0;
    
    pthread_t id[I];
    
    pthread_barrier_init(&barreira, NULL, num_threads);
    for(int i = 0; i < num_threads; i++){
        inf *estrutura;
        estrutura = malloc(sizeof(inf));
        if(i < rem){
            estrutura->num = div+1;
        }
        else
            estrutura->num = div;
            
        for(int j = 0; j < estrutura->n; j++)
            estrutura->var[j] = cnt++;
            
        pthread_create(&id[i], NULL, solve, (void *)estrutura);
    }
    
    for(int i = 0; i < num_threads; i++){
        pthread_join(id[i], NULL);
    }
    
    for(int i = 0; i < n; i++){
        printf("%d \n", matriz_result[i]);
    }
    pthread_exit(NULL);
}
