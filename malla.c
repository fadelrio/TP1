#include "malla.h"
#include "lista.h"
#include "nodo.h"
#include "vector.h"
#include "resorte.h"
#include "simulador.h"
#include "config.h"


#define R_CERCANIA 2 //POR PONER UN NUMERO

//pense que si ibamos a tratar a los resortes como listas enlazadas, por que no tambien a los nodos? y asi unificamos metodologias

struct malla {
    lista_t *nodos;
    lista_t *resortes;
	nodo_t *nodo_cercano_actual;
	resorte_t *resorte_cercano_actual;
	simulador_t *simulador;
};

static void _nodo_destruir(void *nodo);

static void _resorte_destruir(void *resorte);

static nodo_t *_agregar_nodo(malla_t *malla, const float pos[2], bool es_fijo);

static void malla_que_hay_cerca(malla_t *malla, const float punto[], tipo_t *tipo);

static void _malla_eliminar_resorte(malla_t *malla);

static void _malla_eliminar_nodo(malla_t *malla);

static nodo_t **_obtener_nodos_aledanos(nodo_t *nodo);

static nodo_t *_obtener_nodo_mas_lejano(size_t n, nodo_t **nodos, const float pos[]);

static bool _resorte_es_ganador_visitar(void *resorte, void *es_ganador);

static bool _graficar_nodo(void *nodo, void *renderer);

static bool _graficar_resorte(void *resorte, void *renderer);





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
    malla->simulador = NULL;
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
    simulador_destruir(malla->simulador);

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


static nodo_t *_agregar_nodo(malla_t *malla, const float pos[2], bool es_fijo){
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


	malla->nodo_cercano_actual = nodo;

  return true;
}

size_t malla_obtener_cant_nodos(malla_t *malla){
    return lista_largo(malla->nodos);
}


static void malla_que_hay_cerca(malla_t *malla, const float punto[], tipo_t *tipo){
    //Si la lista de nodos está vacía implica que también lo está la de resortes
    if(lista_esta_vacia(malla->nodos)){
        *tipo = NADA;
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
            *tipo = NODO;
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
            *tipo = RESORTE;
            malla->resorte_cercano_actual = raux;
            lista_iter_destruir(res_iter);
        }

        if(!lista_iter_avanzar(nodo_iter))
            break;
    }

    lista_iter_destruir(res_iter);
    malla->nodo_cercano_actual = NULL;
    malla->resorte_cercano_actual = NULL;
    *tipo = NADA;   
}

tipo_t malla_tipo_cercano(malla_t *malla, const float pos[]){
    tipo_t tipo = NADA; //solo inicializo para q no me tire el warning huncha pelotas
    malla_que_hay_cerca(malla, pos, &tipo);
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
	nodo_t *nodo_mas_lejano = nodos[0];
	for (size_t i = 1; i < n; i++){
		float aux[2];
		nodo_obtener_posicion(nodos[i],aux);
		float aux1[2];
		nodo_obtener_posicion(nodo_mas_lejano, aux1);
		if (distancia_a_punto(aux, pos) > distancia_a_punto(aux1, pos))
			nodo_mas_lejano = nodos[i];
	}
	return nodo_mas_lejano; 
}



//Pre: Se llamó a que_hay_cerca antes, devolvió NODO y la malla no es nula. Si se ejecuta después de agregar_resorte, se moverá al nodo final de el resorte. Se puede llamar sucesivas veces para mover al mismo nodo sin llamar a que_hay_cerca cada vez. 
//Post: Se movió el nodo a pos[], o a el punto mas cerca a pos[] en el caso de que las longitudes de los resortes no lo permitan
bool mover_nodo(malla_t *malla, const float pos[2]){
	if (nodo_es_fijo(malla->nodo_cercano_actual))
		return false;
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
		nodo_en_uso = nodos_aledanos[0];	
	}else{
		nodo_en_uso = _obtener_nodo_mas_lejano(nres, nodos_aledanos, pos);
	}
	float pos_nodo_en_uso[2];
	nodo_obtener_posicion(nodo_en_uso, pos_nodo_en_uso);
	if (distancia_a_punto(pos_nodo_en_uso, pos) <= L0_MAX){
		nodo_actualizar_posicion(malla->nodo_cercano_actual, pos);
	}else{															//planteo algebraico para encontrar un punto a distancia L0_MAX en la recta que 
		float nodo_pos[2];
		nodo_obtener_posicion(nodo_en_uso, nodo_pos);		//conecta al nodo con pos
		float aux[2];
		vector_resta(2, pos, nodo_pos, aux);
		float escalar = (L0_MAX)/(vector_norma(2, aux));
		float producto[2];
		vector_producto_por_escalar(2, aux, producto, escalar);
		float pos_final[2];
		vector_suma(2, producto, nodo_pos, pos_final);
		nodo_actualizar_posicion(malla->nodo_cercano_actual, pos_final);
	}
		
	//actualizacion de resortes
	resorte_t **resortes = nodo_obtener_resortes(malla->nodo_cercano_actual);
	
	for (size_t i = 0; i<nres; i++)
		resorte_actualizar(resortes[i]);
	free(nodos_aledanos);
	return true;
	
}

