
#ifdef DOXYGEN_EN

/*!

		
*/

#elseif DOXYGEN_RU

/*! 
\example hilbert_fft.c  
Данная программа производит расчет блочного преобразования Гильберта и построение 
спектральной плотности мощности полученного аналитического сигнала.<BR>

В качестве входного сигнала выступает белый гауссовский процесс. <BR>

В результате выполнения программы, в директории `dat` будует создан текстовый файл
`hilbert_fft.txt` который хранит отсчеты спектральной плотности мощности полученного аналитического сигнала.<BR>

График спектральной плотности мощности, построенный по отсчетам из файла `hilbert_fft.txt`
показан на рисунке ниже.

\image html hilbert_fft.png

Можно видеть высокий уровень боковых лепестков спектральной плотности мощности в отрицательной области частот.
Данный эффект обусловлен тем, что размер блока преобразования Гильерта `NFFT` меньше размера вектора спектальной плотности 
мощности `NPSD`. <BR>

Данный пример наглядно иллюстрирует, что  используя преобразование Гильберта на осное FFT мы 
обнуляем значения фиксированных частот в отрицательной области, но никак не контроллируем поведение
спектральной плотности мощности между обнуленныыми спектральными отсчетами.<BR> 

Данный эффект носит название эффекта Гиббса и проявляется при попытке построения фильтров на основе частотной выборки.   
*/

#endif




#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


#define N		65536
#define NFFT	64
#define NPSD	2048
#define FS		1


int main()
{
	/* input signal */
	double x[N];
	double y[N];
	
	double z[NFFT];
	
	double psd[NPSD];
	double frq[NPSD]; 
	
	/* dspl handle */
	HINSTANCE hDSPL;
	
	int n;
	void *pdspl = NULL;
	
	/* load DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	/* create DSPL object for Hilbert transform */
	dspl_obj_create(&pdspl);
	
	/* generate random vector */
	dspl_randn(x, N, 0.0, 1.0);

	/* calculate the block Hilbert transform with 0.5 overlapping.	
	The signal z = x+ j*y is analytic signal*/
	memset(y, 0, N*sizeof(double));
	n = 0;
	while(n + NFFT <= N)
	{
		dspl_hilbert(x+n, NFFT, pdspl, z);
		memcpy(y+n+NFFT/4, z+NFFT/4, NFFT/2*sizeof(double));
		n+=NFFT/2;	
	}
	
	/* calculate PSD of the analytic signal*/
	dspl_pwelch(x+NFFT/4, y+NFFT/4, N-NFFT/2, 
				DSPL_WIN_HAMMING | DSPL_WIN_PERIODIC, 0, 
				NPSD, NPSD/2, pdspl, FS, psd, frq);

	/* linear PSD to dB scaling */ 
	for(n = 0; n < NPSD; n++)
		psd[n] = 10*log10(psd[n]);
	
	/* frequency vector */ 
	dspl_linspace(-FS/2.0, FS/2.0, NPSD, DSPL_PERIODIC, frq);

	/* FFT shift. Zero frequency in the center */
	dspl_fft_shift(psd, NULL, NPSD, psd, NULL);
	
	/* write PSD to the dat/hilbert_fft.txt */
	dspl_writetxt(frq,psd,NPSD,"dat/hilbert_fft.txt");

	/* Free DSPL object */
	dspl_obj_free(&pdspl);

	/* clear dspl handle */
	FreeLibrary(hDSPL);
	
	return 0;
}
