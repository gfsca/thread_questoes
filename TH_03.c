#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int randomize(){ // função retorna um número aleatório que vai até RAND_MAX, usar % para limitar seu range.
    srand((unsigned)time(NULL));
    return rand();
}


int main(){  


    return 0;
}