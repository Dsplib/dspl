#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include "dspl.h"


#define N	3
#define M	2

int main()
{
	double b[N+1]={1.0,  2.0,  3.0,  0.0};	
	double a[N+1]={-2.0, 1.0, -1.0, -2.0};		
	
	double c[M+1]={1.0, 3.0, -2.0};	
	double d[M+1]={2.0, -1.0, -0.0};		
	
	double e[N*M+1];
	double f[N*M+1];
	
	HINSTANCE hDSPL;	/* DSPL.DLL handle */
	
	int n;
		
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
	
	/* Chebyshev type 2 filter analog prototype calculation */
	dspl_compos(b,a,N, d,c,M, f, e);
	
	/* print filter transfer function coefficients */
	printf("Filter coefficients:\n");
	for (n = 0; n < N*M+1; n++)
		printf("\tf[%d] = %.5f\te[%d] = %.5f\n", n, f[n], n, e[n]);

	
	/* clear DSPL handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
