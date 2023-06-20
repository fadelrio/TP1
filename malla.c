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
	nodo_t *nodo_cercano_actual;
	resorte_t *resorte_cercano_actual;
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
    malla->nodo_cercano_actual = NULL;
    malla->resorte_cercano_actual = NULL;

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


static void malla_que_hay_cerca(malla_t *malla, const float pos[2], tipo_t tipo){
    //Si la lista de nodos está vacía implica que también lo está la de resortes
    if(lista_esta_vacia(malla->nodos)){
        tipo = NADA;
    }

    //iteramos la lista de nodos y de resortes para saber que es lo que hay más cercano al punto
    lista_iter_t *nodo_iter = lista_iter_crear(malla->nodos);

    float mindist = R_CERCANIA, distancia;

    while (!lista_iter_al_final(nodo_iter)){
        nodo_t *naux = lista_iter_ver_actual(nodo_iter);
        distancia = distancia_a_punto(naux->posicion, pos);
        if(distancia <= mindist){
            tipo = NODO;
            malla->nodo_cercano_actual = naux;
            lista_iter_destruir(nodo_iter);
            //Ya si hay un solo nodo en la cercanía del radio, no puede haber 2
            //No se pueden crear dos nodos a una distancia entre ellos menor a R_CERCANIA, que el usuario no joda
        }
        if(!lista_iter_avanzar(nodo_iter))
            break;
    }

    lista_iter_destruir(nodo_iter);

    lista_iter_t *res_iter = lista_iter_crear(malla->resortes);
    
    while (!lista_iter_al_final(res_iter)){
        resorte_t *raux = lista_iter_ver_actual(res_iter);
        distancia = distancia_a_segmento(punto, raux);
       
        if(distancia < mindist){
            tipo = RESORTE;
            malla->resorte_cercano_actual = raux;
            lista_iter_destruir(res_iter);
        }

        if(!lista_iter_avanzar(nodo_iter))
            break;
    }

    lista_iter_destruir(res_iter);
    tipo = NADA;   
}

tipo_t malla_tipo_cercano(malla_t *malla, const float pos[2])
    tipo_t tipo;
    malla_que_hay_cerca(malla, pos, tipo);
    return tipo;


static bool malla_eliminar_resorte(malla_t *malla){
    lista_iter_t *res_iter = lista_iter_crear(malla->resortes);
        while (!lista_iter_al_final(res_iter)){
            if(!lista_iter_avanzar(res_iter) || resorte_comparar(lista_iter_ver_actual(res_iter), res))
                break;
    }
    res = lista_iter_borrar(res_iter); //solo hago esta asignación pq lista_iter_borrar no es void
    lista_iter_destruir(res_iter);
    resorte_destruir(res);
    return true;
}

static bool malla_eliminar_nodo(malla_t *malla){
    lista_iter_t *nodo_iter = lista_iter_crear(malla->nodos);
    while (!lista_iter_al_final(nodo_iter)){
        if(!lista_iter_avanzar(nodo_iter) || nodo_comparar(lista_iter_ver_actual(nodo_iter), malla->nodo_cercano_actual)) //Habria q implementar esta funcion
            break;
    }

    nodo_t *naux = lista_iter_borrar(nodo_iter); //solo hago esta asignación pq lista_iter_borrar no es void
    bool estado = true; 
    for(size_t i = 0; i < naux->nres; i++){
        if(!eliminar_resorte_de_malla(malla, naux->resortes[i])) //nose si esta bien escrito nodo->resortes[i]
            estado = false;
    }

    nodo_destruir(naux);
    lista_iter_destruir(nodo_iter);
    return estado;
}

feliminar_t funciones_eliminar[] = {malla_eliminar_nodo, malla_eliminar_resorte};

bool malla_eliminar_elemento(malla_t *malla, tipo_t tipo){
    /*feliminar_t funcion = funciones_eliminar[tipo];
    return funcion(malla);*/
    return funciones_eliminar[tipo](malla); //ta bien asi o es como lo anterior?
}


