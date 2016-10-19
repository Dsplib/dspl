#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "dspl.h"


int main()
{
	/* input signal */
	double *xR = NULL  ;
	double *xI = NULL;
	   
	/* FFT */  
	double *yR = NULL;
	double *yI = NULL;
	
	/* dspl handle */
	HINSTANCE hDSPL;
	
	int n, N=131072, K = 512;
	
	void *pdspl = NULL;
	
	clock_t t;
	
	
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
		
	xR = (double*)malloc(N*sizeof(double));	
	xI = (double*)malloc(N*sizeof(double));
	yR = (double*)malloc(N*sizeof(double));
	yI = (double*)malloc(N*sizeof(double));

	
	/* input signal s(n) = exp(2*pi*j*0.2*n) */
	for(n = 0; n < N; n++)
	{
		xR[n] =  cos(M_2PI * (double)n *0.2);
		xI[n] =  sin(M_2PI * (double)n *0.2);
	}

	/* DSPL object create */
	dspl_obj_create(&pdspl);
	
	while(N>2)
	{		
		t = clock();
		dspl_fft(xR, xI, N, pdspl,  yR, yI);
		
		/* K times N-points FFT calculation */
		for(n = 0; n<K; n++)
			dspl_fft(xR, xI, N, pdspl,  yR, yI);
		
		t = clock()-t;
		
		/* calculate and print FFT calculation time */
		printf("N = %12d \t K = %8d \t FFT time = %f ms\n", 
				N, K, 1E3 * (float)(t)/(float)(K*CLOCKS_PER_SEC));
		
		/* increase K on 1.5 times */
		K *= 1.5;
		
		/* decrease N on 2 times */
		N /= 2; 
	}	
	
	/* Free memory */		
	dspl_obj_free(&pdspl);
		
	free(xR);
	free(xI);
	free(yR);
	free(yI);
	
	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
