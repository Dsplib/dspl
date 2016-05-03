
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
	N =       131072         K =      512    FFT time = 4.335938 ms
	N =        65536         K =      768    FFT time = 1.757813 ms
	N =        32768         K =     1152    FFT time = 0.668403 ms
	N =        16384         K =     1728    FFT time = 0.347222 ms
	N =         8192         K =     2592    FFT time = 0.189043 ms
	N =         4096         K =     3888    FFT time = 0.123971 ms
	N =         2048         K =     5832    FFT time = 0.089163 ms
	N =         1024         K =     8748    FFT time = 0.074303 ms
	N =          512         K =    13122    FFT time = 0.061728 ms
	N =          256         K =    19683    FFT time = 0.049281 ms
	N =          128         K =    29524    FFT time = 0.044709 ms
	N =           64         K =    44286    FFT time = 0.044303 ms
	N =           32         K =    66429    FFT time = 0.000151 ms
	N =           16         K =    99643    FFT time = 0.000100 ms
	N =            8         K =   149464    FFT time = 0.000067 ms
	N =            4         K =   224196    FFT time = 0.000045 ms
	\endverbatim	
	<BR>
	<BR>
	Для сравнения производительности с функциями FFT входящих в состав пакетов
	GNU Octave и MATLAB можно использовать следующий скрипт:
	<BR>
	\verbatim
	clear all; close all;        

	N = 131072;
	K = 512;

	n = 0:N-1;
	x = exp(2i*pi * n *0.2);


	while(N>2)
		t = tic;
		for(k = 1:K)
			y = fft(x(1:N));
			
		end
		t = toc(t);
		
		fprintf("N = %12d, K = %8d, OCTAVE FFT time %.7f ms\n",N,K,1000*t/K);
		N = N/2;
		K = floor(K*1.5);
	end
	\endverbatim
	<BR>
	Данный скрипт также произведет замер времени выполнения FFT и выведет результат на печать.
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
	
	int n, N=131072, K = 512;
	
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
		dspl_fft(xR, xI, N, pdspl,  yR, yI);
		
		/* K times N-points FFT calculation */
		for(n = 0; n<K; n++)
			dspl_fft(xR, xI, N, pdspl,  yR, yI);
		
		t = clock()-t;
		
		/* calculate and print FFT calculation time */
		printf("N = %12d \t K = %8d \t FFT time = %f ms\n", 
				N, K, 1E3 * (float)(t)/(float)(K*CLOCKS_PER_SEC));
		
		/* increase K on 1.5 times */
		K *= 1.5;
		
		/* decrease N on 2 times */
		N /= 2; 
	}	
	
	/* Free memory */		
	dspl_obj_free(&pdspl);
		
	free(xR);
	free(xI);
	free(yR);
	free(yI);
	
	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
