#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define N		1000000
#define NHIST	30

int main()
{
	double *y = NULL;
		
	double w[NHIST];
	double x[NHIST];
	
	
	/* dspl handle */
	HINSTANCE hDSPL;
	
	
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
	
	y = (double*)malloc(N*sizeof(double));
	
	
	
	/* */
	dspl_rand(y, N);	
	dspl_histogram_norm(y, N, NHIST, x, w);	
	dspl_writetxt(x, w, NHIST, "dat/math_stat_histogram_rand.txt");
	
	/* gaussian random numbers m = 0, std = 1.0 */
	dspl_randn(y, N, 0.0, 1.0);
	dspl_histogram_norm(y, N, NHIST, x, w);
	dspl_writetxt(x, w, NHIST, "dat/math_stat_histogram_randn.txt");
	
	
	
	
	free(y);
	
	
	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
