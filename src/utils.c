#include <stdio.h>
#include <math.h>

void hello_cp(){
    printf("Hello Computacao Paralela!!!\n");
}

void centroid(float *A,float *B,int *C,int K,int N,float *R1,float *R2){
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

int normalize(float *A,float *B,int *C,int K,int N,float *R1,float *R2){
	int ret = 0;	
	for(int i = 0; i < N; i++) {
		float maxD=1000;

		int mem = C[i];
		float mem2 = A[i];
		float mem3 = B[i];
		for(int j = 0; j < K; j++) {
			float D = pow(mem2-R1[j],2)+pow(mem3-R2[j],2);

			if(maxD > D) {
				C[i] = j;
				maxD = D;
			}
		}
		if(mem != C[i]) ret ++;
	}
	return ret;
}
