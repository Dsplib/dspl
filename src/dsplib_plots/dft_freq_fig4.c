#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"

#define N 30

int main()
{

	HINSTANCE hDSPL;

	double sR[N];
	double sI[N];

	double SR[N];
	double SI[N];

	double S[N];
	double k[N];
	double frq[N];

	int n;	
    double f0 = -20E3;
    double Fs = 120E3;


    /* Load dspl.dll */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	for(n = 0; n < N; n++)
	{
		sR[n] = cos(M_2PI * f0 * (double)n / Fs);
		sI[n] = sin(M_2PI * f0 * (double)n / Fs);
	}


	dspl_dft(sR, sI, N, SR, SI);
	dspl_fft_shift(SR, SI, N, SR, SI);

	for(n = 0; n < N; n++)
	{
		S[n] = sqrt(SR[n]*SR[n] + SI[n]*SI[n]);
		k[n] = (double)n;
		frq[n] = -Fs*0.5 + (double)n * Fs/(double)N;
		printf("f[%.2d] = %7.3f", n, frq[n]);
		printf("S[%.2d] = %7.3f\n", n, S[n]);
	}

	dspl_writetxt(k,S,N,"dat/dft_freq_fig4.txt");


		
	FreeLibrary(hDSPL);
	
	return 0;
}
