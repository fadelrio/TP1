#include "lista.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    void *dato;
    struct nodo *prox;
} nodo_t;

struct lista {
    nodo_t *prim;
    nodo_t *ult;
    size_t largo;
};

struct lista_iter {
    lista_t *lista;
    nodo_t *ant;
    nodo_t *act;
};


static nodo_t *crear_nodo(void *dato, nodo_t *prox) {
    nodo_t *n = malloc(sizeof(nodo_t));
    if(n == NULL) return NULL;

    n->dato = dato;
    n->prox = prox;

    return n;
}


lista_t *lista_crear() {
    lista_t *l = malloc(sizeof(lista_t));
    if(l == NULL) return NULL;

    l->prim = NULL;
    l->ult = NULL;
    l->largo = 0;

    return l;
}

bool lista_esta_vacia(const lista_t *l) {
    return l->largo == 0;
}

bool lista_insertar_primero(lista_t *l, void *dato) {
    nodo_t *n = crear_nodo(dato, l->prim);
    if(n == NULL) return false;

    l->largo++;
    l->prim = n;

    if(l->ult == NULL)
        l->ult = n;

    return true;
}

bool lista_insertar_ultimo(lista_t *l, void *dato) {
    nodo_t *n = crear_nodo(dato, NULL);
    if(n == NULL) return NULL;

    if(l->ult != NULL)
        l->ult->prox = n;

    l->ult = n;

    if(l->prim == NULL)
        l->prim = n;

    l->largo++;

    return true;
}

void *lista_borrar_primero(lista_t *l) {
    if(l->prim == NULL) return NULL;

    nodo_t *n = l->prim;
    void *dato = n->dato;

    l->prim = n->prox;
    free(n);

    if(l->ult == n)
        l->ult = NULL;

    l->largo--;

    return dato;
}

size_t lista_largo(const lista_t *l) {
    return l->largo;
}

void lista_destruir(lista_t *l, void (*destruir_dato)(void *)) {
    while(l->prim != NULL) {
        nodo_t *n = l->prim;
        if(destruir_dato)
            destruir_dato(n->dato);
        l->prim = n->prox;
        free(n);
    }
    free(l);
}

void lista_recorrer(lista_t *l, bool (*visitar)(void *, void *), void *extra) {
    nodo_t *n = l->prim;
    while(n) {
        if(!visitar(n->dato, extra))
            return;
        n = n->prox;
    }
}


lista_iter_t *lista_iter_crear(lista_t *l) {
    lista_iter_t *iter = malloc(sizeof(lista_iter_t));
    if(iter == NULL) return NULL;

    iter->lista = l;
    iter->ant = NULL;
    iter->act = l->prim;

    return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter) {
    if(iter->act == NULL)
        return false;

    iter->ant = iter->act;
    iter->act = iter->act->prox;

    return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter) {
    if(iter->act == NULL)
        return NULL;

    return iter->act->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter) {
    return iter->act == NULL;
}

void lista_iter_destruir(lista_iter_t *iter) {
    free(iter);
}


bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
    nodo_t *nuevo = crear_nodo(dato, iter->act);
    if(nuevo == NULL) return false;

    // Primera posición
    if(iter->ant == NULL)
        iter->lista->prim = nuevo;
    else
        iter->ant->prox = nuevo;

    // Última posición
    if(iter->act == NULL)
        iter->lista->ult = nuevo;

    iter->act = nuevo;
    iter->lista->largo++;

    return true;
}

void *lista_iter_borrar(lista_iter_t *iter) {
    if(iter->act == NULL)
        return NULL;

    nodo_t *nodo = iter->act;
    void *dato = nodo->dato;

    if(iter->ant == NULL)
        iter->lista->prim = nodo->prox;
    else
        iter->ant->prox = nodo->prox;

    if(nodo->prox == NULL)
        iter->lista->ult = iter->ant;

    iter->act = nodo->prox;
    iter->lista->largo--;
    free(nodo);

    return dato;
}

