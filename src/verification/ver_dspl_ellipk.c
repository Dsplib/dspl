/*
*   dspl_fft function example.  
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"

#define N	100

int main()
{
	double k[N];
	double K[N];
	
	/* dspl handle */
	HINSTANCE hDSPL;

	void *pdspl = NULL;
	
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
	
	dspl_obj_create(&pdspl);
	
	dspl_linspace(0.0, 1.0, N, DSPL_PERIODIC, k);
	
	dspl_ellipk(k,N,K);
	
	dspl_writebin(k, K, N, "dat/dspl_ellip/ellipk.bin");
	
	dspl_obj_free(&pdspl);
	

	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
