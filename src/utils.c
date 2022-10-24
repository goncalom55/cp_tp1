#include <stdio.h>
#include <math.h>

void centroid(float *AB,int *C,int K,int N,float *R1,float *R2){
	int kn[K];



	for(int i = 0; i < K; i++) {
		kn[i] = 0;
		R1[i] = 0;
		R2[i] = 0;	
	}
	for(int i = 0,j=0;j<N,j++) {
		kn[C[j]]++;
		
		R1[C[j]]+=AB[i++];
		
		R2[C[j]]+=AB[i++];
		
	}
	for(int i =0; i<K; i++) {
		R1[i] /= kn[i];
		R2[i] /= kn[i];
	}
	
}

int normalize(float *AB,int *C,int K,int N,float *R1,float *R2){
	int ret = 0;	
	float quickX[K];
	float quickY[K];
	for(int i = 0; i < K; i++) {
		quickX[i] = R1[i];
		quickY[i] = R2[i];
	}
	for(int i = 0,t=0; i < N; i++) {
		int c = 0;
		int mem = C[i];
		float mem2 = AB[t++];
		float mem3 = AB[t++];
		float r = pow(mem2-quickX[0],2)+pow(mem3-quickY[0],2);

		for (int j = 1; j < K; j++) {
			float comp = pow(mem2-quickX[j],2)+pow(mem3-quickY[j],2);	
			if(r > comp) {
				c = j;
				r = comp;
			}
		}

		if(c!=mem){
			C[i] = c;
			ret = 1;
		}
	}
	return ret;
}
