#include "nodo.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


struct nodo{
	resorte_t **resortes;//está vacio si nres = 0.
	size_t resortes_memb;//cantidad de memoria almacenada para la lista de resortes
	size_t nres;//cantidad de resortes
	bool es_fijo;
	float posicion[2];//primer valor corresponde a la coordenada x & el segundo valor corresponde a la cordenada y
};


nodo_t *nodo_crear(const float posicion[2], bool es_fijo){
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (nodo == NULL)
		return NULL;
	nodo->resortes = NULL;
	nodo->resortes_memb = 0;
	nodo->nres = 0;	
	nodo->es_fijo = es_fijo;
	memcpy(nodo->posicion, posicion, 2 * sizeof(float));
	return nodo;
}

void nodo_destruir(nodo_t *nodo){
	free(nodo->resortes);
	free(nodo);
}

bool nodo_agregar_resorte(resorte_t *resorte, nodo_t *nodo){
	if (nodo->resortes_memb == 0){
		nodo->resortes = malloc(10 * sizeof(resorte_t*));
		if (nodo->resortes == NULL)
			return false;
		nodo->resortes_memb = 10;
	}
	if (nodo->nres == nodo->resortes_memb){
		resorte_t **aux = realloc(nodo->resortes,((nodo->resortes_memb * 1.5) * sizeof(resorte_t*)));
		if (aux == NULL)
			return false;
		nodo->resortes = aux;
		nodo->resortes_memb *= 1.5;
	}
	nodo->resortes[nodo->nres++] = resorte;
	return true;
}

bool nodo_eliminar_resorte(resorte_t *resorte, nodo_t *nodo, bool (*comparador)(resorte_t*, resorte_t*)){ 
	size_t i = 0;	
	for (;i < nodo->nres && !(comparador(resorte, nodo->resortes[i])); i++);
	if (i == nodo->nres)
		return false;
	nodo->resortes[i] = NULL;
	for (;i<nodo->nres;i++){
		memmove(nodo->resortes[i],nodo->resortes[i+1], nodo->nres-(i+1));
	}
	nodo->nres--;
	return true;

}

resorte_t **nodo_obtener_resortes(const nodo_t *nodo){
	return nodo->resortes;
}

size_t nodo_obtener_cantidad_de_resortes(const nodo_t *nodo){
	return nodo->nres;
}

void nodo_obtener_posicion(const nodo_t *nodo, float posicion[2]){
	//memcpy(posicion, nodo->posicion, 2 * sizeof(float));
	posicion[0] = nodo->posicion[0];
	posicion[1] = nodo->posicion[1];
}

void nodo_actualizar_posicion(nodo_t *nodo,const float posicion[2]){
	//memcpy(nodo->posicion, posicion, 2 * sizeof(float));
	nodo->posicion[0] = posicion[0];
	nodo->posicion[1] = posicion[1];
}


bool nodo_comparar(nodo_t *nodo1, nodo_t *nodo2){
	//return (nodo1->posicion[0] == nodo2->posicion[0]) && (nodo1->posicion[1] == nodo2->posicion[1]);
	return nodo1 == nodo2;
}

bool nodo_es_fijo(const nodo_t *nodo){
	return nodo->es_fijo;
}
