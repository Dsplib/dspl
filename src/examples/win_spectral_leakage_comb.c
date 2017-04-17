#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define N		50
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

int dspl_writecsv(double* x, int r, int c, char* fn)
{
	int k, n;
	int res;
	FILE* pFile = NULL;
	
	if(!x)
	{
		res =DSPL_ERROR_PTR;
		goto exit_label;
	}
	if(r < 1 || c < 1)
	{
		res =DSPL_ERROR_SIZE;
		goto exit_label;
	}
	if(!fn)
	{
		res =DSPL_ERROR_FNAME;
		goto exit_label;
	}
	
	pFile = fopen(fn, "w+");
	if(pFile == NULL)
	{
		res =DSPL_ERROR_FOPEN;
		goto exit_label;
	}
	
	for(k = 0; k < c-1; k++)
		fprintf(pFile, "i%d,", k);	
	fprintf(pFile, "i%d\n", c-1);
	
	for(n = 0; n < r; n++)
	{
		for(k = 0; k < c-1; k++)
		{
			fprintf(pFile, "%+.4E,", x[k*r + n]);	
		}
		fprintf(pFile, "%+.4E\n", x[k*r+c-1]);
	}
	
	
	res = DSPL_OK;
exit_label:
	dspl_print_err(res, "dspl_writecsv");
	if(pFile)
		fclose(pFile);
	return res;	

}

int main()
{
	/* input signals */
	double t[N],  s[N],  S[N*K], SMAX[K], fmax[K];
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

	memset(SMAX,0,K*sizeof(double));
	for(ind = 1; ind < K; ind++) 
	{
		for(n = 0; n < N; n++)			
			s[n] = sin(M_2PI*t[n]*f/FS);
		dspl_fft_abs(s, NULL, N, pdspl, S+ind*N, 0);
		dspl_minmax(S+ind*N, N, NULL,  SMAX+ind);
		fmax[ind] = f;
		f+=DF;
	}
		
	dspl_writecsv(S, N, K, "dat/win_spectral_leakage_comb.csv");
	dspl_writetxt(fmax, SMAX, K, "dat/win_spectral_leakage_comb_smax.csv");
	
	/* Free DSPL object */
	dspl_obj_free(&pdspl);

	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}

                                                