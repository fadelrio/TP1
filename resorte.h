#ifndef RESORTE_H
#define RESORTE_H
#include <stdbool.h>
#include "config.h"
#include "nodo.h"

/*
Muchas de las funciones y el funcionamiento general de este TDA está pensado para que haya otro TDA que se ocupe de administrarlo en conjunto con nodo_t.
*/

//Crea un resorte en memoria nueva
//Pre: nodo1 y nodo2 no pueden ser NULL
//Post: Se crea el resorte y se incializan todos sus miembros
resorte_t *resorte_crear( nodo_t *nodo1, nodo_t *nodo2);

//Libera la memoria asociada a la estructura resorte 
//Post: no se ocupa de liberar la memoria de los nodos asociados
void resorte_destruir(resorte_t *resorte);

//Devuelve la constante k actual del resorte
//Pre: el resorte no es NULL
float resorte_obtener_constante(resorte_t *resorte);

//Devuelve la longitud actual del resorte
//Pre: el resorte no es NULL
float resorte_obtener_longitud(resorte_t *resorte);

//Devuelve un arreglo con los dos nodos por interfaz
//Pre: el resorte no es NULL
nodo_t **resorte_obtener_nodos(resorte_t *resorte);

//Devuelve si resorte1 es igual a resorte2
bool resorte_comparar(resorte_t *resorte1, resorte_t *resorte2);

//Actualiza datos internos del resorte, se debe ejecutar cada vez que se realice una actualizacion a las masas a las que esta sujeto el resorte
//Pre: el resorte no es NULL
bool resorte_actualizar(resorte_t *resorte);

//Devuelve si la longitud de el resorte no es mas de MAXIMO_ESTIRAMIENTO% respecto a la longitud inicial
//Pre: el resorte no es NULL
bool resorte_es_ganador(resorte_t *resorte);

#endif
