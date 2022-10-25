#include <stdio.h>
#include <math.h>
#include "../include/utils.h"

void centroid(Ponto *pontos, Nucleo *nucleos, int K, int N){

	for(int i = 0; i < K; i++) {
		Nucleo *nucleo = &nucleos[i];
		nucleo->x = 0;
		nucleo->y = 0;	
		nucleo->agregados = 0;
	}
	for(int i = 0,j=0;i<N;i+=2) {
		Ponto ponto_local1 = pontos[i];
		Ponto ponto_local2 = pontos[i+1];
		Nucleo *nucleo1 = &nucleos[ponto_local1.grupo];
		Nucleo *nucleo2 = &nucleos[ponto_local2.grupo];
		nucleo1->agregados++;
		nucleo2->agregados++;
		nucleo1->x += ponto_local1.x;
		nucleo2->x += ponto_local2.x;
		nucleo1->y += ponto_local1.y;
		nucleo2->y += ponto_local2.y;
	}
	for(int i =0; i<K; i++) {
		Nucleo *nucleo = &nucleos[i];
		nucleo->x /= nucleo->agregados;
		nucleo->y /= nucleo->agregados;	
	}
	
}

int minima_dist(Ponto *ponto, float *distancias, int K) {
	int nucleo = 0;
	float dist_comp = distancias[0];
	for (int i = 1; i < K; i++) {
		if (dist_comp > distancias[i]) {
			nucleo = i;
			dist_comp = distancias[i];
		}
	}
	if (nucleo != ponto->grupo) {
		ponto->grupo = nucleo;
		return 1;
	}
	return 0;
}

int normalize(Ponto *pontos, Nucleo *nucleos, int K, int N){
	int retorno = 0;	
	Nucleo nucleos_locais[K];

	float distancias1[K];
	float distancias2[K];

	for(int i = 0; i < K; i+=2) {
		nucleos_locais[i] = nucleos[i];
		nucleos_locais[i+1] = nucleos[i+1];
	}

	for(int i = 0; i < N && !retorno; i+=2) {
		Ponto ponto_local1 = pontos[i];
		Ponto ponto_local2 = pontos[i+1];
		
		for (int j = 0; j < K; j+=2) {
			distancias1[j] = pow(ponto_local1.x - nucleos_locais[j].x,2) + pow(ponto_local1.y - nucleos_locais[j].y,2);
			distancias1[j+1] = pow(ponto_local1.x - nucleos_locais[j+1].x,2) + pow(ponto_local1.y - nucleos_locais[j+1].y,2);
			
			distancias2[j] = pow(ponto_local2.x - nucleos_locais[j].x,2) + pow(ponto_local2.y - nucleos_locais[j].y,2);
			distancias2[j+1] = pow(ponto_local2.x - nucleos_locais[j+1].x,2) + pow(ponto_local2.y - nucleos_locais[j+1].y,2);
		}

		retorno += minima_dist(&pontos[i], distancias1, K) + minima_dist(&pontos[i+1], distancias2, K);
	}
	
	return retorno;
}
