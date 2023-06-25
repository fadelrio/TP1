#ifndef MALLA_H
#define MALLA_H

#include "lista.h"
#include "nodo.h"
#include "vector.h"
#include "resorte.h"
#include <stddef.h>
#include <SDL2/SDL.h>
#include <stdlib.h>


typedef struct malla malla_t;

typedef enum tipo {NODO,RESORTE,NADA} tipo_t;

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
bool agregar_nodo_a_malla(malla_t *malla, const float pos[], bool es_fijo);

//Agrega un resorte a la lista de resortes de la malla|     
//Pre: hay un nodo en posi[], se llamó a que_hay_cerca con posi[] y devolvió NODO 
//la malla está creada y no es nula
//Post: el resorte forma parte de la malla
bool agregar_resorte_a_malla(malla_t *malla, const float posi[], const float posf[]);

//Devuelve por nombre la cantidad de nodos almacenados en la malla
size_t malla_obtener_cant_nodos(malla_t *malla);


//Indica de qué tipo es el elemento hay en la cercania de un radio R_CERCANIA, es un wrapper de malla_que_hay_cerca
//Pre: La malla fue creada y no hay dos nodos cuya distancia entre sí sea menor a R_CERCANIA
//Post: Devuelve una etiqueta del tipo que se encontró mas cerca, en el caso de resorte, puede haber mas de un elemento cerca, devuelve 0 si no se encontró nada
tipo_t malla_tipo_cercano(malla_t *malla, const float pos[]);


//Elimina de la lista de elementos correspondientes al elemento del tipo indicado
//Pre: La malla está creada, la función no se llama si el nodo es fijo, se llamó antes a la funcion 
//malla_tipo_cercano para pasar como argumento el tipo, y el mismo no podrá ser NADA
//Post: Se elimina al elemento cuyo tipo fue indicado
void malla_eliminar_elemento(malla_t *malla, tipo_t tipo);
//-----------------------------------------------------

//Mueve un nodo de su posicion actual a pos[]
//Pre: Se llamó a que_hay_cerca antes, devolvió NODO y la malla no es nula. Si se ejecuta después de agregar_resorte, se moverá al nodo final de el resorte. Se puede llamar sucesivas veces para mover al mismo nodo sin llamar a que_hay_cerca cada vez. 
//Post: Se movió el nodo a pos[], o a el punto mas cerca a pos[] en el caso de que las longitudes de los resortes no lo permitan
bool mover_nodo(malla_t *malla, const float pos[2]);

//Se debe ejecutar despues de la ultima llamada para un nodo a mover_nodo, se ocupa de que no queden nodos superpuestos. Despues de llamarla se deberá llamar a que_hay_cerca nuevamente para mover un nodo 
//Pre: se llamó a mover_nodo al menos una vez
//Post: no quedan nodos superpuestos y no se puede volver a llamar a mover_nodo sin llamar a que_hay_cerca
void finalizar_mover_nodo(malla_t *malla);

//Devuelve si la malla ingresada es ganadora o no (las longitudes de los resortes no son mas de MAXIMO_ESTIRAMIENTO% respecto a la longitud inicial)
//Devolverá true siempre si nunca se simuló la malla
//Pre: malla no es NULL
//Post: 
bool es_ganadora(malla_t *malla);

//Grafica la malla según un graficador de SDL
//Pre: ni malla ni renderer sonn NULL
//Post: se mostró la malla en pantalla
void malla_graficar(SDL_Renderer *renderer, malla_t *malla);

//prepara todo para poder llamar a malla_simular()
//Pre: malla no es null
//Post: se puede llamar a malla_simular()
void malla_iniciar_simulacion(malla_t *malla);

//Simula el sistema masas-resortes de la malla
//Pre: se llamó (una vez, al principio) a malla_iniciar_simulacion()
//Post: se simuló un instante dt de el sistema
void malla_simular(malla_t *malla);



#endif

