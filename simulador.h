#ifndef SIMULADOR_H
#define SIMULADOR_H

#include "lista.h"

typedef struct simulador simulador_t;

//Recibe una lista de nodos y una lista de resortes y devuelve un puntero a una estructura simulador_t
//Pre: No hay otro simulador creado, es único
//Post: Se creó un simulador sin alterar las listas obtenidas
simulador_t *simulador_crear(lista_t *lista_nodos, lista_t *lista_resortes);

//libera la memoria asociada a la estrctura simulador, no la asociada a los nodos y los resortes
//Pre: simulador no es nulo
//Post: Se liberó la memoria asociada a la simulacion
void simulador_destruir(simulador_t *simulador);

//simula un instante dt en la malla de nodos y resortes
//Pre: simulador no es nulo, dt < 0
//Post: Se simuló un dt, y se actualizaron las posiciones de los nodos obtenidos en la creación del simulador
void simulador_simular(simulador_t *simulador, float dt);

#endif
