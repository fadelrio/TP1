#include "vector.h"
#include <math.h>

float vector_norma(size_t d,const float v[d]){
	float norma = 0;
	for (size_t i = 0; i < d; i++)
		norma += v[i]*v[i];
	return sqrt(norma);
}

void vector_suma(size_t d, const float a[d], const float b[d], float c[d]){
	for (size_t i = 0; i < d; i++)
		c[i] = a[i] + b[i];
}
