
#ifdef DOXYGEN_EN

/*!
		
*/

#elseif DOXYGEN_RU

/*! 
	\example fft_performance.c                                        
	Данная программа тестирует производительность алгоритмов быстрого преобразования Фурье. <BR>	
	DSPL использует библиотеку <a href = "http://fftw.org">FFTW</a> для расчета БПФ.<BR>
	Программа рассчитывает время одного N-точечного БПФ для N от 4 до 131072.<BR>
	Время расчета выводится на печать.<BR>
	<BR>
	Результат работы программы:
	\verbatim
	N =       131072         K =       16    FFT time = 8.125000 ms
	N =        65536         K =       24    FFT time = 3.333333 ms
	N =        32768         K =       36    FFT time = 1.666667 ms
	N =        16384         K =       54    FFT time = 0.925926 ms
	N =         8192         K =       81    FFT time = 0.370370 ms
	N =         4096         K =      121    FFT time = 0.165289 ms
	N =         2048         K =      181    FFT time = 0.165746 ms
	N =         1024         K =      271    FFT time = 0.147601 ms
	N =          512         K =      406    FFT time = 0.123153 ms
	N =          256         K =      609    FFT time = 0.098522 ms
	N =          128         K =      913    FFT time = 0.098576 ms
	N =           64         K =     1369    FFT time = 0.094960 ms
	N =           32         K =     2053    FFT time = 0.004871 ms
	N =           16         K =     3079    FFT time = 0.006496 ms
	N =            8         K =     4618    FFT time = 0.006496 ms
	N =            4         K =     6927    FFT time = 0.004331 ms
	\endverbatim
*/

#endif






#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "dspl.h"


int main()
{
	/* input signal */
	double *xR = NULL  ;
	double *xI = NULL;
	           
	/* FFT */  
	double *yR = NULL;
	double *yI = NULL;

	
	/* dspl handle */
	HINSTANCE hDSPL;
	
	int n, N=131072, K = 16;
	
	void *pdspl = NULL;
	
	clock_t t;
	
	
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
		
	xR = (double*)malloc(N*sizeof(double));	
	xI = (double*)malloc(N*sizeof(double));
	yR = (double*)malloc(N*sizeof(double));
	yI = (double*)malloc(N*sizeof(double));

	/* input signal s(n) = exp(2*pi*j*0.2*n) */
	for(n = 0; n < N; n++)
	{
		xR[n] =  cos(M_2PI * (double)n *0.2);
		xI[n] =  sin(M_2PI * (double)n *0.2);
	}

	/* DSPL object create */
	dspl_obj_create(&pdspl);
	
	while(N>2)
	{		
		t = clock();
		
		/* K times N-points FFT calculation */
		for(n = 0; n<K; n++)
			dspl_fft(xR, xI, N, pdspl,  yR, yI);
		
		t = clock()-t;
		
		/* calculate and print FFT calculation time */
		printf("N = %12d \t K = %8d \t FFT time = %f ms\n", 
				N, K, 1E3 * (float)(t)/(float)(K*CLOCKS_PER_SEC));
		
		/* increase K on 1.5 times */
		K *= 1.5;
		
		/* decrease N 2 times */
		N /= 2; 
	}	
		
	dspl_obj_free(&pdspl);
		
	free(xR);
	free(xI);
	free(yR);
	free(yI);
	
	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
