#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define P 	1
#define Q	1
#define N	8 
#define X0	0.25


int main()
{

	HINSTANCE hDSPL;		/* dspl handle 						*/
	
	/* input signal vector s = [1 2 2 1 -0.5 -1 -2 -0.5] */
	double s[N] = {1.0, 2.0, 2.0, 1.0, -0.5, -1.0, -2.0, -0.5};
	
	/* 	vector z keeps s and 3 additional zeros 		
		z = [0 0 1 2 2 1 -0.5 -1 -2 -0.5 0]			
		zeros are necessary for n-3 to be a nonzero. */ 
	double z[N+3];	
	
	double y[N];	/*output signal delayed on X0 fractional delay 	*/
	double x;		/* x_k value */
	double delta;	/* delta_k value */
	double a[4];	/* Polynomial coeff vector */
	int k, n;		
		
    /* Load dspl.dll */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	/* z = [0 0 1 2 2 1 -0.5 -1 -2 -0.5 0]	*/
	memset(z, 0, (N+3) * sizeof(double));
	memcpy(z+2, s, N*sizeof(double));
	
	/* table header print */
	printf("\n\n -----------------------------------------------------");
	printf("-----------------------------------------------------\n");
	printf(" | k     xk    n   delta | s(n-3)  s(n-2)  s(n-1)  s(n) |");
	printf("     a0       a1       a2        a3   |   y(k)   |\n");
	printf(" -----------------------------------------------------");
	printf("-----------------------------------------------------\n");
	
	for(k = 0; k < N; k++)
	{
		x = (double)k * Q/P - X0;
		n = floor(x)+2;
		n+=2;
		delta = - floor(x) - 1.0 + x;
		
		/* polynomial coefficients calculation */
		a[0] = z[n-1];
		a[3] = (z[n] - z[n-3]) / 6.0 + 0.5 * (z[n-2] - z[n-1]);
		a[1] = 0.5*(z[n] - z[n-2]) - a[3];
		a[2] = z[n] - z[n-1] - a[3] - a[1];
		
		
		dspl_polyval(a,3,&delta, 1, y+k);
		
		printf(" | %.1d  %6.2f   %.1d  %6.2f |", k, x, n-2, -delta);
		printf(" %6.1f  %6.1f %6.1f %6.1f |", z[n-3], z[n-2], z[n-1], z[n]);
		printf(" %8.4f  %8.4f %8.4f %8.4f |", a[0], a[1], a[2], a[3]);
		printf(" %8.4f |\n", y[k]);
	}
	
	printf(" -----------------------------------------------------");
	printf("-----------------------------------------------------\n\n");	
	
	/* clear dspl handle */	
	FreeLibrary(hDSPL);
	return 0;
}
