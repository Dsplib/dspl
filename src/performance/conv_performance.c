#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "dspl.h"

#define M	200000
#define N   200000

int main()
{

	double *aR = NULL;
	double *aI = NULL;
	   

	double *bR = NULL;
	double *bI = NULL;
	
	double *cR = NULL;
	double *cI = NULL;
	
	/* dspl handle */
	HINSTANCE hDSPL;
	
	clock_t t;
	
	
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
		
	aR = (double*)malloc(N*sizeof(double));	
	aI = (double*)malloc(N*sizeof(double));
	bR = (double*)malloc(M*sizeof(double));
	bI = (double*)malloc(M*sizeof(double));
	cR = (double*)malloc((M+N-1)*sizeof(double));
    cI = (double*)malloc((M+N-1)*sizeof(double));
	
	dspl_rand(aR, N);
	dspl_rand(aI, N);

	dspl_rand(bR, M);
	dspl_rand(bI, M);
	
	t = clock();
	
	
	dspl_conv_cmplx(aR, aI, N, bR, bI, M, cR, cI);
	
	t = clock()-t;
	
	printf("conv time = %f s\n", (float)(t)/(float)(CLOCKS_PER_SEC));
	
	
		
	free(aR);
	free(aI);
	free(bR);
	free(bI);
	free(cR);
	free(cI);
	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
