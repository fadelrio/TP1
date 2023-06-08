#include "nodo.h"
#include "resorte.h"
#include <stdlib.h>
#include <string.h>


typedef struct nodo{
	//float masa; depende de la respuesta a la pregunta del header
	resorte_t **resortes;//es NULL si nres es 0
	size_t nres;//cantidad de resortes
	bool es_fijo;
	float posicion[2];//primer valor corresponde a la coordenada x & el segundo valor corresponde a la cordenada y
} nodo_t;


nodo_t *nodo_crear(float posicion[2], bool es_fijo){
	nodo_t *nodo = malloc(sizeof(nodo_t));
	nodo->resortes = NULL;
	nodo->nres = 0;	
	nodo->es_fijo = es_fijo;
	memcpy(nodo->posicion, posicion, 2 * sizeof(float));
	return nodo;
}

void nodo_destruir(nodo_t *nodo){
	free(nodo);
}

bool nodo_agregar_resorte(resorte_t *resorte, nodo_t *nodo){
	if (nodo->nres == 0){
		nodo->resortes = malloc(RESORTES_MAXIMOS * sizeof(resorte_t*));
		if (nodo->resortes == NULL)
			return false;
	}
	if (nodo->nres == RESORTES_MAXIMOS)
		return false;
	nodo->resortes[nodo->nres++];
	return true;
}

bool nodo_eliminar_resorte(resorte_t *resorte, nodo_t *nodo){
	size_t i = 0;	
	for (;resorte_comparar(resorte, nodo->resortes[i]) && i < nodo->nres ; i++);
	if (i == nodo->nres)
		return false;
	for (;i<nodo->nres;i++){
		nodo->resortes[i] = nodo->resortes[i+1];
	}
	nodo->nres--;
	return true;
}

resorte_t **nodo_obtener_resortes(const nodo_t *nodo){
//depende de la pregunta del header
}

size_t nodo_obtener_cantidad_de_resortes(const nodo_t *nodo){
	return nodo->nres;
}

void nodo_obtener_posicion(const nodo_t *nodo, float posicion[2]){
	memcpy(posicion, nodo->posicion, 2 * sizeof(float));
}

bool nodo_es_fijo(const nodo_t *nodo){
	return nodo->es_fijo;
}
