#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"

#define N	100

int main()
{
	double xR[N];
	double xI[N];
	
	double yR[N];
	double yI[N];
	
	/* dspl handle */
	HINSTANCE hDSPL;

	void *pdspl = NULL;
	
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
	

	/* fill x vector */
	dspl_linspace(0.0,   10.0, N, DSPL_PERIODIC, xR);
	dspl_linspace(10.0, -10.0, N, DSPL_PERIODIC, xI);
	dspl_writebin(xR, xI, N, "dat/math_basic_x.bin");
	
	dspl_asin_cmplx(xR, xI, N, yR, yI);
	dspl_writebin(yR, yI, N, "dat/math_basic_asin.bin");
	
	
	dspl_cos_cmplx(xR, xI, N, yR, yI);
	dspl_writebin(yR, yI, N, "dat/math_basic_cos.bin");

	dspl_sin_cmplx(xR, xI, N, yR, yI);
	dspl_writebin(yR, yI, N, "dat/math_basic_sin.bin");
	

	dspl_sqrt_cmplx(xR, xI, N, yR, yI);
	dspl_writebin(yR, yI, N, "dat/math_basic_sqrt.bin");

	dspl_log_cmplx(xR, xI, N, yR, yI);	                                                       
	dspl_writebin(yR, yI, N, "dat/math_basic_log.bin");
		

	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
