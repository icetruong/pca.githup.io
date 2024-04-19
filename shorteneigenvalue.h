#ifndef shorteneigenvalue_h
#define shorteneigenvalue_h

#include <stdio.h>
#include <stdlib.h>

typedef double T;

int shorteneigenvalue(T* Eigenvalue,int M)
{
	T sumM = (T)0,sumK = (T)0;
	for(int i = 0;i<M;i++)
		sumM += Eigenvalue[i];
	for(int i = 0;i<M;i++)
	{
		sumK+=Eigenvalue[i];
		if(sumK/sumM > (T)0.95) return i+1;
	}
}

#endif
