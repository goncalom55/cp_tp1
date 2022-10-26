#include <stdio.h>
#include <stdlib.h>
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

int normalize(Ponto *pontos, Nucleo *nucleos, int K, int N){
	int retorno = 0;	
	Nucleo nucleos_locais[K];

	float distancias[K];
	float distancias2[K];

	for(int i = 0; i < K; i+=2) {
		nucleos_locais[i] = nucleos[i];
		nucleos_locais[i+1] = nucleos[i+1];
	}

	for(int i = 0; i < N; i+=2) {
		Ponto ponto_local = pontos[i];
		Ponto ponto_local2 = pontos[i+1];
		
		for (int j = 0; j < K; j+=2) {
			distancias[j] = (ponto_local.x - nucleos_locais[j].x)*(ponto_local.x - nucleos_locais[j].x)
			 +
			(ponto_local.y - nucleos_locais[j].y)*(ponto_local.y - nucleos_locais[j].y);
			
			distancias[j+1] = (ponto_local.x - nucleos_locais[j+1].x)*(ponto_local.x - nucleos_locais[j+1].x)
			 + 
			(ponto_local.y - nucleos_locais[j+1].y)*(ponto_local.y - nucleos_locais[j+1].y);

			distancias2[j] = (ponto_local2.x - nucleos_locais[j].x)*(ponto_local2.x - nucleos_locais[j].x)
			 +
			(ponto_local2.y - nucleos_locais[j].y)*(ponto_local2.y - nucleos_locais[j].y);
			
			distancias2[j+1] = (ponto_local2.x - nucleos_locais[j+1].x)*(ponto_local2.x - nucleos_locais[j+1].x)
			 + 
			(ponto_local2.y - nucleos_locais[j+1].y)*(ponto_local2.y - nucleos_locais[j+1].y);
		}

		int nuclear = 0;
		int nuclear2 = 0;
		float dist_comp = distancias[0];
		float dist2 = distancias2[0];
		for (int i = 1; i < K; i++) {
			float comp = distancias[i];
			if (dist_comp > comp) {
				nuclear = i;
				dist_comp = comp;
			}
			comp = distancias2[i];
			if (dist2 > comp) {
				nuclear2 = i;
				dist2 = comp;
			}
		}
	
		pontos[i].grupo = nuclear;
		pontos[i+1].grupo = nuclear2;
		retorno += abs(nuclear - ponto_local.grupo) + abs(nuclear2 - ponto_local2.grupo);

	}

	return retorno;
}
