#include "nodo.h"
#include "resorte.h"

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
	nodo_simulado_t **nodos_simulados_sin_resortes;
	size_t n_res;
	resorte_simulado_t **resortes_simulados;
	float masa;
};

simulador_t *simulador_crear(lista_t *lista_nodos, lista_t *lista_resortes){
	simulador_t *simulador = malloc(sizeof(simulador));
	simulador->nodos_simulados_sin_resortes = malloc(lista_largo(lista_nodos)*sizeof(nodo_simulado_t*));//almacena memoria de sobra, pero es mas rapido
	simulador->resortes_simulados = malloc(lista_largo(lista_resortes)*sizeof(resorte_simulado_t*));
	simulador->sim = 0;
	simulado->masa = MASA_TOTAL/lista_largo(lista_nodos);
	//hacer funciones para usar con lista_recorrer que añadan los nodos sin resortes y los resortes a sus respectivas listas.
	
}

static void 
