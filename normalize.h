#ifndef normalize_h
#define normalize_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef double T;

T** normalize(T** Eigenvecto,int N,int M)
{
	T* temp = (T*) malloc(M*sizeof(T));
	for(int i = 0;i<M;i++)
		temp[i] = (T)0;
	for(int j = 0;j<M;j++)
	{
		for(int i = 0;i<N;i++)
			temp[j] += Eigenvecto[i][j]*Eigenvecto[i][j];
		temp[j] = sqrt(temp[j]);
	}
	for(int i = 0;i<N;i++)
		for(int j = 0;j<M;j++)
			Eigenvecto[i][j] = Eigenvecto[i][j] / temp[j];
	free(temp);
	return Eigenvecto;
}

#endif
