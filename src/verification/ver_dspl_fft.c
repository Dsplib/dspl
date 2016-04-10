/*
*   dspl_fft function example.  
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define N	1024

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
	
	/*256-points FFT calculation */
	dspl_fft(xR, xI, N, pdspl,  yR, yI);
		
	/*256-points IFFT calculation 
	We no need to recalculate FFT object */
	dspl_ifft(yR, yI, N, pdspl, zR, zI);	

	/* save input signal, FFT and IFFT to the bin-files */
	dspl_writebin(xR, xI, n, "dat/dspl_fft/fft_in.bin");
	dspl_writebin(yR, yI, n, "dat/dspl_fft/fft_out.bin");
	dspl_writebin(zR, zI, n, "dat/dspl_fft/ifft_out.bin");
		
	//printf("obj = %.8x\n", obj);	
	dspl_obj_free(&pdspl);
	
	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
