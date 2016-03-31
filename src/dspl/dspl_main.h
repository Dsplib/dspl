#ifndef DSPL_MAIN_H
#define DSPL_MAIN_H


typedef struct
{
	double *wR;
	double *wI;
	double *t0R;
	double *t0I;
	double *t1R;
	double *t1I;
	int n;
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




/* global FFT Object */
extern fft_t fftObj;


/* global Convolution Object */
extern conv_t convObj;



int  	dspl_conv_create(int n);
void 	dspl_conv_free();

int  	dspl_fft_create(int n, int *p2);
void 	dspl_fft_free();
int  	dspl_fft_p2 (int n);

#endif