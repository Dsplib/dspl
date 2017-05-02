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
	double z0[P],    z1[P];
	double z0c[P*K], z1c[P*K];
	double Z0C[P*K], Z1C[P*K], frqC[P*K];
	double Z0[P], 	 Z1[P],    frq[P];
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

	/* create DSPL object for DFT */
	dspl_obj_create(&pdspl);
	
	/* input signals z0 and z1 */
	for(n = 0; n < N; n++)
	{
		z0[n] = sin(M_2PI*(double)n*F0/FS);
		z1[n] = sin(M_2PI*(double)n*F1/FS);
	}
	
	/* time vector */ 
	dspl_linspace(0, P, P, 	 DSPL_PERIODIC,  t); 
	dspl_linspace(0, P, P*K, DSPL_SYMMETRIC, tc);
	
	for(n = 0; n < N*K; n++)
	{
		z0c[n] = sin(M_2PI*tc[n]*F0/FS);
		z1c[n] = sin(M_2PI*tc[n]*F1/FS);
	}
	
	
	/* write txt files */
	dspl_writetxt(t,  z0,  P,   "dat/win_spectral_leakage_dtft_z0_time.txt");
	dspl_writetxt(t,  z1,  P,   "dat/win_spectral_leakage_dtft_z1_time.txt");	
	dspl_writetxt(tc, z0c, P*K, "dat/win_spectral_leakage_dtft_z0c_time.txt");	
	dspl_writetxt(tc, z1c, P*K, "dat/win_spectral_leakage_dtft_z1c_time.txt");
	
	/* recalculate s0c and s1c signals */
	memset(z0c,0,P*K*sizeof(double));
	memset(z1c,0,P*K*sizeof(double));
	for(n = 0; n < N; n++)
	{
		z0c[n] = sin(M_2PI*(double)n*F0/FS);
		z1c[n] = sin(M_2PI*(double)n*F1/FS);
	}
	
	/* DFT of s0 signal*/
	dspl_fft_abs(z0, NULL, P, pdspl, Z0, DSPL_FLAG_FFT_SHIFT);

	
	/* DFT of s1 signal*/
	dspl_fft_abs(z1, NULL, P, pdspl, Z1, DSPL_FLAG_FFT_SHIFT);
	
	
	/* frequency vector */ 
	dspl_linspace(-FS/2.0, FS/2.0, P, DSPL_PERIODIC, frq);

	
	/* DFT of s0c signal*/
	dspl_fft_abs(z0c, NULL, P*K, pdspl, Z0C, DSPL_FLAG_FFT_SHIFT);
	
	
	/* DFT of s1c signal*/
	dspl_fft_abs(z1c, NULL, P*K, pdspl, Z1C, DSPL_FLAG_FFT_SHIFT);
	
	/* frequency vector */ 
	dspl_linspace(-FS/2.0, FS/2.0, P*K, DSPL_PERIODIC, frqC);
	
		
	dspl_writetxt(frq, Z0, P, "dat/win_spectral_leakage_dtft_z0_freq.txt");
	dspl_writetxt(frq, Z1, P, "dat/win_spectral_leakage_dtft_z1_freq.txt");
	
	dspl_writetxt(frqC, Z0C, P*K, "dat/win_spectral_leakage_dtft_z0c_freq.txt");
	dspl_writetxt(frqC, Z1C, P*K, "dat/win_spectral_leakage_dtft_z1c_freq.txt");
	
	
	/* Free DSPL object */
	dspl_obj_free(&pdspl);

	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}

