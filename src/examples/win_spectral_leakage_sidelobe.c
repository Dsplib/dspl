#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define N		100
#define FS		1000.0
#define F0		200.0
#define F1		205.0
#define F2		300.0

int main()
{
	/* input signals */
	double t[N],   s0[N],  s1[N];
	double frq[N], S0[N],  S1[N];
	
	int n;
	void *pdspl = NULL;
	
	/* dspl handle */
	HINSTANCE hDSPL;
		
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	/* create DSPL object for Hilbert transform */
	dspl_obj_create(&pdspl);
	
	
	/* time vector */ 
	dspl_linspace(0, N, N, DSPL_PERIODIC, t); 

	
	/* input signals s0 and s1 */
	for(n = 0; n < N; n++)
	{
		s0[n] = 10.0 * sin(M_2PI*t[n]*F0/FS) + 0.2 * sin(M_2PI*t[n]*F2/FS);
		s1[n] = 10.0 * sin(M_2PI*t[n]*F1/FS) + 0.2 * sin(M_2PI*t[n]*F2/FS);
	}	
	
	/* DFT of s0 signal*/
	dspl_fft_abs(s0, NULL, N, pdspl, S0, DSPL_FLAG_LOG);
	
	/* DFT of s1 signal*/
	dspl_fft_abs(s1, NULL, N, pdspl, S1, DSPL_FLAG_LOG);
	
	/* frequency vector */ 
	dspl_linspace(0, FS, N, DSPL_PERIODIC, frq);

	/* write txt files */
	dspl_writetxt(frq, S0, N/2, "dat/win_spectral_leakage_sidelobe_s0.txt");

	dspl_writetxt(frq, S1, N/2, "dat/win_spectral_leakage_sidelobe_s1.txt");
	
	
	/* Free DSPL object */
	dspl_obj_free(&pdspl);

	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}

