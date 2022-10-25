#include "../include/utils.h"

#include<stdio.h>
#include<stdlib.h>

#define K 4
#define N 10000000

#ifndef size
#define size 512
#endif

Ponto *pontos;
Nucleo *nucleos;

void alloc() {
	pontos = malloc(N*sizeof(Ponto));
	nucleos = malloc(K*sizeof(Nucleo));
}

void init() {
    	srand(10);
	for(int i=0,j=0; j<N;i++,j++) {
		pontos[i].x = (float) rand() / RAND_MAX; 
		pontos[i].y = (float) rand() / RAND_MAX;
		pontos[i].grupo = 0;
    	}
	for(int i=0 ; i < K ; i++) {
		nucleos[i].x = pontos[i].x;
		nucleos[i].y = pontos[i].y;
		nucleos[i].agregados = 0;
	}
}

int main() {
   	alloc();
   	init();
   	int j=0;
   	while (normalize(pontos, nucleos, K, N)){
    	centroid(pontos, nucleos, K, N);
    	j++;
   	}
   	for(int i=0;i<K;i++){
		printf("Center: (%.3f,%.3f) : Size : %d\n", nucleos[i].x, nucleos[i].y, nucleos[i].agregados);
   	}
   	printf("%d iterações!\n", j);
}
