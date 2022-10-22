#include <stdio.h>
#include <math.h>

void hello_cp(){
    printf("Hello Computacao Paralela!!!\n");
}

void centroid(double *A,double *B,int *C,int K,int N,double *R1,double *R2){
	int kn[K];
	for(int i = 0; i < K; i++) {
		kn[i] = 0;
		R1[i] = 0;
		R2[i] = 0;	
	}
	for(int i = 0; i<N; i++) {
		kn[C[i]]++;
		R1[C[i]]+=A[i];
		R2[C[i]]+=B[i];
	}
	for(int i =0; i<K; i++) {
		R1[i] /= kn[i];
		R2[i] /= kn[i];
	}
	
}

int normalize(double *A,double *B,int *C,int K,int N,double *R1,double *R2){
	int ret = 0;	
	for(int i = 0; i < N; i++) {
		float maxD=10;
		int mem = C[i];	
		for(int j = 0; j < K; j++) {
			float D = sqrt(pow(A[i]-R1[j],2)+pow(B[i]-R2[j],2));

			if(maxD > D) {
				C[i] = j;
				maxD = D;
			}
		}
		if(mem != C[i]) ret ++;
	}
	return ret;
}
