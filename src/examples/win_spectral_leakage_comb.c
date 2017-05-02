#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define N		50
#define P		10
#define K		251
#define FS		1000.0
#define DF		2.0



void dspl_write_csv_line(FILE* pFile, int *ind, double *x, int n)
{
	fprintf(pFile, "i%d,", *ind);
	for(n = 0; n < N-1; n++)
		fprintf(pFile, "%+.4E,", x[n]);
	fprintf(pFile, "%+.4E\n", x[N-1]);	
	*ind = *ind+1;
}



int main()
{
	/* input signals */
	double t[N],  s[N],  S[N*K], SMAX[K], fmax[K];
	double sdtft[N*P], SDTFT[N*K*P];
	double  f = 0.0;
		
	int n, ind;
	void *pdspl = NULL;
	FILE* pFile = NULL;
	
	
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
	dspl_linspace(0, N,  N, DSPL_PERIODIC, t); 
	dspl_linspace(0, FS, N, DSPL_PERIODIC, S); 
	dspl_linspace(0, FS, N*P, DSPL_PERIODIC, SDTFT);
	
	memset(SMAX,0,K*sizeof(double));
	memset(sdtft, 0, N*P*sizeof(double));
	for(ind = 1; ind < K; ind++) 
	{
		for(n = 0; n < N; n++)			
			s[n] = sdtft[n] = sin(M_2PI*t[n]*f/FS);
		
		dspl_fft_abs(s, NULL, N, pdspl, S+ind*N, 0);
		dspl_fft_abs(sdtft, NULL, N*P, pdspl, SDTFT+ind*N*P, 0);
		dspl_minmax(S+ind*N, N, NULL,  SMAX+ind);
		fmax[ind] = f;
		f+=DF;
	}
		
	dspl_writecsv(S, N, K, "dat/win_spectral_leakage_comb.csv");
	dspl_writecsv(SDTFT, N*P, K, "dat/win_spectral_leakage_comb_dtft.csv");
	dspl_writetxt(fmax, SMAX, K, "dat/win_spectral_leakage_comb_smax.csv");
	
	/* Free DSPL object */
	dspl_obj_free(&pdspl);

	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}

                                                