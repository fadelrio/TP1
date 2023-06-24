#include "malla.h"


#define R_CERCANIA 20 //POR PONER UN NUMERO
//pense que si ibamos a tratar a los resortes como listas enlazadas, por que no tambien a los nodos? y asi unificamos metodologias

struct malla {
    lista_t *nodos;
    lista_t *resortes;
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
    malla->nodo_cercano_actual = NULL;
    malla->resorte_cercano_actual = NULL;

    return malla;
}


static void _nodo_destruir(void *nodo){
    nodo_destruir((nodo_t *)nodo);
}

static void _resorte_destruir(void *resorte){
    resorte_destruir((resorte_t *)resorte);
}

void malla_destruir(malla_t *malla){
    lista_destruir(malla->nodos, _nodo_destruir);
    lista_destruir(malla->resortes, _resorte_destruir);
    free(malla);
}

bool agregar_nodo_a_malla(malla_t *malla, const float pos[], bool es_fijo){
    nodo_t *n = nodo_crear(pos, es_fijo);
    if(!n)
        return false;
    
    if(!lista_insertar_primero(malla->nodos, n))
        return false;
    
    return true;
}
static nodo_t *_agregar_nodo(malla_t *malla, const float pos[], bool es_fijo){
	nodo_t *n = nodo_crear(pos, es_fijo);
    if(!n)
        return NULL;
    
    if(!lista_insertar_primero(malla->nodos, n))
        return NULL;
    
    return n;
}

bool agregar_resorte_a_malla(malla_t *malla, const float posi[], const float posf[]){
    nodo_t *nodo = _agregar_nodo(malla, posf, false);
	if (!nodo)
		return false;
	resorte_t *r = resorte_crear(malla->nodo_cercano_actual, nodo);
    if(!r)
        return false;
     
    if(!nodo_agregar_resorte(r, nodo))
		return false;
	if(!nodo_agregar_resorte(r, malla->nodo_cercano_actual)){
		malla_eliminar_elemento(malla, NODO);
		return false;
	}

    if(!lista_insertar_primero(malla->resortes, r)){
		malla_eliminar_elemento(malla, NODO);
		nodo_eliminar_resorte(r,malla->nodo_cercano_actual,resorte_comparar);
		return false;
	}

        return false;

	malla->nodo_cercano_actual = nodo;

    return true;
}

size_t malla_obtener_cant_nodos(malla_t *malla){
    return lista_largo(malla->nodos);
}


static void malla_que_hay_cerca(malla_t *malla, const float punto[], tipo_t tipo){
    //Si la lista de nodos está vacía implica que también lo está la de resortes
    if(lista_esta_vacia(malla->nodos)){
        tipo = NADA;
        return;
    }

    //iteramos la lista de nodos y de resortes para saber que es lo que hay más cercano al punto
    lista_iter_t *nodo_iter = lista_iter_crear(malla->nodos);

    float mindist = R_CERCANIA, distancia;

    while (!lista_iter_al_final(nodo_iter)){
        nodo_t *naux = lista_iter_ver_actual(nodo_iter);
        float posaux[2];
        nodo_obtener_posicion(naux, posaux);
        distancia = distancia_a_punto(posaux, punto);
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
        nodo_t **nodosaux = resorte_obtener_nodos(raux);
        float posiaux[2], posfaux[2];
        nodo_obtener_posicion(nodosaux[0], posiaux);
        nodo_obtener_posicion(nodosaux[1], posfaux);
        distancia = distancia_a_segmento(punto, posiaux, posfaux);
       
        if(distancia < mindist){
            tipo = RESORTE;
            malla->resorte_cercano_actual = raux;
            lista_iter_destruir(res_iter);
        }

        if(!lista_iter_avanzar(nodo_iter))
            break;
    }

    lista_iter_destruir(res_iter);
    malla->nodo_cercano_actual = NULL;
    malla->resorte_cercano_actual = NULL;
    tipo = NADA;   
}

tipo_t malla_tipo_cercano(malla_t *malla, const float pos[]){
    tipo_t tipo = NADA; //solo inicializo para q no me tire el warning huncha pelotas
    malla_que_hay_cerca(malla, pos, tipo);
    return tipo;
}


static void _malla_eliminar_resorte(malla_t *malla){
    lista_iter_t *res_iter = lista_iter_crear(malla->resortes);
        while (!lista_iter_al_final(res_iter)){
            if(!lista_iter_avanzar(res_iter) || resorte_comparar(lista_iter_ver_actual(res_iter), malla->resorte_cercano_actual))
                break;
    }
    resorte_t *res = lista_iter_borrar(res_iter); //solo hago esta asignación pq lista_iter_borrar no es void
    lista_iter_destruir(res_iter);
    resorte_destruir(res);
}

static void _malla_eliminar_nodo(malla_t *malla){
    lista_iter_t *nodo_iter = lista_iter_crear(malla->nodos);
    while (!lista_iter_al_final(nodo_iter)){
        if(!lista_iter_avanzar(nodo_iter) || nodo_comparar(lista_iter_ver_actual(nodo_iter), malla->nodo_cercano_actual)) //Habria q implementar esta funcion
            break;
    }

    nodo_t *naux = lista_iter_borrar(nodo_iter);
    resorte_t **rauxs = nodo_obtener_resortes(naux);
    for(size_t i = 0; i < nodo_obtener_cantidad_de_resortes(naux); i++){
        malla->resorte_cercano_actual = rauxs[i];
        _malla_eliminar_resorte(malla);
    }

    nodo_destruir(naux);
    lista_iter_destruir(nodo_iter);
}

typedef void (*feliminar_t)(malla_t *);
feliminar_t funciones_eliminar[] = {_malla_eliminar_nodo, _malla_eliminar_resorte};

void malla_eliminar_elemento(malla_t *malla, tipo_t tipo){
    /*feliminar_t funcion = funciones_eliminar[tipo];
    return funcion(malla);*/
    funciones_eliminar[tipo](malla); //ta bien asi o es como lo anterior?
}