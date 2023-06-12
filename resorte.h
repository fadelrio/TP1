#ifndef RESORTE_H
#define RESORTE_H
#include <stdbool.h>

/*
Muchas de las funciones y el funcionamiento general de este TDA está pensado para que haya otro TDA que se ocupe de administrarlo en conjunto con nodo_t.
*/

typedef struct resorte resorte_t;
typedef struct nodo nodo_t;

//nodo1 y nodo2 no pueden ser NULL
resorte_t *resorte_crear( nodo_t *nodo1, nodo_t *nodo2);

//no se ocupa de liberar la memoria de los nodos asociados
void resorte_destruir(resorte_t *resorte);

//devuelve la constante k actual del resorte
float resorte_obtener_constante(resorte_t *resorte);

//devuelve la longitud actual del resorte
float resorte_obtener_longitud(resorte_t *resorte);

//devuelve un arreglo con los dos nodos por interfaz
nodo_t **resorte_obtener_nodos(resorte_t *resorte);

//devuelve si resorte1 es igual a resorte2
bool resorte_comparar(resorte_t *resorte1, resorte_t *resorte2);

//actualiza datos internos del resorte, se debe ejecutar cada vez que se realice una actualizacion a las masas a las que esta sujeto el resorte
bool resorte_actualizar(resorte_t *resorte);

#endif
