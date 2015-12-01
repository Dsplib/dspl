/*
*   dspl_dft function example.  
*
*	Task:
*   Calculate 256-points DFT for complex exponent 
*	s(n) = exp(2*pi*j*0.2*n), n = 0...255
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"

#define N	256

int main()
{
	double xR[N]; /* input signal real  part vector */
	double xI[N]; /* input signal image part vector */
	double yR[N]; /* DFT real  part vector */
	double yI[N]; /* DFT image part vector */
	int n;
	int res;

	HINSTANCE hInstDLL;

	/* Load dspl.dll */
	hInstDLL = dspl_load();
	if(!hInstDLL)
	{
		printf("dspl.dll Loading Error!\n");
		return 0;
	}

	/*print current dspl.dll version */
	dspl_get_version(1);

	/* input signal s(n) = exp(2*pi*j*0.2*n) */
	for(n = 0; n < N; n++)
	{
		xR[n] = cos(M_2PI * (double)n *0.2);
		xI[n] = sin(M_2PI * (double)n *0.2);
	}

	/* DFT calculation */
	dspl_print_msg("DFT calculation", 1, 64);	
	res = dspl_dft(xR, xI, N, yR, yI);
	dspl_print_err(res, 1);

	/* save result to ex_dspl_dft.bin */
	dspl_print_msg("Save input signal vector to ex_dspl_dft.bin", 1, 64);
	res = dspl_savevar(xR, xI, N, "xin", "dat/ex_dspl_dft.bin");
	dspl_print_err(res, 1);
	
	dspl_print_msg("Save DFT vector to ex_dspl_dft.bin", 1, 64);
	res = dspl_savevar(yR, yI, N, "xout", "dat/ex_dspl_dft.bin");
	dspl_print_err(res, 1);

	FreeLibrary(hInstDLL);
	
	return 0;
}
