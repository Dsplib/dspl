
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define P 	10
#define Q	1
#define K	512
#define N	5 


int main()
{

	HINSTANCE hDSPL;		/* dspl handle 					*/
	
	double s[N] = {0.0, 0.0, 1.0, 0.0, 0.0};
		
	double *t=NULL;		/* time 						*/
	double *h=NULL;		/* Filter impulse response		*/
	double w[K];	/* Normalized Angular frequency	*/
	double HR[K];	/* Filter frequency response real part	*/
	double HI[K];	/* Filter frequency response image part	*/
	double H[K];	/* Filter magnitude  			*/
	int  k, nh;

    /* Load dspl.dll */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	dspl_resample_lagrange(s, N, P, Q, 0, &h, &nh);
	t = (double*) malloc(nh*sizeof(double));
	
	dspl_linspace(0, nh, nh, DSPL_PERIODIC, t);	
	
	dspl_writetxt(t,h,nh,"dat/resample_lagrange_filter_time.txt");
	
	dspl_linspace(0, M_PI, K, DSPL_PERIODIC, w);
	dspl_freqz(h, NULL, nh-1, w, K, HR, HI);
	for(k = 0; k < K; k++)
		H[k] = 10.0*log10((HR[k]*HR[k] + HI[k]*HI[k]));
	dspl_writetxt(w,H,K,"dat/resample_lagrange_filter_freq.txt");
	
		
	/* clear dspl handle */	
	FreeLibrary(hDSPL);
	free(h);
	free(t);
	return 0;
}
