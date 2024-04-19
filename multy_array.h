#ifndef multy_array_h
#define multy_array_h

#include <stdio.h>
#include <stdlib.h>

typedef double T;

T** multy_array(T** a,T** b,int n,int m,int k)
{
	T** c = (T**)malloc(n*sizeof(T*));
	for(int i = 0;i<n;i++)
		c[i] = (T*)malloc(k*sizeof(T));
	for(int i = 0;i<n;i++)
		for(int j = 0;j<n;j++)
			c[i][j] = (T)0;
	for(int i = 0;i<n;i++)
		for(int j = 0;j<k;j++)
			for(int q = 0;q<m;q++)
			{
				c[i][j] += a[i][q]*b[q][j];
			}
	return c;
}

#endif
