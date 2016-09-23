
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"

#define P 	20
#define Q	11
#define	N	54
#define L	10
#define FS	26.4
#define F0	6

int main()
{

	HINSTANCE hDSPL;	/* dspl handle											*/
	
	double s[N];		/* input signal s(n) vector (FS sample-rate)			*/
	double ts[N];		/* input signal time points								*/ 
	
	double c[N*L];		/* pseudo-continuous  signal vector (FS*L sample-rate)	*/
	double tc[N*L];		/* pseudo-continuous  signal time points				*/
	
	double *y = NULL;	/* output signal y(k) vector (FS*P/Q sample-rate)		*/
	double *ty = NULL;	/* output signal time points							*/
	
	int n, K;
	
	/* Load dspl.dll */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
		
	/* FS*L kHz sample rate signal */
	for(n = 0; n < N*L; n++)
	{
		tc[n] = (double)n / (FS * L);
		c[n] = sin(M_2PI * tc[n] * F0);		
	}

	/* FS kHz sample rate signla */
	for(n = 0; n < N; n++)
	{
		ts[n] = (double)n / FS;
		s[n] = sin(M_2PI * ts[n] * F0);		
	}
	
	
	/* Farrow filter output */	
	dspl_resample_lagrange(s, N, P, Q, 0, &y, &K);
	ty = (double*)malloc(K*sizeof(double));
	
	/* Output signal time points*/
	for(n = 0; n < K; n++)
		ty[n] = (double)n * Q / (FS * P);
	
	/* save data to files */
	dspl_writetxt(tc, c, (N-1)*L, "dat/resample_lagrange_ex_fs_c.txt");
	dspl_writetxt(ts, s, N, "dat/resample_lagrange_ex_fs_s.txt");
	dspl_writetxt(ty, y, K, "dat/resample_lagrange_ex_fs_y.txt");
		
	free(y);
	free(ty);
		
	/* clear dspl handle */	
	FreeLibrary(hDSPL);
	
	return 0;
}
