#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define N		50
#define P		200


#define FS		1000.0
#define F0		200.0
#define F1		210.0



int main()
{
	/* input signals */
	double s0[P],  s1[P];
	double z0[P],  z1[P];
	double w[P],    W[P];

	double S0[P], S1[P];
	double Z0[P], Z1[P];
		
	double frq[P], t[P];
	
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
	for(n = 0; n < P; n++)
	{
		s0[n] = sin(M_2PI*(double)n*F0/FS);
		s1[n] = sin(M_2PI*(double)n*F1/FS);
	}
	
	memset(w, 0, P*sizeof(double));
	for(n = 0; n < N; n++)
		w[n] = 1.0;
	
	/* time vector */ 
	dspl_linspace(0, P, P, DSPL_PERIODIC,  t); 

	
	/* DFT of s0 signal*/
	dspl_fft_abs(s0, NULL, P, pdspl, S0, 1);
	
	/* DFT of s1 signal*/
	dspl_fft_abs(s1, NULL, P, pdspl, S1, 1);
	
	/* DFT of win signal*/
	dspl_fft_abs(w, NULL, P, pdspl, W, 1);
	
	for(n = 0; n < P; n++)
	{
		z0[n] = s0[n]*w[n];
		z1[n] = s1[n]*w[n];
	}
	
	
	/* DFT of z0 signal*/
	dspl_fft_abs(z0, NULL, P, pdspl, Z0, 1);
	
	/* DFT of z1 signal*/
	dspl_fft_abs(z1, NULL, P, pdspl, Z1, 1);
	
		/* frequency vector */ 
	dspl_linspace(-FS/2.0, FS/2.0, P, DSPL_PERIODIC, frq);
	
	/* write txt files */
	dspl_writetxt(t, s0, P, "dat/win_dtft_conv_s0_time.txt");
	dspl_writetxt(t, s1, P, "dat/win_dtft_conv_s1_time.txt");
	dspl_writetxt(t, w,  P, "dat/win_dtft_conv_w_time.txt");
	
	dspl_writetxt(frq, S0, P, "dat/win_dtft_conv_s0_freq.txt");
	dspl_writetxt(frq, S1, P, "dat/win_dtft_conv_s1_freq.txt");
	dspl_writetxt(frq, W,  P, "dat/win_dtft_conv_w_freq.txt");
	
	
	dspl_writetxt(t, z0, P, "dat/win_dtft_conv_z0_time.txt");
	dspl_writetxt(frq, Z0, P, "dat/win_dtft_conv_z0_freq.txt");
	dspl_writetxt(t, z1, P, "dat/win_dtft_conv_z1_time.txt");
	dspl_writetxt(frq, Z1, P, "dat/win_dtft_conv_z1_freq.txt");
	
	/* Free DSPL object */
	dspl_obj_free(&pdspl);

	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}

