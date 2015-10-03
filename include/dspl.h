#ifndef DSPL_H
#define DSPL_H

#include <math.h>
  
/* DSPL VERSION */
#define DSPL_VERSION 0x000F090C
 
/* math const definition */
#ifndef M_PI
#define M_PI	3.1415926535897932384626433832795
#endif
#ifndef M_2PI
#define M_2PI	6.283185307179586476925286766559
#endif
 	
/* max message length */ 
#define DSPL_MSG_LENGTH			256

#define DSPL_OK					0

/* Error codes */
#define	DSPL_ERROR_FFT_SIZE		  90	
#define DSPL_ERROR_FILTER_A0	 100	 
#define DSPL_ERROR_FNAME		 200	
#define DSPL_ERROR_FOPEN		 250
#define DSPL_ERROR_PTR			1000
#define DSPL_ERROR_SIZE			4000


#define DSPL_MATRIX_REAL		0
#define DSPL_MATRIX_COMPLEX		1
#define DSPL_MATRIX_TYPE		1
#define DSPL_MAT_MAJOR_COL		0
#define DSPL_MAT_MAJOR_ROW		1


typedef struct
{
	int row;
	int col;
	int type;
	int ord;
	double *pR;
	double *pI;           
} matrix_t;


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


#ifdef DLL_EXPORT
	#define DSPL_API	__declspec(dllexport)

#ifdef __cplusplus
extern "C" {
#endif
/* Linear convolution for real vectors  (dspl_conv.c) */
DSPL_API int dspl_conv (double* a, int na, double* b,  int nb, double *c);

/* Linear convolution for complex vectors  (dspl_conv.c) */
DSPL_API int dspl_conv_cmplx	(double* aR, double* aI, int na, 
                     double* bR, double* bI, int nb, 
					 double *cR, double *cI);

/* Discrete Fourier Transform  (dspl_dft.c) */
DSPL_API int dspl_dft (double* xR, double* xI, int n, double* yR, double* yI);




/* Fast Fourier Transform  (dspl_fft.c)*/
DSPL_API int dspl_fft(double* xR, double* xI, int n, fft_t *pfft, 
											double* yR, double* yI);

/* Create Fast Fourier Transform  (dspl_fft.c)*/
DSPL_API int dspl_fft_create(fft_t *fft, int n);

/* IIR filter output for real IIR filter and real signal (dspl_filter_iir.c) */
DSPL_API int dspl_filter_iir	(double* b, double* a, int ord, double* x, int n, double* y);

/* Get DSPL version  (dspl_inout.c) */
DSPL_API int dspl_get_version (int printFlag);

/* print error code (dspl_inout.c) */
DSPL_API void dspl_print_err (int res, int printCR);

/* print message (dspl_inout.c) */
DSPL_API void dspl_print_msg (char* msg, int printTime, int msgLen);

/* save vectors to text file (dspl_inout.c) */
DSPL_API int dspl_savetxt (double* x, double *y, int n, char* fn);

#ifdef __cplusplus
}
#endif

#endif

#endif


