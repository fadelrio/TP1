#include "nodo.h"
#include "resorte.h"

typedef struct nodo_simulado{
	nodo_t *nodo;
	float pos_ant[2];
	float pos_antant[2];
}nodo_simulado_t;

typedef struct resorte_simulado{
	resorte_t *resorte;
	float long_ant;
}resorte_simulado_t;

struct simulador {
	size_t n_nodos;
	nodo_simulado_t **nodos_simulados;
	size_t n_res;
	resorte_simulado_t **resortes_simulados;
	float masa;
};
