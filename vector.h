#ifndef VECTOR_H
#define VECTOR_H


//devuelve la norma de el vector
float vector_norma(size_t d,const float v[d]);

//devuelve por interfaz la suma de los vectores a y b en el vector c
void vector_suma(size_t d, const float a[d], const float b[d], float c[d]);

//devuelve por interfaz la resta de los vectores a y b en el vector c
void vector_resta(size_t d, const float a[], const float b[], float c[]);

//devuelve por interfaz la suma de los vectores a y b en el vector c
static void vector_producto_por_escalar(size_t d, const float a[], const float b[], float escalar);

//devuelve por nombre el producto interno/escalar de a y b
static float producto_interno(size_t d, const float a[], const float b[]);

//devuelve por nombre el parametro alpha que define que punto de un resorte es el mas cercano a "a"
static float parametro_distancia(const float a[], const resorte_t *resorte);

//devuelve por nombre la distancia de un punto p1 a p2
float distancia_a_punto(const float p1[], const float p2[]);

//devuelve por nombre la distancia de un segmento (resorte) a un punto
float distancia_a_segmento(const float punto[], const resorte_t *resorte);

#endif
