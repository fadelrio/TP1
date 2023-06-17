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

nodo_t *nodo_crear(float posicion[2], bool es_fijo);

//no se ocupa de liberar los resortes asociados
void nodo_destruir(nodo_t *nodo);

//agrega un resorte a los asociados al nodo
bool nodo_agregar_resorte(resorte_t *resorte, nodo_t *nodo);

//elimina un resorte de los asociados al nodo. devuelve false si el resorte no estaba vinculado al nodo. No libera la memoria del resorte
bool nodo_eliminar_resorte(resorte_t *resorte, nodo_t *nodo, bool (*comparador)(resorte_t*, resorte_t*));
	
//devuelve un puntero a la lista de resortes de la estructura
resorte_t **nodo_obtener_resortes(const nodo_t *nodo);

//devuelve la cantidad de resortes unidos al nodo
size_t nodo_obtener_cantidad_de_resortes(const nodo_t *nodo);

//devuelve por interfaz a posicion un vector de dos elementos donde el primero corresponde a las x y el segundo a las y.
void nodo_obtener_posicion(const nodo_t *nodo, float posicion[2]);

//cambia la posicion actual del nodo
void nodo_actualizar_posicion(nodo_t *nodo, float posicion[2]);

//devuelve si ambos nodos tienen la misma posicion
bool nodo_comparar(nodo_t *nodo1, nodo_t *nodo2);

//devuelve si el nodo es fijo o no
bool nodo_es_fijo(const nodo_t *nodo);

#endif
