#include "nodo.h"
#include "resorte.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
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
	assert(nodo_obtener_resortes(nodo1)[0] == resorte);
	assert(nodo_obtener_resortes(nodo2) != NULL);
	assert(nodo_obtener_resortes(nodo2)[0] == resorte);

	float pos3[] = {2.5,4.6};
	float l = resorte_obtener_longitud(resorte);
	printf("%f\n",l);
	nodo_actualizar_posicion(nodo1, pos3);
	resorte_actualizar(resorte);
	assert(l != resorte_obtener_longitud(resorte));

	assert(nodo_obtener_cantidad_de_resortes(nodo1) == 1);
	assert(nodo_obtener_cantidad_de_resortes(nodo2) == 1);

	assert(!nodo_eliminar_resorte(NULL, nodo1, resorte_comparar));
	assert(nodo_eliminar_resorte(resorte, nodo1, resorte_comparar));

	assert(nodo_obtener_cantidad_de_resortes(nodo1) == 0);

	assert(nodo_obtener_resortes(nodo1)[0] == NULL);

	nodo_destruir(nodo1);
	nodo_destruir(nodo2);
	resorte_destruir(resorte);
	return 0;
}
