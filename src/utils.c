#include <stdio.h>
#include <math.h>

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
	float quickX[4];
	float quickY[4];
	for(int i = 0; i < K; i++) {
		quickX[i] = R1[i];
		quickY[i] = R2[i];
	}
	for(int i = 0; i < N; i++) {
		int mem = C[i];
		float mem2 = A[i];
		float mem3 = B[i];
		float maxD=10;
		for(int j = 0; j < K; j++) {
			float D = pow(mem2-quickX[j],2)+pow(mem3-quickY[j],2);

			if(maxD > D) {
				C[i] = j;
				maxD = D;
			}
		}
		if(C[i]!=mem)ret++;
	}
	return ret;
}
