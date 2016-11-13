#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define ORD_MAX 500
#define N	4096

int main()
{
	/* input signal */
	double h[ORD_MAX];
	
	
	double w[N];
	double H[N];
	double wp;
	
	int ord;
	/* dspl handle */
	HINSTANCE hDSPL;
	
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
		
	
	dspl_linspace(0, M_PI, N, DSPL_PERIODIC, w);
	
	ord = 131;
	wp = 0.125;	
	dspl_fir_lpf(ord, wp, DSPL_WIN_HAMMING, 0, h);
	dspl_freqz_resp(h, NULL, ord, w, N, H, NULL, NULL);
	dspl_writebin(w, H, N, "dat/fir_lpf_odd_freq.bin");
	dspl_writebin(h, NULL, ord+1, "dat/fir_lpf_odd_time.bin");
	
	ord = 132;
	wp = 0.125;	
	dspl_fir_lpf(ord, wp, DSPL_WIN_HAMMING, 0, h);
	dspl_freqz_resp(h, NULL, ord, w, N, H, NULL, NULL);
	dspl_writebin(w, H, N, "dat/fir_lpf_even_freq.bin");
	dspl_writebin(h, NULL, ord+1, "dat/fir_lpf_even_time.bin");


	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
