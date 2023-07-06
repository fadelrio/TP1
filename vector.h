#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>


//devuelve por nombre la norma del vector v
float vector_norma(size_t d,const float v[d]);

//devuelve por interfaz la suma de los vectores a y b en el vector c
void vector_suma(size_t d, const float a[d], const float b[d], float c[d]);

//devuelve true si a y b son iguales, false si no
bool vector_comparar(size_t d, const float a[d], const float b[d]);

//devuelve por interfaz la resta de los vectores a y b en el vector c
void vector_resta(size_t d, const float a[d], const float b[d], float c[d]);

//devuelve por interfaz la suma de los vectores a y b en el vector c
void vector_producto_por_escalar(size_t d, const float a[d], float b[d], float escalar);

//devuelve por nombre el producto interno/escalar de a y b
float producto_interno(size_t d, const float a[d], const float b[d]);

//realiza un producto por escalar on site / in place (sobre el mismo vector)
void vector_producto_por_escalar_ons(size_t d, float a[d], float escalar);

//devuelve por nombre la distancia de un punto p1 a p2
float distancia_a_punto(const float p1[], const float p2[]);

//devuelve por nombre la distancia de un segmento (resorte) a un punto
float distancia_a_segmento(const float punto[], const float posi[], const float posf[]);


#endif
