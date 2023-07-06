#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>


//Devuelve por nombre la norma del vector v de tamaño d
//Pre: el vector está creado e inicializado
float vector_norma(size_t d,const float v[d]);

//Devuelve por interfaz la suma de los vectores a y b en el vector c
//Pre: tanto a, como b, como c deben tener el mismo tamaño: d
void vector_suma(size_t d, const float a[d], const float b[d], float c[d]);

//Devuelve true si a y b son iguales, false si no
//Pre: tanto a, como b, deben tener el mismo tamaño: d
bool vector_comparar(size_t d, const float a[d], const float b[d]);

//Devuelve por interfaz la resta de los vectores a y b en el vector c
//Pre: tanto a, como b, deben tener el mismo tamaño: d
//Post: c también será de longitud c
void vector_resta(size_t d, const float a[d], const float b[d], float c[d]);

//Devuelve por interfaz el producto de a por el flotante escalar en el vector b
void vector_producto_por_escalar(size_t d, const float a[d], float b[d], float escalar);

//Devuelve por nombre el producto interno/escalar entre a y b, ambos del mismo tamaño
float producto_interno(size_t d, const float a[d], const float b[d]);

//Realiza un producto por escalar on site / in place (sobre el mismo vector) del vector a de tamaño d
void vector_producto_por_escalar_ons(size_t d, float a[d], float escalar);

//Devuelve por nombre la distancia de un punto p1 a p2, ambos de coordenadas (x, y)
float distancia_a_punto(const float p1[], const float p2[]);

//Devuelve por nombre la distancia de un segmento, dados sus puntos inicial y final, a un punto
//Pre: todos los puntos poseen cordenadas (x, y)
float distancia_a_segmento(const float punto[], const float posi[], const float posf[]);


#endif
