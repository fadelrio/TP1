#ifndef MALLA_H
#define MALLA_H

#include "nodo.h"
#include "resorte.h"
#include <stddef.h>

typedef struct malla malla_t;

/*crea y devuelve por nombre una malla con sus miembros inicializados
segun el invariante de representacion de listas enlazadas*/
malla_t *malla_crear();

//destruye la malla y todos sus miembros
void malla_destruir(malla_t *malla);

//pregunta: que otra operacion mas se puede hacer con malla?
//porque agregar nodos o sacar nodos, o resortes, para eso
//estan las operaciones de lista enlazada



#endif

