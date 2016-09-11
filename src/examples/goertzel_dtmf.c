#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


/* DFT size */
#define N 205

/* sample rate */
#define FS	8000

int main()
{

	HINSTANCE hDSPL;		/* dspl handle 				*/
	
	/* DTMF frequency vector 	*/
	double frq[8] = {697, 770, 852, 941, 1209, 1336, 1477, 1633};
	
	/* DTMF DFT indexes (N = 205)	*/
	int    ind[8] = {18,  20,  22,  24,  31,   34,   38,   42};
	
	char sym[16] = "123a456b789cs0rd";
	char fn[24];
	
	double t[N];			/* time 					*/

	double s[N];			/* DTMF signal 				*/
	double SR[8];			/* DFT image part 			*/
	double SI[8];
	double S[8];			/* Spectrum magnitude  		*/
	
	
	int n, m, k;

    /* Load dspl.dll */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	for(n = 0; n < N; n++)
		t[n] = (double)n/FS;
	
	for(k = 0; k < 4; k++)	
	{
		for(m = 0; m < 4; m++)
		{
			for(n = 0; n < N; n++)
				s[n] =	sin(M_2PI * frq[k]   * t[n]) +
						sin(M_2PI * frq[m+4] * t[n]);
			
			dspl_goertzel(s, NULL, N, ind, 8, SR, SI);
			
			for(n = 0; n < 8; n++)
				S[n] = sqrt(SR[n]*SR[n] + SI[n]*SI[n]);
			
			sprintf(fn, "dat/dtmf_sym_%c_time.txt", sym[k*4+m]);
			dspl_writetxt(t, s, 201, fn);
			
			sprintf(fn, "dat/dtmf_sym_%c_freq.txt", sym[k*4+m]);
			dspl_writetxt(frq, S, 8, fn);
		}		
	}
		
	/* clear dspl handle */	
	FreeLibrary(hDSPL);
	
	return 0;
}
