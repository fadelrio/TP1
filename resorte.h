#ifndef RESORTE_H
#define RESORTE_H


typedef struct resorte resorte_t;
typedef struct nodo nodo_t;

//nodo1 y nodo2 no pueden ser NULL
resorte_t *resorte_crear(nodo_t *nodo1, nodo_t *nodo2);

void resorte_destruir(resorte_t resorte);

//devuelve la constante k actual del resorte
float resorte_obtener_constante(resorte_t resorte);

//devuelve la longitud actual del resorte
float resorte_obtener_longitud(resorte_t resorte);

//devuelve un arreglo con los dos nodos por interfaz
void resorte_obtener_nodos(resorte_t resorte, nodo_t **nodos);

#endif
