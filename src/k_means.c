#include "../include/utils.h"

#include<stdio.h>
#include<stdlib.h>

#define K 4
#define N 10000000

#ifndef size
#define size 512
#endif

float *XY;
float *Xn,*Yn;
int *Nucleos;

void alloc() {
	XY = malloc(2*N*sizeof(float));
	Nucleos = malloc(N*sizeof(int));
	Xn = malloc(K*sizeof(float));
	Yn = malloc(K*sizeof(float));
}

void init() {
    	srand(10);
	for(int i=0,j=0; j<N;i++,j++) {
		XY[i] = (float) rand() / RAND_MAX; 
		XY[++i] = (float) rand() / RAND_MAX;
		Nucleos[j] = 0;
    	}
	for(int i=0,j =0; j<K;i++) {
		Xn[j] = XY[i];
		Yn[j++] = XY[++i];
	}
}

int main() {
   alloc();
   init();
   int j=0;
   while (normalize(XY,Nucleos,K,N,Xn,Yn)){
    centroid(XY,Nucleos,K,N,Xn,Yn);
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
