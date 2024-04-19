#ifndef PCA_H
#define PCA_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "average.h"
#include "datanew.h"
#include "invert_array.h"
#include "covar_matrix.h"
#include "eigenvecto_eigenvalue.h"
#include "normalize.h"
#include "shorteneigenvalue.h"


typedef double T;

T** PCA(T** Data,int N,int M,int &K)
{
	T* X =(T*) malloc(N*sizeof(T));// vecto_average;
	T** TempData = (T**) malloc(N*sizeof(T*));
	T** TempDatat = (T**) malloc(M*sizeof(T*));
	T** C_matrix = (T**) malloc(N*sizeof(T*));// matrix covariance
	T** A_At_matrix = (T**) malloc(M*sizeof(T*));
	T** Eigenvecto = (T**) malloc(N*sizeof(T*));
	T** Eigenvectot = (T**) malloc(M*sizeof(T*));
	T* Eigenvalue = (T*) malloc(N*sizeof(T));
	T** Temp_Eigenvecto = (T**) malloc(M*sizeof(T*));
	for(int i = 0;i<N;i++)
	{
		TempData[i] = (T*)malloc(M*sizeof(T));
		C_matrix[i] = (T*)malloc(N*sizeof(T));
		Eigenvecto[i] = (T*)malloc(N*sizeof(T));
	}
	for(int i = 0;i<M;i++)
	{
		TempDatat[i] = (T*)malloc(N*sizeof(T));
		Eigenvectot[i] = (T*)malloc(M*sizeof(T));
		A_At_matrix[i] = (T*)malloc(M*sizeof(T));
		Temp_Eigenvecto[i] = (T*)malloc(M*sizeof(T));
	}
		
	
	// initialize data 
	for(int i = 0;i<N;i++)
		for(int j = 0;j<M;j++)
		{
			TempData[i][j] = Data[i][j];
			C_matrix[i][j] = (T)0;
			Eigenvecto[i][j] = (T)0;
		}
	for(int i = 0;i<N;i++)
	{
		X[i] = (T)0;
		Eigenvalue[i] = (T)0;
	}
	//calculation
	X = average_vecto(Data,N,M);
	TempData = datanew_vecto(Data,X,N,M);
	TempDatat = invert_array(TempData,N,M);
	C_matrix = covar_matrix(TempData,TempDatat,N,M);
	if(N>M) 
	{	
		A_At_matrix = covar_matrix(TempDatat,TempData,M,N);
		Temp_Eigenvecto = Eigenvecto_Eigenvalue(A_At_matrix,M,Temp_Eigenvecto,Eigenvalue);
		Eigenvecto = multy_array(TempData,Temp_Eigenvecto,N,M,M);
		Eigenvecto = normalize(Eigenvecto,N,M);
	}
	else
		Eigenvecto = Eigenvecto_Eigenvalue(C_matrix,N,Eigenvecto,Eigenvalue);
	K = shorteneigenvalue(Eigenvalue,N);
	T** NewData = (T**) malloc(K*sizeof(T*));
	for(int i = 0;i<K;i++)
		NewData[i] = (T*) malloc(M*sizeof(T));
	Eigenvectot = invert_array(Eigenvecto,N,M);
	NewData = multy_array(Eigenvectot,TempData,K,N,M);
	for(int i = 0;i<N;i++)
	{
//		free(TempData[i]);
//		free(C_matrix[i]);
	}
	for(int i = 0;i<M;i++)
	{
//		free(Eigenvectot[i]);
//		free(Temp_Eigenvecto[i]);
	}
	free(X);
	free(TempData);
	free(TempDatat);
	free(C_matrix);
	free(A_At_matrix);
	free(Eigenvecto);
	free(Eigenvectot);
	free(Eigenvalue);
	free(Temp_Eigenvecto);
	return NewData;
}

#endif
