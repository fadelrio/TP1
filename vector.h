#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdbool.h>


//devuelve la norma de el vector
float vector_norma(size_t d,const float v[]);

//devuelve por interfaz la suma de los vectores a y b en el vector c
void vector_suma(size_t d, const float a[], const float b[], float c[]);

void vector_resta(size_t d, const float a[], const float b[], float c[]);

bool vector_comparar(size_t d, const float a[], const float b[]);

//devuelve por interfaz la resta de los vectores a y b en el vector c
void vector_resta(size_t d, const float a[], const float b[], float c[]);

//devuelve por nombre la distancia de un punto p1 a p2
float distancia_a_punto(const float p1[], const float p2[]);

//devuelve por nombre la distancia de un segmento (resorte) a un punto
float distancia_a_segmento(const float punto[], const float posi[], const float posf[]);

#endif
