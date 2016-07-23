#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define N	1024

int main()
{
	/* input signal */
	double x[N];
	
	
	double y[N];
	
	/* dspl handle */
	HINSTANCE hDSPL;
	
	int n;
	void *pdspl = NULL;
	
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
		
	dspl_randn(x, N, 0.0, 1.0);


	dspl_obj_create(&pdspl);

	dspl_hilbert(x, N, pdspl, y);
	
	dspl_writebin(x, y, N, "dat/hilbert_fft_even.bin");
	
	dspl_hilbert(x, N-1, pdspl, y);
	
	/* save result for odd length */
	dspl_writebin(x, y, N-1, "dat/hilbert_fft_odd.bin");

	dspl_obj_free(&pdspl);

	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
