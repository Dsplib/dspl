/*
*   dspl_fft function example.  
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define N	1000

int main()
{
	/* input signal */
	double xR[N];
	double xI[N];
	
	/* FFT */
	double yR[N];
	double yI[N];
	
	/* IFFT */
	double zR[N];
	double zI[N];
	
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
		
	

	/* input signal s(n) = exp(2*pi*j*0.2*n) */
	for(n = 0; n < N; n++)
	{
		xR[n] =  cos(M_2PI * (double)n *0.2);
		xI[n] =  sin(M_2PI * (double)n *0.2);
	}


	dspl_obj_create(&pdspl);

	
	/*N-points FFT calculation */
	dspl_fft(xR, xI, N, pdspl,  yR, yI);

	/*N-points IFFT calculation 
	We no need to recalculate FFT object */
	dspl_ifft(yR, yI, N, pdspl, zR, zI);	

	/* save input signal, FFT and IFFT to the bin-files */
	dspl_writebin(xR, xI, N, "dat/fft_in.bin");
	dspl_writebin(yR, yI, N, "dat/fft_out.bin");
	dspl_writebin(zR, zI, N, "dat/ifft_out.bin");

	dspl_obj_free(&pdspl);

	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
