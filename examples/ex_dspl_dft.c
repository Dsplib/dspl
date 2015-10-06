/*
*   dspl_dft function example.  
*
*	Task:
*   Calculate 256 samples of complex exponent 
*	s(n) = exp(2*pi*j*0.2*n), n = 0...255
*	and calculate DFT 
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"
#include "dspl_load.h"

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

	/* save result to ex_dspl_dft.txt */
	dspl_print_msg("Save result to ex_dspl_dft.txt", 1, 64);
	res = dspl_savetxt(yR, yI, N, "dat/ex_dspl_dft.txt");
	dspl_print_err(res, 1);

	FreeLibrary(hInstDLL);
	
	return 0;
}
