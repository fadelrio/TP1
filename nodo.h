#ifndef NODO_H
#define NODO_H

/*
Muchas de las funciones y el funcionamiento general de este TDA está pensado para que haya otro TDA que se ocupe de administrarlo en conjunto con resortes_t.
*/

#include <stddef.h>
#include <stdbool.h>

#define RESORTES_MAXIMOS 5

typedef struct nodo nodo_t;
typedef struct resorte resorte_t;

//Crea y devuelve por nombre un nodo con su posicion y fijación inicializados
nodo_t *nodo_crear(const float posicion[2], bool es_fijo);

//Pre: el nodo no es NULL y había sido creado
//Post: destruye el nodo pero no se ocupa de liberar los resortes asociados, solo la memoria que ocupan dentro de la estructura nodo
void nodo_destruir(nodo_t *nodo);

//Agrega un resorte a los asociados al nodo
//Pre: el nodo estaba creado e inicializado
//Post: Linkea un resorte a la lista
bool nodo_agregar_resorte(resorte_t *resorte, nodo_t *nodo);

//Elimina un resorte de los asociados al nodo.
//Pre: Tanto nodo como resorte no son NULL y la lista de resortes no está vacía
//Post: devuelve false si el resorte no estaba vinculado al nodo. No libera la memoria del resorte
bool nodo_eliminar_resorte(resorte_t *resorte, nodo_t *nodo, bool (*comparador)(resorte_t*, resorte_t*));
	
//Devuelve un puntero a la lista de resortes de la estructura
//Pre: el nodo estaba creado e inicializado
resorte_t **nodo_obtener_resortes(const nodo_t *nodo);

//Devuelve la cantidad de resortes unidos al nodo
//Pre: el nodo estaba creado e inicializado, y sus variables actualizadas al momento de ejecución de la función
size_t nodo_obtener_cantidad_de_resortes(const nodo_t *nodo);

//Devuelve por interfaz la posicion de un vector de dos elementos donde el primero corresponde a las x y el segundo a las y.
//Pre: el nodo estaba creado e inicializado, y sus variables actualizadas al momento de ejecución de la función
void nodo_obtener_posicion(const nodo_t *nodo, float posicion[2]);

//Cambia la posicion actual del nodo al vector "posición"
//Pre: El nodo estaba creado
void nodo_actualizar_posicion(nodo_t *nodo,const float posicion[2]);

//Devuelve si ambos nodos tienen la misma posicion
//Pre: ambos nodos estaban creados e inicializados
bool nodo_comparar(nodo_t *nodo1, nodo_t *nodo2);

//Devuelve si el nodo es fijo o no
//Pre: El nodo estaba creado
bool nodo_es_fijo(const nodo_t *nodo);

#endif
