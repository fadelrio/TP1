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

static nodo_t *_agregar_nodo(malla_t *malla, const float pos[2], bool es_fijo){
	nodo_t *n = nodo_crear(pos, es_fijo);
    if(!n)
        return NULL;
    
    if(!lista_insertar_primero(malla->nodos, n))
        return NULL;
    
    malla->nnodos++;
    return n;
}

bool agregar_resorte_a_malla(malla_t *malla, const float posi[2], const float posf[2]){
    nodo_t *nodo = _agregar_nodo(malla, posf, false);
	if (!n)
		return false;
	resorte_t *r = resorte_crear(malla->nodo_cercano_actual, nodo);
    if(!r)
        return false;
     
    if(!nodo_agregar_resorte(r, nodo))
		return false;
	if(!nodo_agregar_resorte(r, malla->nodo_cercano_actual)){
		_eliminar_nodo_de_malla(malla, nodo);
		return false;
	}

    if(!lista_insertar_primero(malla->resortes, r)){
		_eliminar_nodo_de_malla(malla, nodo);
		nodo_eliminar_resorte(r,malla->nodo_cercano_actual,resorte_comparar);
		return false;
	}

        return false;

	malla->nodo_cercano_actual = nodo;
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
    //Si la lista de nodos está vacía implica que también lo está la de resortes
    if(lista_esta_vacia(malla->nodos)){
        return NULL;
    }

    //iteramos la lista de nodos y de resortes para saber que es lo que hay más cercano al punto
    lista_iter_t *nodo_iter = lista_iter_crear(malla->nodos);

    float mindist = R_CERCANIA, distancia;

    while (!lista_iter_al_final(nodo_iter)){
        distancia = distancia_a_punto(lista_iter_ver_actual(nodo_iter)->posicion, pos);
        if(distancia <= mindist){
            return (nodo_iter); //Ya si hay un solo nodo en la cercanía del radio, no puede haber 2
            //No se pueden crear dos nodos a una distancia entre ellos menor a R_CERCANIA, que el usuario no joda
        }
        if(!lista_iter_avanzar(nodo_iter))
            break;
    }

    lista_iter_t *res_iter = lista_iter_crear(malla->resortes);
    resorte_t *raux = NULL;
    
    while (!lista_iter_al_final(res_iter)){
        distancia = distancia_a_segmento(punto, lista_iter_ver_actual(res_iter));
       
        if(distancia < mindist){ 
            raux = lista_iter_ver_actual(res_iter);
            mindist = distancia;
            //Puede haber +1 resortes en un radio de cercanía si el usuario
            //fue tan hdp de haber creado dos resortes que salen de un nodo y que se 
            //separan por un angulo muy pequeño? Yencima puede ser tan hdp el usuario de haber
            //Clickeado jussssto entre los dos resortes??                       
        }
        if(!lista_iter_avanzar(nodo_iter))
            break;
    }
    lista_iter_destruir(nodo_iter);
    lista_iter_destruir(res_iter);
    return raux;     
}


static void _eliminar_nodo_de_malla(malla_t *malla, nodo_t *nodo){
    lista_iter_t *nodo_iter = lista_iter_crear(malla->nodos);
        while (!lista_iter_al_final(nodo_iter)){

        if(!lista_iter_avanzar(nodo_iter) || nodo_comparar(lista_iter_ver_actual(nodo_iter), nodo)) //Habria q implementar esta funcion
            break;
    }
    nodo = lista_iter_borrar(nodo_iter); //solo hago esta asignación pq lista_iter_borrar no es void
    lista_iter_destruir(nodo_iter);
	nodo_destruir(nodo);
}

void *eliminar_resorte_de_malla(malla_t *malla, resorte_t *res){
    lista_iter_t *res_iter = lista_iter_crear(malla->resortes);
        while (!lista_iter_al_final(res_iter)){

        if(!lista_iter_avanzar(res_iter) || resorte_comparar(lista_iter_ver_actual(res_iter), res))
            break;
    }
    res = lista_iter_borrar(res_iter); //solo hago esta asignación pq lista_iter_borrar no es void
    lista_iter_destruir(res_iter);
    return res;
}

static nodo_t **_obtener_nodos_aledanos(nodo_t *nodo){
	size_t nres;	
	nodo_t **nodos = malloc((nres = nodo_obtener_cantidad_de_resortes(nodo))* sizeof(nodo));
	resorte_t **resortes = nodo_obtener_resortes(nodo);
	for (size_t i = 0; i < nres; i++){
		nodo_t **aux = resorte_obtener_nodos(resortes[i]);
		if (aux[0] == nodo){ //se puede comparar de esta forma porque cada nodo de la malla existe una sola vez en memoria
			nodos[i] = aux[1];
			continue;
		}
		nodos[i] = aux[0];
	}
	return nodos;
}

