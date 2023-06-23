#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "lista.h"

typedef struct simulador simulador_t;

//recibe una lista de nodos y una lista de resortes y devuelve un puntero a una estructura simulador_t
simulador_t *simulador_crear(lista_t *lista_nodos, lista_t *lista_resortes);

//libera la memoria asociada a la estrctura simulador, no la asociada a los nodos y los resortes
void simulador_destruir(simulador_t *simulador);

//simula un instante dt en la malla de nodos y resortes
void simulador_simular(simulador_t *simulador, float dt);

#endif
