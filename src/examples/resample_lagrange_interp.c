
#ifdef DOXYGEN_EN

/*!
		
*/

#elseif DOXYGEN_RU

/*! 

\example resample_lagrange_interp.c  
Данная программа производит интерполяцию на основе 
кубического полинома Лагранжа.
*/

#endif



#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define P 	10
#define Q	1

#define	N	20
#define K	P*N 


int main()
{

	HINSTANCE hDSPL;	/* dspl handle 					*/
	
	double s[N];		
	double ts[N];		/* time 						*/
	double y[K];		/* Normalized Angular frequency	*/
	double ty[K];		/* Filter frequency response real part	*/
	double z[K];
	double e[K];
	int  k;

    /* Load dspl.dll */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	dspl_linspace(0, N, N, DSPL_PERIODIC, ts);
	for(k = 0; k < N; k++)
		s[k] = sin(M_2PI * ts[k] * 0.31);
	dspl_linspace(0, N, K, DSPL_PERIODIC, ty);
	dspl_resample_lagrange(s, N, P, Q, 0, y, K);
	
	for(k = 0; k < K; k++)
	{
		z[k] = sin(M_2PI * ty[k]*0.31);
		e[k] = z[k] - y[k];
	}
	
	dspl_writetxt(ts,s,N,"dat/resample/lagrange_interp_s.txt");
	dspl_writetxt(ty,y,K,"dat/resample/lagrange_interp_y.txt");
	dspl_writetxt(ty,z,K,"dat/resample/lagrange_interp_z.txt");
	dspl_writetxt(ty,e,K,"dat/resample/lagrange_interp_e.txt");
		
	/* clear dspl handle */	
	FreeLibrary(hDSPL);
	
	return 0;
}
