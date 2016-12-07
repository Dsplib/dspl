
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"

#define P 	10
#define Q	1

#define	N	8

int main()
{

	HINSTANCE hDSPL;	/* dspl handle 					*/
	
	double s[N] = {1.0, 2.0, 2.0, 1.0, -0.5, -1.0, -2.0, -0.5};		
	double *y = NULL;
	double *t = NULL;
	int n;
	
	/* Load dspl.dll */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
	
	dspl_resample_spline(s, N, P, Q, 0, &y, &n);
	t = (double*)malloc(n*sizeof(double));
	
	dspl_linspace(0, N-1, N, DSPL_SYMMETRIC, t);
	dspl_writetxt(t, s, N, "dat/resample_spline_interp_s.txt");
	
	dspl_linspace(0, N-1, n, DSPL_SYMMETRIC, t);
	dspl_writetxt(t, y, n, "dat/resample_spline_interp_y.txt");

	free(y);
	free(t);
		
	/* clear dspl handle */	
	FreeLibrary(hDSPL);
	
	return 0;
}
