#include "resorte.h"
#include "vector.h"
#include <math.h>
#include <stdlib.h>



struct resorte{

	float longitud;//depende de la posicion de los nodos, se deberá actualizar cuando se modifique la posicion de los nodos
	float constante;//depende de la posicion, se debera actualizar cuando se actualice esta.
	nodo_t *nodos[2];//PUEDEN SER MODIFICADOS POR FUERA DE LAS FUNCIONES DE RESORTE.H cada vez que se modifiquen se deberá llamar a la función para actualizar

};

resorte_t *resorte_crear(nodo_t *nodo1, nodo_t *nodo2){
	resorte_t *r = malloc(sizeof(resorte_t));
	if (r == NULL)
		return NULL;
	float xn1[2];
	float xn2[2];
	float aux[2];
	nodo_obtener_posicion(nodo1,xn1);
	nodo_obtener_posicion(nodo2,xn2);
	vector_resta(2,xn1,xn2,aux);	
	r->longitud = vector_norma(2, aux);
	r->constante = K_BASE/powf(r->longitud, POTENCIA_K);
	r->nodos[0] = nodo1;
	r->nodos[1] = nodo2;
	return r;
}

void resorte_destruir(resorte_t *resorte){
	free(resorte);
}


float resorte_obtener_constante(resorte_t *resorte){
	return resorte->constante;
}

float resorte_obtener_longitud(resorte_t *resorte){
	return resorte->longitud;
}

nodo_t **resorte_obtener_nodos(resorte_t *resorte){
	return resorte->nodos;
}

bool resorte_comparar(resorte_t *resorte1, resorte_t *resorte2){
	return (resorte1 == resorte2);
}

bool resorte_actualizar(resorte_t *resorte){
	float xn1[2];
	float xn2[2];
	float aux[2];
	nodo_obtener_posicion(resorte->nodos[0],xn1);
	nodo_obtener_posicion(resorte->nodos[1],xn2);
	vector_resta(2,xn1,xn2,aux);	
	resorte->longitud = vector_norma(2, aux);
	resorte->constante = K_BASE/powf(resorte->longitud, POTENCIA_K);
	return true;
}

bool resorte_es_ganador(resorte_t *resorte){
	float pos0[2];
	nodo_obtener_posicion(resorte->nodos[0],pos0);
	float pos1[2];
	nodo_obtener_posicion(resorte->nodos[1],pos1);
	float longitud_actual = distancia_a_punto(pos0, pos1);
	return ((longitud_actual/resorte->longitud - 1.0) < MAXIMO_ESTIRAMIENTO);
}

