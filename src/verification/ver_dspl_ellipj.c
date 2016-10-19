/*
*   dspl_fft function example.  
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"

#define N	10

int main()
{
	double k = 0.99;
	double uR[N], uI[N];
	double wR[N], wI[N];
	double tR[N], tI[N];
	int n;
	
	/* dspl handle */
	HINSTANCE hDSPL;
	
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
	
	
	
	dspl_linspace(0, 0.4, N, DSPL_PERIODIC, uR);
	dspl_linspace(0, 0.4, N, DSPL_PERIODIC, uI);
	
	
	dspl_ellip_cd_cmplx( uR, uI, N, k, tR, tI);
	dspl_ellip_acd_cmplx(tR, tI, N, k, wR, wI);
	
	for(n=0; n < N; n++)
	{
		printf("%.2d   %8.4E   %8.4E   %8.4E   %8.4E   %8.4E   %8.4E\n", n, uR[n], wR[n], uI[n], wI[n], uR[n]- wR[n], uI[n]- wI[n]);
		
	}
	


	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
