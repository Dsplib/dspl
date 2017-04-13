#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define N		50
#define P		200
#define K		8
#define FS		1000.0
#define F0		200.0
#define F1		210.0

int main()
{
	/* input signals */
	double s0[P],  s1[P];
	double s0c[P*K], s1c[P*K];
	double S0C[P*K], S1C[P*K], frqC[P*K];
	double S0[P], S1[P], frq[P];
	double  t[P], tc[P*K];
	
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
	
	/* input signals s0 and s1 */
	for(n = 0; n < N; n++)
	{
		s0[n] = sin(M_2PI*(double)n*F0/FS);
		s1[n] = sin(M_2PI*(double)n*F1/FS);
	}
	
	/* time vector */ 
	dspl_linspace(0, P, P, 	 DSPL_PERIODIC,  t); 
	dspl_linspace(0, P, P*K, DSPL_SYMMETRIC, tc);
	
	for(n = 0; n < N*K; n++)
	{
		s0c[n] = sin(M_2PI*tc[n]*F0/FS);
		s1c[n] = sin(M_2PI*tc[n]*F1/FS);
	}
	
	
	/* write txt files */
	dspl_writetxt(t,  s0,  P, "dat/win_dtft_s0_time.txt");
	dspl_writetxt(t,  s1,  P, "dat/win_dtft_s1_time.txt");	
	dspl_writetxt(tc, s0c, P*K, "dat/win_dtft_s0c_time.txt");	
	dspl_writetxt(tc, s1c, P*K, "dat/win_dtft_s1c_time.txt");
	
	/* recalculate s0c and s1c signals */
	memset(s0c,0,P*K*sizeof(double));
	memset(s1c,0,P*K*sizeof(double));
	for(n = 0; n < N; n++)
	{
		s0c[n] = sin(M_2PI*(double)n*F0/FS);
		s1c[n] = sin(M_2PI*(double)n*F1/FS);
	}
	
	/* DFT of s0 signal*/
	dspl_fft_abs(s0, NULL, P, pdspl, S0, DSPL_FLAG_FFT_SHIFT);

	
	/* DFT of s1 signal*/
	dspl_fft_abs(s1, NULL, P, pdspl, S1, DSPL_FLAG_FFT_SHIFT);
	
	
	/* frequency vector */ 
	dspl_linspace(-FS/2.0, FS/2.0, P, DSPL_PERIODIC, frq);

	
	/* DFT of s0c signal*/
	dspl_fft_abs(s0c, NULL, P*K, pdspl, S0C, DSPL_FLAG_FFT_SHIFT);
	
	
	/* DFT of s1c signal*/
	dspl_fft_abs(s1c, NULL, P*K, pdspl, S1C, DSPL_FLAG_FFT_SHIFT);
	
	/* frequency vector */ 
	dspl_linspace(-FS/2.0, FS/2.0, P*K, DSPL_PERIODIC, frqC);
	
	
	
	
	dspl_writetxt(frq, S0, P, "dat/win_dtft_s0_freq.txt");
	dspl_writetxt(frq, S1, P, "dat/win_dtft_s1_freq.txt");
	
	dspl_writetxt(frqC, S0C, P*K, "dat/win_dtft_s0c_freq.txt");
	dspl_writetxt(frqC, S1C, P*K, "dat/win_dtft_s1c_freq.txt");
	
	
	/* Free DSPL object */
	dspl_obj_free(&pdspl);

	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}

