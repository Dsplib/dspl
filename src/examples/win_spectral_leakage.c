#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define N		50
#define K		300
#define FS		1000.0
#define F0		200.0
#define F1		210.0

int main()
{
	/* input signals */
	double s0[N], s1[N];
	double s0c[K], s1c[K];
	double SR[N], SI[N];
	double S0[N], S1[N];
	double frq[N], t[N], tc[K];
	
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
	dspl_linspace(0, N, N, DSPL_PERIODIC, t); 
	dspl_linspace(0, N, K, DSPL_PERIODIC, tc);
	
	for(n = 0; n < K; n++)
	{
		s0c[n] = sin(M_2PI*tc[n]*F0/FS);
		s1c[n] = sin(M_2PI*tc[n]*F1/FS);
	}
	
	/* DFT of s0 signal*/
	dspl_fft(s0, NULL, N, pdspl, SR, SI);
	
	/* Magnitude S0(k), k = 0... N-1 */
	for(n = 0; n < N; n++)
		S0[n] = sqrt(SR[n]*SR[n] + SI[n]*SI[n]);
	
	/* DFT of s1 signal*/
	dspl_fft(s1, NULL, N, pdspl, SR, SI);
	
	/* Magnitude S1(k), k = 0... N-1 */
	for(n = 0; n < N; n++)
		S1[n] = sqrt(SR[n]*SR[n] + SI[n]*SI[n]);
	
	/* frequency vector */ 
	dspl_linspace(0, FS, N, DSPL_PERIODIC, frq);

	
	/* write txt files */
	dspl_writetxt(t, s0, N, "dat/win_spectral_lekage_s0_time.txt");

	dspl_writetxt(t, s1, N, "dat/win_spectral_lekage_s1_time.txt");
	
	dspl_writetxt(tc, s0c, K, "dat/win_spectral_lekage_s0c_time.txt");
	
	dspl_writetxt(tc, s1c, K, "dat/win_spectral_lekage_s1c_time.txt");
	
	dspl_writetxt(frq, S0, N, "dat/win_spectral_lekage_s0_freq.txt");

	dspl_writetxt(frq, S1, N, "dat/win_spectral_lekage_s1_freq.txt");
	
	
	/* Free DSPL object */
	dspl_obj_free(&pdspl);

	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}

