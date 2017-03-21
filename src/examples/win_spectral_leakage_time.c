#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define N		50
#define K		400	
#define FS		1000.0
#define F0		200.0
#define F1		210.0

int main()
{
	/* input signals */
	double t[N],  s0[N],  s1[N];
	double tc[K], s0c[K], s1c[K];
	
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
	dspl_linspace(0, N, K, DSPL_SYMMETRIC, tc);
	
	/* input signals s0 and s1 */
	for(n = 0; n < N; n++)
	{
		s0[n] = sin(M_2PI*t[n]*F0/FS);
		s1[n] = sin(M_2PI*t[n]*F1/FS);
	}	
	
	for(n = 0; n < K; n++)
	{
		s0c[n] = sin(M_2PI*tc[n]*F0/FS);
		s1c[n] = sin(M_2PI*tc[n]*F1/FS);
	}
		
	
	/* write txt files */
	dspl_writetxt(t, s0, N, "dat/win_spectral_lekage_s0_time_0n.txt");
	dspl_writetxt(t, s1, N, "dat/win_spectral_lekage_s1_time_0n.txt");	
	dspl_writetxt(tc, s0c, K, "dat/win_spectral_lekage_s0c_time_0n.txt");	
	dspl_writetxt(tc, s1c, K, "dat/win_spectral_lekage_s1c_time_0n.txt");
	
	dspl_linspace(N, 2*N, N, DSPL_PERIODIC, t); 
	dspl_linspace(N, 2*N, K, DSPL_SYMMETRIC, tc);
	
	/* write txt files */
	dspl_writetxt(t, s0, N, "dat/win_spectral_lekage_s0_time_pn.txt");
	dspl_writetxt(t, s1, N, "dat/win_spectral_lekage_s1_time_pn.txt");	
	dspl_writetxt(tc, s0c, K, "dat/win_spectral_lekage_s0c_time_pn.txt");	
	dspl_writetxt(tc, s1c, K, "dat/win_spectral_lekage_s1c_time_pn.txt");
	
	dspl_linspace(-N, 0, N, DSPL_PERIODIC, t); 
	dspl_linspace(-N, 0, K, DSPL_SYMMETRIC, tc);
	
	/* write txt files */
	dspl_writetxt(t, s0, N, "dat/win_spectral_lekage_s0_time_mn.txt");
	dspl_writetxt(t, s1, N, "dat/win_spectral_lekage_s1_time_mn.txt");	
	dspl_writetxt(tc, s0c, K, "dat/win_spectral_lekage_s0c_time_mn.txt");	
	dspl_writetxt(tc, s1c, K, "dat/win_spectral_lekage_s1c_time_mn.txt");
	
	
	/* Free DSPL object */
	dspl_obj_free(&pdspl);

	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}

