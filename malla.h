#ifndef MALLA_H
#define MALLA_H

#include "nodo.h"
#include "resorte.h"
#include <stddef.h>

typedef struct malla malla_t;

typedef enum tipo {NODO,RESORTE,NADA} tipo_t;

typedef bool (*feliminar_t)(malla_t);

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
//Pre: hay nodos en las dos posiciones
//la malla está creada y no es nula
//Post: el resorte forma parte de la malla
bool agregar_resorte_a_malla(malla_t *malla, const float posi[2], const float posf[2]);

//VALEN

//Funcion interna que actualiza los valores miembros de malla nodo_cercano_actual y resorte_cercano_actual y el tipo que corresponda, segun que es lo que haya cerca
//Pre:
//Post: 
static void malla_que_hay_cerca(malla_t *malla, const float pos[2], tipo_t tipo);


//Indica de qué tipo es el elemento hay en la cercania de un radio R_CERCANIA, es un wrapper de malla_que_hay_cerca
//Pre: La malla fue creada y no hay dos nodos cuya distancia entre sí sea menor a R_CERCANIA
//Post: Devuelve una etiqueta del tipo que se encontró mas cerca, en el caso de resorte, puede haber mas de un elemento cerca, devuelve 0 si no se encontró nada
tipo_t malla_tipo_cercano(malla_t *malla, const float pos[2]);

//Elimina un nodo de la lista de nodos de la malla y se ocupa de destruir el nodo y sus resortes asociados
//Pre: la posicion se encuentra a menos de R_CERCANIA de distancia, antes de llamar a esta función se llamó a que_hay_cerca.
//Post: el nodo ya no forma parte de la malla
static bool malla_eliminar_nodo(malla_t *malla);

//Elimina un resorte de la lista de resortes de la malla y se ocupa de destruir el resorte
//Pre: la posicion se encuentra a menos de R_CERCANIA de distancia, antes de llamar a esta función se llamó a que_hay_cerca.
//Post: el resorte ya no forma parte de la malla
static bool malla_eliminar_resorte(malla_t *malla);

//Elimina de la lista de elementos correspondientes al elemento del tipo indicado
//Pre: La malla está creada, la función no se llama si el nodo es fijo, se llamó antes a la funcion 
//malla_tipo_cercano para pasar como argumento el tipo, y el mismo no podrá ser NADA
//Post: Se elimina al elemento cuyo tipo fue indicado
bool malla_eliminar_elemento(malla_t *malla, tipo_t tipo);
//-----------------------------------------------------

//Mueve un nodo de su posicion actual a pos[]
//Pre: Se llamó a que_hay_cerca antes, devolvió NODO y la malla no es nula 
//Post: Se movió el nodo a pos[], o a el punto mas cerca a pos[] en el caso de que las longitudes de los resortes no lo permitan
bool mover_nodo(malla_t *malla, const float pos[2]);



#endif

