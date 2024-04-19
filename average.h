#ifndef average_h
#define average_h

#include <stdio.h>
#include <stdlib.h>

typedef double T;

T* average_vecto(T** A_matrix,int N,int M)
{
	T* X =(T*) malloc(N*sizeof(T));
	for(int i = 0;i<N;i++) X[i] = (T)0;
	for(int i = 0;i<N;i++){
		for(int j = 0;j<M;j++)
			X[i] += A_matrix[i][j];
		X[i]=X[i]/ M;
	}
	return X;
}
#endif
