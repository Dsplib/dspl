#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


/* DFT size */
#define N 30

int main()
{

	HINSTANCE hDSPL;		/* dspl handle 				*/
	void* pdspl = NULL;		/* dspl object pointer 		*/
	double sR[N];			/* input signal real part 	*/
	double sI[N];			/* input signal image part 	*/

	double SR[N];			/* DFT real part 			*/
	double SI[N];			/* DFT image part 			*/

	double S[N];			/* Spectrum magnitude  		*/
	double k[N];			/* indexes 					*/	
	
    double f0 = -20;		/* signal frequency (Hz) 	*/	
    double Fs = 120;		/* Sample rate (Hz) 		*/
	
	int n;

    /* Load dspl.dll */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	/* DSPL object create */
	dspl_obj_create(&pdspl);

	/* s(n) = exp(j*2*pi*f0*(0:N-1)/Fs) */
	for(n = 0; n < N; n++)
	{
		sR[n] = cos(M_2PI * f0 * (double)n / Fs);
		sI[n] = sin(M_2PI * f0 * (double)n / Fs);
	}

	/* DFT calculation */
	dspl_dft(sR, sI, N, SR, SI);

	/* Spectrum magnitude and indexes calculation */
	for(n = 0; n < N; n++)
	{
		S[n] = sqrt(SR[n]*SR[n] + SI[n]*SI[n]);
		k[n] = (double)n;

	}

	/* Save spectrum magnitude to dat/dft_freq_fig1.txt file */
	dspl_writetxt(k,S,N,"dat/dft_freq_fig1.txt");

	/* destroy DSPL object */
	dspl_obj_free(&pdspl);
		
		
	/* clear dspl handle */	
	FreeLibrary(hDSPL);
	
	return 0;
}
