#ifndef MALLA_H
#define MALLA_H

#include "nodo.h"
#include "resorte.h"
#include <stddef.h>

typedef struct malla malla_t;

typedef enum tipo {NODO,RESORTE} tipo_t;

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
//Pre: hay un nodo en posi[], se llamó a que_hay_cerca con posi[] y devolvió NODO 
//la malla está creada y no es nula
//Post: el resorte forma parte de la malla
bool agregar_resorte_a_malla(malla_t *malla, const float posi[2], const float posf[2]);

//VALEN
//Indica que hay en la cercania de un radio R_CERCANIA
//Pre: La malla fue creada y no hay dos nodos cuya distancia entre sí sea menor a R_CERCANIA
//Post: Devuelve una etiqueta del tipo que se encontró mas cerca, en el caso de resorte, puede haber mas de un elemento cerca, devuelve 0 si no se encontró nada
tipo_t que_hay_cerca(malla_t *malla, const float pos[2]);

//Elimina un nodo de la lista de nodos de la malla pero no se ocupa de destruir el nodo
//Pre: la posicion se encuentra a menos de R_CERCANIA de distancia, antes de llamar a esta función se llamó a que_hay_cerca.
//Post: el nodo ya no forma parte de la malla
bool eliminar_nodo_de_malla(malla_t *malla, const float pos[2]);

//Elimina un resorte de la lista de resortes de la malla pero no se ocupa de destruir el resorte
//Pre: la posicion se encuentra a menos de R_CERCANIA de distancia, antes de llamar a esta función se llamó a que_hay_cerca.
//Post: el resorte ya no forma parte de la malla
bool eliminar_resorte_de_malla(malla_t *malla, const float pos[2]);
//-----------------------------------------------------

//Mueve un nodo de su posicion actual a pos[]
//Pre: Se llamó a que_hay_cerca antes, devolvió NODO y la malla no es nula. Si se ejecuta después de agregar_resorte, se moverá al nodo final de el resorte. Se puede llamar sucesivas veces para mover al mismo nodo sin llamar a que_hay_cerca cada vez. 
//Post: Se movió el nodo a pos[], o a el punto mas cerca a pos[] en el caso de que las longitudes de los resortes no lo permitan
bool mover_nodo(malla_t *malla, const float pos[2]);



#endif

