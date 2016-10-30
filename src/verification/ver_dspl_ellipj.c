/*
*   dspl_fft function example.  
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"

#define N	100

int main()
{
	double k;
	double uR[N], uI[N];
	double wR[N], wI[N];

	
	/* dspl handle */
	HINSTANCE hDSPL;
	
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
	
	
	dspl_randn(uR, N, 0, 10);
	dspl_randn(uI, N, 0, 10);
	dspl_writebin(uR, uI, N, "dat/ellip_u.bin");
	
	dspl_ellip_cd_cmplx( uR, uI, N, 0.999, wR, wI);
	dspl_writebin(wR, wI, N, "dat/ellip_cd_0.999.bin");
	
	dspl_ellip_cd_cmplx( uR, uI, N, 0.990, wR, wI);
	dspl_writebin(wR, wI, N, "dat/ellip_cd_0.990.bin");
	
	dspl_ellip_cd_cmplx( uR, uI, N, 0.900, wR, wI);
	dspl_writebin(wR, wI, N, "dat/ellip_cd_0.900.bin");
	
	dspl_ellip_cd_cmplx( uR, uI, N, 0.700, wR, wI);
	dspl_writebin(wR, wI, N, "dat/ellip_cd_0.700.bin");
	
	
	dspl_ellip_sn_cmplx( uR, uI, N, 0.999, wR, wI);
	dspl_writebin(wR, wI, N, "dat/ellip_sn_0.999.bin");
	
	dspl_ellip_sn_cmplx( uR, uI, N, 0.990, wR, wI);
	dspl_writebin(wR, wI, N, "dat/ellip_sn_0.990.bin");
	
	dspl_ellip_sn_cmplx( uR, uI, N, 0.900, wR, wI);
	dspl_writebin(wR, wI, N, "dat/ellip_sn_0.900.bin");
	
	dspl_ellip_sn_cmplx( uR, uI, N, 0.700, wR, wI);
	dspl_writebin(wR, wI, N, "dat/ellip_sn_0.700.bin");
	


	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
