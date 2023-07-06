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

bool vector_comparar(size_t d, const float a[d], const float b[d]){
	for (size_t i = 0; i<d; i++){
		if (a[i] != b[i])
			return false;	
	}
	return true;
}

void vector_producto_por_escalar_ons(size_t d, float a[d], float escalar){
	for (size_t i = 0; i < d; i++)
		a[i] *= escalar;
}

void vector_producto_por_escalar(size_t d, const float a[d], float b[d], float escalar){
	for (size_t i = 0; i < d; i++)
		b[i] = a[i] * escalar;
}

float producto_interno(size_t d, const float a[d], const float b[d]){
	float pi = 0;
	for(size_t i = 0; i < d; i++){
		pi += a[i]*b[i];
	}
	return pi;
}


static float parametro_distancia(const float a[], const float posi[], const float posf[]){
	float vaux[2];
	float vaux2[2];
	vector_resta(2, a, posi, vaux);
	vector_resta(2, posf, posi, vaux2);

	return producto_interno(2, vaux, vaux2) / powf(vector_norma(2, vaux2), 2.0);
}

float distancia_a_punto(const float p1[], const float p2[]){
	float vaux[2];
	vector_resta(2, p1, p2, vaux);
	return vector_norma(2, vaux);
}


float distancia_a_segmento(const float punto[], const float posi[], const float posf[]){
	float alpha = parametro_distancia(punto, posi, posf), distancia;

	if(alpha <= 0){
		//primer nodo es el mas cercano a punto
		distancia = distancia_a_punto(punto, posi);
	}
	else if(alpha >= 1){
		//segundo nodo es el mas cercano al punto
		distancia = distancia_a_punto(punto, posf);
	}
	else{
		//el punto mas cercano es nodo0 + alpha*(nodo1- nodo0)
		float vaux[2];
		vector_resta(2, posf, posi, vaux);
		float vaux2[2];
		vector_producto_por_escalar(2, vaux, vaux2, alpha);
		vector_suma(2, posi, vaux2, vaux);
		distancia = distancia_a_punto(punto, vaux);
	}
	return distancia;

}
