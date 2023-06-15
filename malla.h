#ifndef MALLA_H
#define MALLA_H

#include "nodo.h"
#include "resorte.h"
#include <stddef.h>

typedef struct malla malla_t;

//Crea y devuelve por nombre una malla con sus miembros inicializados
//segun el invariante de representacion de listas enlazadas
//Pre: No hay otra malla, es única
//Post: Se crea la malla sobre la que se estará trabajando a lo largo del ejercicio
malla_t *malla_crear();

//Destruye la malla y todos sus miembros
//Pre: había una malla creada
//Post: al destruirse la malla se reinicia el juego
void malla_destruir(malla_t *malla);

//Agrega un nodo a la lista de nodos de la malla
//Pre: La lista de nodos tanto como la malla están creadas
//Post: Agrega en primer lugar de la lista al nodo de la posición y fijación indicados
bool agregar_nodo_a_malla(malla_t *malla, const float pos[2], bool es_fijo);

//Agrega un resorte a la lista de resortes de la malla|     
//Pre: el resorte no supera la longitud máxima y tanto 
//la malla como nodo1 y nodo2 están creados y no son nulos
//Post: agrega un resorte en primer lugar de la lista enlazada y además los linkea a nodo1 y nodo2
bool agregar_resorte_a_malla(malla_t *malla, nodo_t *nodo1, nodo_t *nodo2);

//Indica que hay en la cercania de un radio R_CERCANIA
//Pre: La malla fue creada y no hay dos nodos cuya distancia entre sí sea menor a R_CERCANIA, con los resortes que onda?
//Post: Devuelve NULL si no hay nada cerca, o un puntero al resorte o nodo que se tenga más cerca
void *que_hay_cerca(malla_t *malla, const float pos[2]);

//Elimina un nodo de la lista de nodos de la malla pero no se ocupa de destruir el nodo
//Pre: El nodo al que se pasa como argumento pertenece a la lista de nodos de la malla
//Post: Se devuelve un puntero al mismo nodo que se eliminó de la lista para poder destruirlo
void *eliminar_nodo_de_malla(malla_t *malla, nodo_t *nodo);

//Elimina un resorte de la lista de resortes de la malla pero no se ocupa de destruir el resorte
//Pre: El resorte al que se pasa como argumento pertenece a la lista de resortes de la malla
//Post: Se devuelve un puntero al mismo resorte que se eliminó de la lista para poder destruirlo
void *eliminar_resorte_de_malla(malla_t *malla, resorte_t *res);


#endif

