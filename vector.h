#ifndef VECTOR_H
#define VECTOR_H


//devuelve la norma de el vector
float vector_norma(size_t d,const float v[d]);

//devuelve por interfaz la suma de los vectores a y b en el vector c
void vector_suma(size_t d, const float a[d], const float b[d], float c[d]);


#endif
