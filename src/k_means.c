#include "../include/utils.h"

#include<stdio.h>
#include<stdlib.h>

#define K 4
#define N 10000000

#ifndef size
#define size 512
#endif

float *X_Coords, *Y_Coords;
float *Xn,*Yn;
int *Nucleos;

void alloc() {
	X_Coords = malloc(N*sizeof(float));
	Y_Coords = malloc(N*sizeof(float));
	Nucleos = malloc(N*sizeof(int));
	Xn = malloc(K*sizeof(float));
	Yn = malloc(K*sizeof(float));
}

void init() {
    	srand(10);
	for(int i=0; i<N;i++) {
		X_Coords[i] = (float) rand() / RAND_MAX; 
		Y_Coords[i] = (float) rand() / RAND_MAX;
		Nucleos[i] = 0;
    	}
	for(int i=0; i<K;i++) {
		Xn[i] = X_Coords[i];
		Yn[i] = Y_Coords[i];
	}
}
/*
void mmult() {
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++) {
            C[i*size+j] = 0;
            for(int k=0; k<size; k++) {
                C[i*size+j] += A[i*size+k] * B[k*size+j];
            }
        }
    }
}
*/
int main() {
   alloc();
   init();
   int j=0;
   while (normalize(X_Coords,Y_Coords,Nucleos,K,N,Xn,Yn)){ 
    centroid(X_Coords,Y_Coords,Nucleos,K,N,Xn,Yn);
    j++;
   }
   int num[K];
   for(int i=0;i<K;i++) num[i] = 0;
   for(int i= 0;i<N;i++){
 	num[Nucleos[i]]+=1;
   } 
   for(int i=0;i<K;i++){
	   printf("Center: (%.3f,%.3f) : Size : %d\n",Xn[i],Yn[i],num[i]);
   }
   printf("%d iterações!\n", j);
}
