#include "nodo.h"
#include "resorte.h"
#include "lista.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct nodo_simulado{
	nodo_t *nodo;
	size_t sim; //indica en que iteracion del simulador se actualizaron los terminos sin resorte
	float pos_ant[2];
	float pos_antant[2];
}nodo_simulado_t;

typedef struct resorte_simulado{
	resorte_t *resorte;
	float long_inicial;
	float long_ant;
	nodo_simulado_t nodos_simulados[2];
}resorte_simulado_t;

struct simulador {
	size_t sim;
	size_t n_nodos;
	nodo_simulado_t **nodos_sin_resortes_simulados;
	size_t n_res;
	resorte_simulado_t **resortes_simulados;
	float masa;
};

static bool _seleccionar_nodos(void *n, void *sim);
static bool _convertir_resortes(void *r, void *sim);
static nodo_simulado_t *_convertir_nodo(nodo_t *nodo);

simulador_t *simulador_crear(lista_t *lista_nodos, lista_t *lista_resortes){
	simulador_t *simulador = malloc(sizeof(simulador));
	if (simulador == NULL)
		return NULL;
	simulador->nodos_sin_resortes_simulados = malloc(lista_largo(lista_nodos)*sizeof(nodo_simulado_t*));//almacena memoria de sobra, pero es mas rapido
	if (simulador->nodos_sin_resortes_simulados == NULL)
		return NULL;
	simulador->resortes_simulados = malloc(lista_largo(lista_resortes)*sizeof(resorte_simulado_t*));
	if (simulador->resortes_simulados == NULL){
		free(simulador->nodos_sin_resortes_simulados);
		return NULL;
	}
	simulador->sim = 0;
	simulado->masa = MASA_TOTAL/lista_largo(lista_nodos);
	//hacer funciones para usar con lista_recorrer que añadan los nodos sin resortes y los resortes a sus respectivas listas.
	lista_recorrer(lista_nodos, _seleccionar_nodos, simulador);
	lista_recorrer(lista_resortes, _convertir_resortes, simulador);
	return simulador;
}

void simulador_destruir(simulador_t *simulador){
	for (size_t i = 0; i<simulador->n_nodos; i++)
		free(simulador->nodos_sin_resortes_simulados[i]);
	for (size_t i = 0; i<simulador->n_res; i++)
		free(simulador->resortes_simulados[i]);
	free(simulador->resortes_simulados);
	free(simulador->nodos_sin_resortes_simulados);
	free(simulador);
}
















static bool _seleccionar_nodos(void *n, void *sim){
	nodo_t *nodo = n;
	simulador_t *simulador = sim;
	if (nodo_obtener_cantidad_de_resortes(nodo) == 0){
		nodo_simulado_t *nodo_simulado = _convertir_nodo(nodo);
		if(nodo_simulado == NULL)
			return true; 
		simulador->nodos_sin_resortes_simulados[simulador->n_nodos++] = nodo_simulado;
	}
	return true;
}

static bool _convertir_resortes(void *r, void *sim){
	resorte_t resorte = r;
	simulador_t simulador = sim;
	resorte_simulado_t *resorte_simulado = malloc(sizeof(resorte_simulado_t));
	if (resorte_simulado == NULL)
		return true;
	resorte_simulado->resorte = resorte;
	resorte_simulado->long_inicial = resorte_obtener_longitud(resorte);
	resorte_simulado->long_ant = resorte_obtener_longitud(resorte);
	resorte_simulado->nodos_simulados[0] = _convertir_nodo(resorte_obtener_nodos(resorte)[0]);
	resorte_simulado->nodos_simulados[1] = _convertir_nodo(resorte_obtener_nodos(resorte)[1]);
	simulador->resortes_simulados[simulador->nres++] = resorte_simulado;
	
}

static nodo_simulado_t *_convertir_nodo(nodo_t *nodo){
		nodo_simulado_t *nodo_simulado= malloc(sizeof(nodo_simulado_t));
		if (nodo_simulado == NULL)
			return NULL;
		nodo_simulado->nodo = nodo;
		nodo_simulado->sim = 0;
		float pos[] = nodo_obtener_posicion(nodo);
		nodo_simulado->pos_ant[0] = pos[0];
		nodo_simulado->pos_ant[1] = pos[1];
		nodo_simulado->pos_antant[0] = pos[0];
		nodo_simulado->pos_antant[1] = pos[1];
}








