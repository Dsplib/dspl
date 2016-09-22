
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"

#define P 	20
#define Q	11
#define	N	54
#define FS	26.4
#define F0	6

int main()
{

	HINSTANCE hDSPL;	/* dspl handle 					*/
	
	double s[N];
	double ts[N];
	
	double *y = NULL;
	double *ty = NULL;
	int n, K;
	
	/* Load dspl.dll */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
		
	for(n = 0; n < N; n++)
	{
		ts[n] = (double)n / FS;
		s[n] = sin(M_2PI * ts[n] * F0);		
	}
		
	dspl_resample_lagrange(s, N, P, Q, 0, &y, &K);
	ty = (double*)malloc(K*sizeof(double));
	
	for(n = 0; n < K; n++)
		ty[n] = (double)n * Q / (FS * P);
	
	dspl_writetxt(ts, s, N, "dat/resample_lagrange_ex_fs_s.txt");
	dspl_writetxt(ty, y, K, "dat/resample_lagrange_ex_fs_y.txt");
		
	free(y);
	free(ty);
		
	/* clear dspl handle */	
	FreeLibrary(hDSPL);
	
	return 0;
}
