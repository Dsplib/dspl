#ifndef DSPL_MAIN_H
#define DSPL_MAIN_H

#include <fftw3.h>


typedef struct
{
	fftw_complex 	*in;
	fftw_complex 	*out;
	fftw_plan 		plan;
	int n;
	int nthreads;
} fft_t;



typedef struct
{
	double *aR;
	double *aI;
	double *bR;
	double *bI;
	double *cR;
	double *cI;
	int n;
} conv_t;


typedef struct
{
	fft_t	*pfft;
	conv_t	*pconv;	
} dspl_t;



int 	dspl_fft_create(int n, fft_t *pfft);
void	dspl_fft_free(fft_t *pfft);
int  	dspl_fft_p2 (int n);

#endif