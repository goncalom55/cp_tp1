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

int min(float *R1, float *R2, int K, float X, float Y) {
		
       	float r = pow(X-R1[0],2)+pow(Y-R2[0],2);
	int c = 0;

	for (int i = 1; i < K; i++) {
		float comp = pow(X-R1[i],2)+pow(Y-R2[i],2);	
		if(r > comp) {
			c = i;
			r = comp;
		}
	}
	return c;
}

int normalize(float *A,float *B,int *C,int K,int N,float *R1,float *R2){
	int ret = 0;	
	float quickX[K];
	float quickY[K];
	for(int i = 0; i < K; i++) {
		quickX[i] = R1[i];
		quickY[i] = R2[i];
	}
	for(int i = 0; i < N; i++) {
		int mem = C[i];
		float mem2 = A[i];
		float mem3 = B[i];
		C[i] = min(quickX,quickY,K,mem2,mem3);
		if(C[i]!=mem)ret++;
	}
	return ret;
}
