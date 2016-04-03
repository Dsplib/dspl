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


typedef struct
{
	fft_t	*pfft;
	conv_t	*pconv;	
} dspl_t;



int dspl_fft_create(int n, fft_t *pfft, int *p2);
void	dspl_fft_free(fft_t *pfft);
int  	dspl_fft_p2 (int n);

#endif