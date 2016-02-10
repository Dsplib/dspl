/*
*   dspl_fft function example.  
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define N	256

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
	
	/* fft object structure */
	fft_t	fft;
	
	/* dspl handle */
	HINSTANCE hDSPL;
	
	int n;
	
	
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


	/*FFT create. We can create FFT object one time in 
	the beginning and use it for many FFT calculation*/
	memset(&fft, 0, sizeof(fft_t));
	dspl_fft_create(&fft, N);
	
	/*256-points FFT calculation */
	dspl_fft(xR, xI, N, &fft, yR, yI);

	/*256-points IFFT calculation 
	We no need to recalculate FFT object */
	dspl_ifft(yR, yI, N, &fft, zR, zI);
	
	/* Clear FFT object memory */
	dspl_fft_free(&fft);
	
	/* save input signal, FFT and IFFT to the bin-files */
	dspl_writebin(xR, xI, n, "dat/ex_dspl_fft_in.bin");
	dspl_writebin(yR, yI, n, "dat/ex_dspl_fft_out.bin");
	dspl_writebin(zR, zI, n, "dat/ex_dspl_ifft_out.bin");
		
	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
