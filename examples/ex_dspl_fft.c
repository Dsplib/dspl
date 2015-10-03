/*
*   dspl_fft function example.  
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"
#include "dspl_load.h"

#define N	256

int main()
{
	double xR[N];
	double xI[N];
	double yR[N];
	double yI[N];
	int n;
	int res;
	fft_t	fft;
	HINSTANCE hInstDLL;

	hInstDLL = dspl_load();

	dspl_get_version(1);

	/* input signal s(n) = exp(2*pi*j*0.2*n) */
	for(n = 0; n < N; n++)
	{
		xR[n] = floor(1E6 * cos(M_2PI * (double)n *0.2)) * 1E-6;
		xI[n] = floor(1E6 * sin(M_2PI * (double)n *0.2)) * 1E-6;
	}


	/*	FFT create. We can create FFT object one time in 
		the begining and use it for many FFT calculation*/
	memset(&fft, 0, sizeof(fft_t));
	dspl_print_msg("Create FFT", 1, 64);
	res = dspl_fft_create(&fft, N);
	dspl_print_err(res, 1);
	
	/*  10000 times 256-points FFT calculation 
		We no need to recalculate FFT object */
	dspl_print_msg("FFT calculation", 1, 64);
	for(n = 0; n<10000; n++)
		res = dspl_fft(xR, xI, N, &fft, yR, yI);

	dspl_print_err(res, 1);
	
	/* Save input signal to ex_dspl_fft_in.txt */
	dspl_print_msg("Save result to ex_dspl_fft_in.txt", 1, 64);
	res = dspl_savetxt(xR, xI, N, "dat/ex_dspl_fft_in.txt");
    dspl_print_err(res, 1);
	
	/* Save result to ex_dspl_fft_out.txt */
	dspl_print_msg("Save result to ex_dspl_fft_out.txt", 1, 64);
	res = dspl_savetxt(yR, yI, N, "dat/ex_dspl_fft_out.txt");
    dspl_print_err(res, 1);
	
	/* Clear FFT object memory */
	dspl_fft_free(&fft);
	FreeLibrary(hInstDLL);
	
	return 0;
}