//n > 1, nodos, pos != NULL
static nodo_t *_obtener_nodo_mas_lejano(size_t n, nodo_t **nodos, const float pos[]){
	nodo_t nodo_mas_lejano = nodos[0];
	for (size_t i = 1; i < n; i++){
		if (distancia_a_punto(nodo_obtener_posicion(nodos[i]), pos[]) > distancia_a_punto(nodo_obtener_posicion(nodo_mas_lejano), pos[]))
			nodo_mas_lejano = nodos[i];
	}
	return nodo_mas_lejano; 
}



//Pre: Se llamó a que_hay_cerca antes, devolvió NODO y la malla no es nula. Si se ejecuta después de agregar_resorte, se moverá al nodo final de el resorte. Se puede llamar sucesivas veces para mover al mismo nodo sin llamar a que_hay_cerca cada vez. 
//Post: Se movió el nodo a pos[], o a el punto mas cerca a pos[] en el caso de que las longitudes de los resortes no lo permitan
bool mover_nodo(malla_t *malla, const float pos[2]){
	size_t nres = nodo_obtener_cantidad_de_resortes(malla->nodo_cercano_actual);
	if (nres == 0){
		nodo_actualizar_posicion(malla->nodo_cercano_actual, pos);
		return true;
	}
	nodo_t **nodos_aledanos = _obtener_nodos_aledanos(malla->nodo_cercano_actual);
	if (nodos_aledanos == NULL)
		return false;
	

	nodo_t *nodo_en_uso;	
	if (nres == 1){
		nodo_en_uso = nodos[0];	
	}else{
		nodo_en_uso = _obtener_nodo_mas_lejano(nres, nodos, pos);
	}
	
	if (distancia_a_punto(nodo_en_uso, pos) <= L0_MAX){
		nodo_actualizar_posicion(malla->nodo_cercano_actual, pos)
	}else{															//planteo algebraico para encontrar un punto a distancia L0_MAX en la recta que 
		float nodo_pos[] = nodo_obtener_posicion(nodo_en_uso);		//conecta al nodo con pos
		float aux[];
		vector_resta(2, pos, nodo_pos, aux);
		float escalar = (L0_max)/(vector_norma(2, aux));
		float producto[];
		vector_producto_por_escalar(2, aux, producto, escalar);
		float pos_final[];
		vector_suma(2, producto, nodo_pos, pos_final);
		nodo_actualizar_posicion(malla->nodo_cercano_actual, pos_final);
	}
		
	//actualizacion de resortes
	resorte_t **resortes = nodo_obtener_resortes(malla->nodo_cercano_actual);
	size_t nres = nodo_obtener_cantidad_de_resortes(malla->nodo_cercano_actual);
	
	for (size_t i = 0; i<nres; i++)
		resorte_actualizar(resortes[i]);
	free(nodos_aledanos);
	return true;
	
}

void finalizar_mover_nodo(malla_t *malla){
	lista_iter_t *iter = lista_iter_crear(malla->nodos);
	bool condicion;
	nodo_t *nodo_actual;
	do {
		nodo_actual = lista_iter_ver_actual(iter);
		condicion = (distancia_a_punto(malla->nodo_cercano_actual, nodo_actual) < R_CERCANIA);
		if (condicion && (nodo_actual != malla->nodo_cercano_actual))
			break;
	}while (lista_iter_avanzar(iter));
	//pasar resortes de nodo_cercano_actual a nodo_actual y borrar nodo_cercano_actual. si lista iter no esta al final
	if (lista_iter_al_final(iter)){
		lista_iter_destruir(iter);
		return;
	}
	resorte_t **resortes = nodo_obtener_resortes(malla->nodo_cercano_actual);
	size_t nres = nodo_obtener_cantidad_de_resortes(malla->nodo_cercano_actual);
	for (size_t i = 0; i < nres; i++){
		nodo_agregar_resorte(resortes[i], nodo_actual);
		nodo_t **nodos_resorte = resorte_obtener_nodos(resortes[i]);
		if (nodos_resorte[0] == malla->nodo_cercano_actual){
			nodos_resorte[0] = nodo_actual;		
		}else {
			nodos_resorte[1] = nodo_actual;	
		}
		resorte_actualizar(resortes[i]);
	}
	nodo_destruir(malla->nodo_cercano_actual);
	malla->nodo_cercano_actual = NULL;
}



















