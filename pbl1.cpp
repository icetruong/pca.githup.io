#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "pca.h"

typedef double T;

int main()
{
	int N,M,K;
	FILE *fptr;
	char x[50];
	printf("nhap case ban muon test: ");
	gets(x);
	strcat(x,".txt");
	fptr = fopen(x, "r");
	fscanf(fptr, "%d %d", &N, &M); 
	T** a = (T**)malloc(N*sizeof(T*));
	for(int i = 0;i<N;i++)
		a[i] = (T*)malloc(M*sizeof(T*));
	for (int i = 0; i < N; i++) 
        for (int j = 0; j < M; j++) 
        	fscanf(fptr, "%lf", &a[i][j]);
    fclose(fptr);
	T* b =(T*) malloc(N*sizeof(T*));
	T** c = (T**)malloc(N*sizeof(T*));
	for(int i = 0;i<N;i++)
		c[i] = (T*)malloc(N*sizeof(T*));

	c = PCA(a,N,M,K);
	for(int i = 0; i<K;i++){
			for(int j = 0; j<M;j++)
			printf("%.4f ",c[i][j]);
	printf("\n");
	}
}
