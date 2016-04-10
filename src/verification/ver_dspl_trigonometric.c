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
	double xR[N];
	double xI[N];
	
	double cosR[N];
	double cosI[N];
	
	
	double sinR[N];
	double sinI[N];
	
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
	
	dspl_obj_create(&pdspl);
	
	dspl_linspace(0.0,   10.0, N, DSPL_PERIODIC, xR);
	dspl_linspace(10.0, -10.0, N, DSPL_PERIODIC, xI);
	
	
	dspl_cos_cmplx(xR, xI, N, cosR, cosI);
	dspl_sin_cmplx(xR, xI, N, sinR, sinI);
	
	dspl_writebin(xR, xI, N, "dat/dspl_trigonometric/trig_x.bin");
	dspl_writebin(cosR, cosI, N, "dat/dspl_trigonometric/trig_cos.bin");
	dspl_writebin(sinR, sinI, N, "dat/dspl_trigonometric/trig_sin.bin");
	
	dspl_obj_free(&pdspl);
	

	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
