#ifndef RESORTE_H
#define RESORTE_H


typedef struct resorte resorte_t;
typedef struct nodo nodo_t;

//nodo1 y nodo2 no pueden ser NULL
resorte_t *resorte_crear(const nodo_t *nodo1,const nodo_t *nodo2);

void resorte_destruir(resorte_t *resorte);

//devuelve la constante k actual del resorte
float resorte_obtener_constante(resorte_t *resorte);

//devuelve la longitud actual del resorte
float resorte_obtener_longitud(resorte_t *resorte);

//devuelve un arreglo con los dos nodos por interfaz
void resorte_obtener_nodos(resorte_t *resorte, nodo_t **nodos);

//devuelve si resorte1 es igual a resorte2
bool resorte_comparar(resorte_t *resorte1, resorte_t *resorte2);

//actualiza datos internos del resorte, se debe ejecutar cada vez que se realice una actualizacion a las masas a las que esta sujeto el resorte
bool resorte_actualizar(resorte_t *resorte);

#endif
