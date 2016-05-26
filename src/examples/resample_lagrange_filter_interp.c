
#ifdef DOXYGEN_EN

/*!
		
*/

#elseif DOXYGEN_RU

/*! 

\example resample_lagrange_filter_interp.c  
Данная программа производит расчет импульсной характеристики фильтра интерполятора на основе 
полиномиальной Лагранжевой интерполяции.
*/

#endif



#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define P 	10
#define Q	1

#define	N	41
#define K	512 


int main()
{

	HINSTANCE hDSPL;		/* dspl handle 					*/
	
	double s[4] = {0.0, 0.0, 1.0, 0.0};
		
	double t[N];	/* time 						*/
	double h[N];	/* Filter impulse response		*/
	double w[K];	/* Normalized Angular frequency	*/
	double HR[K];	/* Filter frequency response real part	*/
	double HI[K];	/* Filter frequency response image part	*/
	double H[K];	/* Filter magnitude  			*/
	int  k;

    /* Load dspl.dll */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	dspl_linspace(0, N, N, DSPL_PERIODIC, t);
	dspl_resample_lagrange(s, 4, P, Q, 0, h, N);
	dspl_writetxt(t,h,N,"dat/resample/lagrange_filter_time.txt");
	
	dspl_linspace(0, M_PI, K, DSPL_PERIODIC, w);
	dspl_freqz(h, NULL, N-1, w, K, HR, HI);
	for(k = 0; k < K; k++)
		H[k] = 10.0*log10((HR[k]*HR[k] + HI[k]*HI[k]));
	dspl_writetxt(w,H,K,"dat/resample/lagrange_filter_freq.txt");
	
		
	/* clear dspl handle */	
	FreeLibrary(hDSPL);
	
	return 0;
}
