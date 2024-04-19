#ifndef eigenvecto_eigenvalue_h
#define eigenvecto_eigenvalue_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "multy_array.h"

#define Err 1e-4

typedef double T;

T** Jacobi(T** C_matrix,int M,int ii,int jj,T rPhi)
{
	T** Temp = (T**)malloc(M*sizeof(T*));
	for(int i = 0;i<M;i++)
		Temp[i] = (T*)malloc(M*sizeof(T));
	for(int i = 0;i<M;i++)
		for(int j = 0; j<M;j++)
		{
			Temp[i][j] = C_matrix[i][j];
			C_matrix[i][j] = (T)0;
		}
	T rSp = sin(rPhi);
	T rCp = cos(rPhi);
//	 multy 3 matrix
	for(int i = 0;i<M;i++)
		for(int j = 0;j<M;j++)
			if(i == ii) // row i
				if(j == ii) 
					C_matrix[i][j] = Temp[ii][ii]*rCp*rCp + Temp[jj][jj]*rSp*rSp + 2*Temp[ii][jj]*rCp*rSp;
				else 
					if(j == jj) 
						C_matrix[i][j] = (Temp[jj][jj]-Temp[ii][ii])*rSp*rCp + Temp[ii][jj]*(rCp*rCp-rSp*rSp);
					else 
						C_matrix[i][j] = Temp[ii][j]*rCp+Temp[jj][j]*rSp;
					 
			else 
				if(i == jj)  // row j
					if(j == ii)  
						C_matrix[i][j] = (Temp[jj][jj]-Temp[ii][ii])*rSp*rCp + Temp[ii][jj]*(rCp*rCp-rSp*rSp);
					else 
						if(j == jj) 
							C_matrix[i][j] = Temp[ii][ii]*rSp*rSp + Temp[jj][jj]*rCp*rCp - 2*Temp[ii][jj]*rCp*rSp;
					 	else 
						 	C_matrix[i][j] = Temp[jj][j]*rCp-Temp[ii][j]*rSp;
				else	// row l!=i,j
					if(j == ii) 
						C_matrix[i][j] = Temp[ii][i]*rCp+Temp[jj][i]*rSp;
					else 
						if(j ==jj) 
							C_matrix[i][j] = Temp[jj][i]*rCp-Temp[ii][i]*rSp;
						else 
							C_matrix[i][j] = Temp[i][j];
	
	for(int k = 0;k<M;k++)
		free(Temp[k]);
	free(Temp);
	
	return C_matrix;
}

T getMax(T** C_matrix,int M,int &ii,int &jj)
{
	T rmax = C_matrix[0][1];
	ii = 0;
	jj = 1;
	for(int i = 0;i<M;i++)
		for(int j =0;j<M;j++)
			if(i!=j)
				if(fabs(C_matrix[i][j])>rmax)
				{
					rmax = fabs(C_matrix[i][j]);
					ii = i;
					jj = j;
				}
	return rmax;
}

T** Eigenvecto_Eigenvalue(T** C_matrix,int M,T** Eigenvecto,T* Eigenvalue)
{
	int i,j;
	T rmax,rPhi;
	T** eVec =(T**) malloc(M*sizeof(T*));
	T** eTemp =(T**) malloc(M*sizeof(T*));
	T** eC   =(T**) malloc(M*sizeof(T*));
	
	for(int k = 0;k<M;k++)
	{
		eVec[k] = (T*)malloc(M*sizeof(T));
		eTemp[k] = (T*)malloc(M*sizeof(T));
		eC[k] = (T*)malloc(M*sizeof(T));
	}
	
	for( i = 0; i<M;i++)
		for( j = 0;j<M;j++)
		{
			eTemp[i][j] = (T)0;
			eVec[i][j] = (T)0;
			eC[i][j] = (T)0;
			if(i == j) eTemp[i][j] = (T)1;
		}
	while(1)
	{
		i=0,j=0;
		rmax = getMax(C_matrix,M,i,j);
		if(rmax <= Err) break;
		
		rPhi = atan((T)2*C_matrix[i][j]/(C_matrix[i][i]-C_matrix[j][j])) / (T)2;
		C_matrix = Jacobi(C_matrix,M,i,j,rPhi);
		for(int x = 0;x<M;x++)
			eC[x][x] = (T)1;
		eC[i][i] = cos(rPhi);
		eC[j][j] = eC[i][i];
		eC[j][i] = sin(rPhi);
		eC[i][j] = -eC[j][i];
		
		eVec = multy_array(eTemp,eC,M,M,M);
		for(int x = 0;x<M;x++)
			for(int y = 0;y<M;y++)
			{
				eTemp[x][y] = eVec[x][y];
				eVec[x][y] = (T)0;
				eC[x][y] = (T)0;
			}
	}
	for(int i = 0;i<M;i++)
	{
		Eigenvalue[i] = C_matrix[i][i];
		for(int j = 0;j<M;j++)
			Eigenvecto[i][j] = eTemp[i][j];
	}
			
	T* TempEigenvecto =(T*) malloc(M*sizeof(T));
	for(int i = 0;i<M;i++)
		for(int j = M-1;j>i;j--)
			if(Eigenvalue[j]>Eigenvalue[j-1])
			{
				T TempEigenvalue = Eigenvalue[j-1];
				Eigenvalue[j-1] = Eigenvalue[j];
				Eigenvalue[j] = TempEigenvalue;
				for(int k = 0;k<M;k++)
					TempEigenvecto[k] = Eigenvecto[k][j-1];
				for(int k = 0;k<M;k++)
					Eigenvecto[k][j-1] = Eigenvecto[k][j];
				for(int k = 0;k<M;k++)
					Eigenvecto[k][j] = TempEigenvecto[k];
			}
	for(int k = 0;k<M;k++)
	{
		free(eTemp[k]);
		free(eVec[k]);
		free(eC[k]);	
	}
		
	free(eTemp);
	free(eVec);
	free(eC);
	free(TempEigenvecto);
	return Eigenvecto;
}

#endif