void finalizar_mover_nodo(malla_t *malla){
	lista_iter_t *iter = lista_iter_crear(malla->nodos);
	bool condicion;
	nodo_t *nodo_actual;
	float aux[2];
	float aux1[2];
	do {
		nodo_actual = lista_iter_ver_actual(iter);
		nodo_obtener_posicion(malla->nodo_cercano_actual,aux);
		nodo_obtener_posicion(nodo_actual, aux1);
		condicion = (distancia_a_punto(aux, aux1) < R_CERCANIA);
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

bool es_ganadora(malla_t *malla){
	bool es_g;
	lista_recorrer(malla->resortes, _resorte_es_ganador_visitar, &es_g);
	return es_g && !lista_esta_vacia(malla->resortes);
}


static bool _resorte_es_ganador_visitar(void *resorte, void *es_ganador){
	resorte_t *res = resorte;
	bool *es_g = es_ganador;
	*es_g = resorte_es_ganador(res);
	return *es_g;
}

void malla_graficar(SDL_Renderer *renderer, malla_t *malla){
	lista_recorrer(malla->nodos, _graficar_nodo, renderer);
	lista_recorrer(malla->resortes, _graficar_resorte, renderer);
}

static bool _graficar_nodo(void *nodo, void *renderer){
	SDL_Renderer *ren = renderer;
	nodo_t *n = nodo;
	float pos[2];
	nodo_obtener_posicion(n, pos);
	vector_producto_por_escalar_ons(2, pos, 50);
	if (nodo_es_fijo(n)){
		SDL_SetRenderDrawColor(ren, 0x00, 0xFF, 0x00, 0x00);
	}else
		SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
	float ancho = 10;
	SDL_Rect r1 = {pos[0] - ancho/2, pos[1] - ancho/2, ancho, ancho};
	SDL_RenderDrawRect(ren, &r1);
	return true;
}

static bool _graficar_resorte(void *resorte, void *renderer){
	SDL_Renderer *ren = renderer;
	resorte_t *res = resorte;
	float pos1[2];
	float pos2[2];
	nodo_t **nodos = resorte_obtener_nodos(res);
	nodo_obtener_posicion(nodos[0], pos1);
	nodo_obtener_posicion(nodos[1], pos2);
	vector_producto_por_escalar_ons(2, pos1, 50);
	vector_producto_por_escalar_ons(2, pos2, 50);
	if(resorte_es_ganador(res)){
		SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0xFF, 0x00);
	}else
		SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0x00);
	SDL_RenderDrawLine(ren, pos1[0], pos1[1], pos2[0], pos2[1]);
	return true;
}

void malla_iniciar_simulacion(malla_t *malla){
	malla->simulador = simulador_crear(malla->nodos, malla->resortes);
}

void malla_simular(malla_t *malla){
	simulador_simular(malla->simulador, DT);
}

typedef void (*feliminar_t)(malla_t *);
feliminar_t funciones_eliminar[] = {_malla_eliminar_nodo, _malla_eliminar_resorte};

void malla_eliminar_elemento(malla_t *malla, tipo_t tipo){
    /*feliminar_t funcion = funciones_eliminar[tipo];
    return funcion(malla);*/
    funciones_eliminar[tipo](malla); //ta bien asi o es como lo anterior?
}

