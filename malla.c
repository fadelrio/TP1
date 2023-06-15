#include "malla.h"
#include "lista.h"
#include "nodo.h"
#include "vector.h"
#include "resorte.h"

#define R_CERCANIA 20 //POR PONER UN NUMERO
//pense que si ibamos a tratar a los resortes como listas enlazadas, por que no tambien a los nodos? y asi unificamos metodologias

struct malla {
    lista_t *nodos;
    lista_t *resortes;
    size_t nres;
    size_t nnodos;
};

enum clase{
    NODO
    RESORTE
};

malla_t *malla_crear(){
    malla_t *malla = malloc(sizeof(malla_t));
    if(malla == NULL)
        return NULL;

    lista_t *nodos = lista_crear();
    if(nodos == NULL){
        free(malla);
        return NULL;
    }

    lista_t *resortes = lista_crear();
    if(resortes == NULL){
        free(malla);
        free(nodos);
        return NULL;
    }

    malla->nodos = nodos;
    malla->resortes = resortes;
    malla->nres = 0;
    malla->nnodos = 0;

    return malla;
}

void malla_destruir(malla_t *malla){
    lista_destruir(malla->nodos, nodo_destruir);
    lista_destruir(malla->resortes, resorte_destruir);
    free(malla);
}

bool agregar_nodo_a_malla(malla_t *malla, const float pos[2], bool es_fijo){
    nodo_t *n = nodo_crear(pos, es_fijo);
    if(!n)
        return false;
    
    if(!lista_insertar_primero(malla->nodos, n))
        return false;
    
    malla->nnodos++;
    return true;
}

bool agregar_resorte_a_malla(malla_t *malla, nodo_t *nodo1, nodo_t *nodo2){
    resorte_t *r = resorte_crear(nodo1, nodo2);
    if(!r)
        return false;
    
    if(!(nodo_agregar_resorte(r, nodo1) 
        && nodo_agregar_resorte(r, nodo2)
        && lista_insertar_primero(malla->resortes, r)))

        return false;

    malla->nres++;
    return true;
}

/*
static bool visitar_nodo(nodo_t *nodo, float punto[2]){ //nose si esta bien la firma
    return (distancia_a_punto(nodo->posicion, punto) <= R_CERCANIA);
}

static bool visitar_resorte(resorte_t *resorte, float punto[2]){ //nose si esta bien la firma
     //Ahora sí menor estricto pq si resulta que el punto clickeado esta igual de cerca
     //a un nodo o un resorte, al usuario le borramos el nodo conjunto el resorte por boludo
    return (distancia_a_segmento(punto, resorte) < R_CERCANIA);
}
*/

void *que_hay_cerca(malla_t *malla, const float pos[2]){
    //iteramos la lista de nodos y de resortes para saber que es lo que hay más cercano al punto
    lista_iter_t *nodo_iter = lista_iter_crear(malla->nodos);
    lista_iter_t *res_iter = lista_iter_crear(malla->resortes);

    float mindist = R_CERCANIA, distancia;
    nodo_t *naux = NULL;

    while (!lista_iter_al_final(nodo_iter)){
        distancia = distancia_a_punto(lista_iter_ver_actual(nodo_iter)->posicion, pos);
        if(distancia <= mindist){
            naux = lista_iter_ver_actual(nodo_iter); /*Yo se que esto es carísimo de hacer pero por 
            ahora no se me ocurrio otra forma de hacerlo, habria que conseguir el indice del 
            nodo mas cercano y despues devolver qué nodo hay en ese indice pero las listas enlazadas no tienen indice, 
            entoces se me ocurre que de alguna forma hay que usar a la funcion lista_recorrer, 
            puse arriba comentadas como serian las funciones visitar*/
            mindist = distancia;
        }
        if(!lista_iter_avanzar(nodo_iter))
            break;
    }
    
    while (!lista_iter_al_final(res_iter)){
        distancia = distancia_a_segmento(punto, lista_iter_ver_actual(res_iter));
       
        if(distancia < mindist){ 
            return lista_iter_ver_actual(res_iter);
            //Ya si hay un solo resorte más cerca que un nodo a un punto, entonces ese resorte es unico, no hay otro + cerca                       
        }
        if(!lista_iter_avanzar(nodo_iter))
            break;
    }
    lista_iter_destruir(nodo_iter);
    lista_iter_destruir(res_iter);
    return naux;     
}


void eliminar_nodo_de_malla(malla_t *malla, nodo_t *nodo){
    lista_iter_t *nodo_iter = lista_iter_crear(malla->nodos);
        while (!lista_iter_al_final(nodo_iter)){

        if(!lista_iter_avanzar(nodo_iter) || nodo_comparar(lista_iter_ver_actual(nodo_iter), nodo)) //Habria q implementar esta funcion
            break;
    }
    nodo = lista_iter_borrar(nodo_iter); //solo hago esta asignación pq lista_iter_borrar no es void
    lista_iter_destruir(nodo_iter);
}

void eliminar_resorte_de_malla(malla_t *malla, resorte_t *res){
    lista_iter_t *res_iter = lista_iter_crear(malla->resortes);
        while (!lista_iter_al_final(res_iter)){

        if(!lista_iter_avanzar(res_iter) || resorte_comparar(lista_iter_ver_actual(res_iter), res))
            break;
    }
    res = lista_iter_borrar(res_iter); //solo hago esta asignación pq lista_iter_borrar no es void
    lista_iter_destruir(res_iter);
}
