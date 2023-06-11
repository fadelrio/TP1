#include "resorte.h"
#include "nodo.h"
#include "vector.h"
#include "math.h"


typedef struct resorte{
	float longitud;
	float constante;
	nodo_t *nodos[2];
} resorte_t;

resorte_t *resorte_crear(nodo_t *nodo1, nodo_t *nodo2){
	resorte_t *r = malloc(sizeof(resorte_t));
	float xn1[2];
	float xn2[2];
	float aux[2];
	nodo_obtener_posicion(nodo1,xn1);
	nodo_obtener_posicion(nodo2,xn2);
	vector_sumar(2,xn1,xn2,aux);	
	r->longitud = vector_norma(2, aux);
	r->constante = K_BASE/pow(r->longitud, POTENCIA_K);
	r->nodos[0] = nodo1;
	r->nodos[1] = nodo2;
	return r;
}
