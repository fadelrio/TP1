#include "nodo.h"
#include "resorte.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
	float pos1[] = {1.5, 4.3};
	nodo_t *nodo1 = nodo_crear(pos1, false);
	assert(nodo1 != NULL);
	float pos2[] = {0.5, 2.4};
	nodo_t *nodo2 = nodo_crear(pos2, false);
	assert(nodo2 != NULL);
	resorte_t *resorte = resorte_crear(nodo1, nodo2);
	assert(resorte != NULL);
	nodo_agregar_resorte(resorte, nodo1);	
	nodo_agregar_resorte(resorte, nodo2);
	assert(nodo_obtener_resortes(nodo1) != NULL);
	assert(nodo_obtener_resortes(nodo2) != NULL);
	
	
}
