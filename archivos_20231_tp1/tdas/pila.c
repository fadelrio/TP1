#include "pila.h"
#include <stdlib.h>

typedef struct nodo {
    void *dato;
    struct nodo *sig;
} nodo_t;

struct pila {
    nodo_t *tope;
};

static nodo_t *crear_nodo(void *dato, nodo_t *sig) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if(nodo == NULL) return NULL;

    nodo->dato = dato;
    nodo->sig = sig;

    return nodo;
}

pila_t *pila_crear() {
    pila_t *p = malloc(sizeof(pila_t));
    if(p == NULL) return NULL;

    p->tope = NULL;

    return p;
}

void pila_destruir(pila_t *p, void (*destruir_dato)(void *)) {
    while(!pila_esta_vacia(p)) {
        void *dato = pila_desapilar(p);
        if(destruir_dato != NULL)
            destruir_dato(dato);
    }
    free(p);
}

bool pila_esta_vacia(const pila_t *p) {
    return p->tope == NULL;
}

void *pila_ver_tope(const pila_t *p) {
    if(p->tope == NULL) return NULL;

    return p->tope->dato;
}

bool pila_apilar(pila_t *p, void *dato) {
    nodo_t *n = crear_nodo(dato, p->tope);
    if(n == NULL) return false;

    p->tope = n;

    return true;
}

void *pila_desapilar(pila_t *p) {
    if(p->tope == NULL) return NULL;

    nodo_t *n = p->tope;
    void *dato = n->dato;

    p->tope = n->sig;
    free(n);

    return dato;
}
