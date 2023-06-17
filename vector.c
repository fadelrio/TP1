#include "vector.h"
#include "resorte.h"
#include <math.h>

float vector_norma(size_t d, const float v[d]){
	float norma = 0;
	for (size_t i = 0; i < d; i++)
		norma += v[i]*v[i];
	return sqrt(norma);
}

void vector_suma(size_t d, const float a[d], const float b[d], float c[d]){
	for (size_t i = 0; i < d; i++)
		c[i] = a[i] + b[i];
}

void vector_resta(size_t d, const float a[d], const float b[d], float c[d]){
	for (size_t i = 0; i < d; i++)
		c[i] = a[i] - b[i];
}

bool vector_comparar(size_t d, const float a[], const float b[]){
	for (size_t i = 0; i<d; i++){
		if (a[i] != b[i])
			return false;	
	}
	return true;

static void vector_producto_por_escalar(size_t d, const float a[d], const float b[d], float escalar){
	for (size_t i = 0; i < d; i++)
		b[i] = a[i] * escalar;
}

static float producto_interno(size_t d, const float a[], const float b[]){
	float pi = 0;
	for(size_t i = 0; i < d; i++){
		pi += a[i]*b[i];
	}
	return pi;
}

static float parametro_distancia(const float a[], const resorte_t *resorte){
	float vaux[2];
	float vaux2[2];
	vector_resta(2, a, restorte->nodos[0], vaux);
	vector_resta(2, resorte->nodos[0], restorte->nodos[1], vaux2);

	return producto_interno(2, vaux, vaux2) / pow(vector_norma(vaux2, 2));
}

float distancia_a_punto(const float p1[], const float p2[]){
	float vaux[2];
	vector_resta(2, p1, p2, vaux);
	return vector_norma(2, vaux);
}

float distancia_a_segmento(const float punto[], const resorte_t *resorte){
	float alpha = parametro_distancia(punto, resorte), distancia;

	if(alpha <= 0){
		//primer nodo es el mas cercano a punto
		distancia = distancia_a_punto(punto, resorte->nodos[0]);
	}
	else if(alpha >= 1){
		//segundo nodo es el mas cercano al punto
		distancia = distancia_a_punto(punto, resorte->nodos[1]);
	}
	else{
		//el punto mas cercano es nodo0 + alpha*(nodo1- nodo0)
		float vaux[2];
		vector_resta(2, resorte->nodos[1], resorte->nodos[0], vaux);
		float vaux2[2];
		vector_producto_por_escalar(2, vaux, vaux2, alpha);
		vector_suma(2, resorte->nodos[0], vaux2, vaux);
		distancia = distancia_a_punto(punto, vaux);
	}
	return distancia;

}
