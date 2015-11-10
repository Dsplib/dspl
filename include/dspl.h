/*
*Copyright (c) 2015 Sergey Bakhurin
* Digital Signal Processing Library [http://dsplib.org]
*
* This file is part of DSPL.
* 
* DSPL is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
*(at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU Lesser General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef DSPL_H
#define DSPL_H

#include <math.h>
  

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
#define	DSPL_ERROR_FILTER_ORD	 120
#define	DSPL_ERROR_FILTER_RP	 125	 
#define DSPL_ERROR_FNAME		 200	
#define DSPL_ERROR_FOPEN		 250
#define DSPL_ERROR_POLY_ORD		 900
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



/* Analog Normalized Butterworth Lowpass Filter (dspl_butter_norm.c) */
DSPL_API int dspl_butter_norm(double Rp, int ord, double* b, double* a);



/* Linear convolution for real vectors  (dspl_conv.c) */
DSPL_API int dspl_conv (double* a, int na, double* b,  int nb, double *c);



/* Linear convolution for complex vectors  (dspl_conv.c) */
DSPL_API int dspl_conv_cmplx	(double* aR, double* aI, int na, 
                     double* bR, double* bI, int nb, 
					 double *cR, double *cI);

					 
					 
/* Discrete Fourier Transform  (dspl_dft.c) */
DSPL_API int dspl_dft (double* xR, double* xI, int n, double* yR, double* yI);

/* Inverse Fast Fourier Transform  (dspl_fft.c)*/
DSPL_API int dspl_ifft(double* xR, double* xI, int n, fft_t* pfft, 
											double* yR, double* yI);
											
/* Fast Fourier Transform  (dspl_fft.c)*/
DSPL_API int dspl_fft(	double* xR, double* xI, int n, fft_t *pfft, 
						double* yR, double* yI);

						
						
/* Create Fast Fourier Transform  (dspl_fft.c)*/
DSPL_API int dspl_fft_create(fft_t *pfft, int n);



/* Create Fast Fourier Transform  (dspl_fft.c)*/
DSPL_API void dspl_fft_free(fft_t *pfft);



/* IIR filter output for real IIR filter and real signal (dspl_filter_iir.c) */
DSPL_API int dspl_filter_iir	(double* b, double* a, int ord, double* x, int n, double* y);


/* Analog filter complex transfer function H(jw) (dspl_freqs.c) */
DSPL_API int dspl_freqs(double* b, double* a, int ord, 
						double* w, int n, 
						double *hR, double* hI);



/* IIR digital filter complex transfer function (dspl_freqz.c) */
DSPL_API int dspl_freqz(double* b, double* a, int ord, 
						double* w, int n, 
						double *hR, double* hI);



/* Get DSPL version  (dspl_inout.c) */
DSPL_API int dspl_get_version (int printFlag);



/* Polynom calculation (dspl_polynom.c) */
DSPL_API int dspl_polyval(double* a, int ord, double* x, int n, double* y);



/* Complex polynom calculation (dspl_polynom.c) */
DSPL_API int dspl_polyval_cmplx(	double* aR, double* aI, int ord, 
									double* xR, double* xI, int n,
									double* yR, double* yI);

									
									
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


