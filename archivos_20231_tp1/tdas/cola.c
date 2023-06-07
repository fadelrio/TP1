#include "cola.h"
#include <stdlib.h>

typedef struct nodo {
    void *dato;
    struct nodo *sig;
} nodo_t;

struct cola {
    nodo_t *prim;
    nodo_t *ult;
};


static nodo_t *crear_nodo(void *dato) {
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if(nodo == NULL) return NULL;

    nodo->dato = dato;
    nodo->sig = NULL;

    return nodo;
}


cola_t *cola_crear() {
    cola_t *c = malloc(sizeof(cola_t));
    if(c == NULL) return NULL;

    c->prim = NULL;
    c->ult = NULL;

    return c;
}

bool cola_esta_vacia(const cola_t *c) {
    return c->prim == NULL;
}

bool cola_encolar(cola_t *c, void *dato) {
    nodo_t *n = crear_nodo(dato);
    if(n == NULL) return false;

    if(c->prim == NULL)
        c->prim = n;
    else
        c->ult->sig = n;

    c->ult = n;

    return true;
}

void *cola_ver_primero(const cola_t *c) {
    if(c->prim == NULL) return NULL;

    return c->prim->dato;
}

void *cola_desencolar(cola_t *c) {
    if(c->prim == NULL)
        return NULL;

    nodo_t *n = c->prim;
    void *dato = n->dato;

    c->prim = n->sig;
    if(c->prim == NULL)
        c->ult = NULL;

    free(n);

    return dato;
}

void cola_destruir(cola_t *c, void (*destruir_dato)(void *)) {
    while(!cola_esta_vacia(c)) {
        void *dato = cola_desencolar(c);
        if(destruir_dato != NULL)
            destruir_dato(dato);
    }
    free(c);
}

