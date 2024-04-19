#ifndef datanew_h
#define datanew_h

#include <stdio.h>
#include <stdlib.h>

typedef double T;

T** datanew_vecto(T** A_matrix,T* X,int N,int M)
{
	T** Tempdata = (T**) malloc(N*sizeof(T*));
	for(int i = 0;i<N;i++) 
		Tempdata[i] = (T*) malloc(M*sizeof(T));
	for(int i = 0;i<N;i++)
		for(int j = 0;j<M;j++)
			Tempdata[i][j] = A_matrix[i][j] - X[i];
	return Tempdata;
}

#endif
