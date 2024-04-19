#ifndef invert_array_h
#define invert_array_h

#include <stdio.h>
#include <stdlib.h>

typedef double T;

T** invert_array(T** a,int n,int m)
{
	T** c = (T**)malloc(m*sizeof(T*));
	for(int i = 0;i<m;i++)
		c[i] = (T*)malloc(n*sizeof(T));
	for(int i = 0;i<m;i++)
		for(int j = 0;j<n;j++)
			c[i][j] = a[j][i];
	return c;
}

#endif
