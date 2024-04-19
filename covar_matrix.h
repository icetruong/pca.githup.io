#ifndef covar_matrix_h
#define covar_matrix_h

#include <stdio.h>
#include <stdlib.h>
#include "multy_array.h"

typedef double T;

T** covar_matrix(T** A_matrix,T** At_matrix,int N,int M)
{
	T** c = (T**)malloc(N*sizeof(T*));
	for(int i = 0;i<N;i++)
		c[i] = (T*)malloc(N*sizeof(T));
	c = multy_array(A_matrix,At_matrix,N,M,N);
	for(int i = 0;i<N;i++)
		for(int j = 0;j<N;j++)
			c[i][j] =(T) c[i][j] / (M-1);
	return c;
}

#endif
