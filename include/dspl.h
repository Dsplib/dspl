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
 	

                                     

#define DSPL_OK						0

/* Error codes */
#define	DSPL_ERROR_FFT_SIZE			0x00009000	
#define DSPL_ERROR_FILTER_A0		0x00010000
#define	DSPL_ERROR_FILTER_ORD		0x00012000
#define	DSPL_ERROR_FILTER_RP		0x00012500	
#define	DSPL_ERROR_FILTER_RS		0x00012550 
#define	DSPL_ERROR_FILTER_WP		0x00012560 
#define DSPL_ERROR_FNAME			0x00020000	
#define DSPL_ERROR_FOPEN			0x00025000
#define DSPL_ERROR_POLY_ORD			0x00090000
#define DSPL_ERROR_PTR				0x00100000
#define DSPL_ERROR_SIZE				0x00400000
#define DSPL_ERROR_UNWRAP			0x00450000
#define	DSPL_ERROR_WIN_TYPE			0x00500000
	
	
#define DSPL_MATRIX_REAL			0
#define DSPL_MATRIX_COMPLEX			1
#define DSPL_MATRIX_TYPE			1
#define DSPL_MAT_MAJOR_COL			0
#define DSPL_MAT_MAJOR_ROW			1
	
	
/* data */	
#define DSPL_DAT_REAL				0
#define DSPL_DAT_COMPLEX			1


/* max message length */ 
#define DSPL_MSG_LENGTH				256


#define DSPL_SYMMETRIC				0x00000000
#define DSPL_PERIODIC				0x00010000



/* window types */
#define DSPL_WIN_MASK				0x0000FFFF
#define	DSPL_WIN_BARTLETT			0x00000010
#define	DSPL_WIN_BARTLETT_HANN		0x00000020
#define	DSPL_WIN_BLACKMAN			0x00000030	
#define	DSPL_WIN_BLACKMAN_HARRIS	0x00000040
#define	DSPL_WIN_BLACKMAN_NUTTALL	0x00000050
#define	DSPL_WIN_FLAT_TOP			0x00000060		
#define	DSPL_WIN_GAUSSIAN			0x00000070
#define	DSPL_WIN_HAMMING			0x00000080
#define	DSPL_WIN_HANN				0x00000090
#define	DSPL_WIN_LANCZOS			0x00000100
#define	DSPL_WIN_NUTTALL			0x00000110	
#define	DSPL_WIN_RECT				0x00000120		
#define	DSPL_WIN_COS				0x00000130							

#define DSPL_WIN_TYPE_MASK			0x000F0000
#define DSPL_WIN_SYMMETRIC			DSPL_SYMMETRIC
#define DSPL_WIN_PERIODIC			DSPL_PERIODIC
				

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



/* Analog low-pass prototype frequency transformation to band-pass 
filter with wp0 .. wp1 pass-band   (dspl_filter_transform.c) */
DSPL_API int dspl_ap2bpass(double* b, double* a, int n, 
						   double wp0, double wp1, 
						   double* beta, double* alpha);

/* Analog low-pass prototype frequency transformation to band-stop 
filter with ws0 .. ws1 stop-band   (dspl_filter_transform.c) */
DSPL_API int dspl_ap2bstop(double* b, double* a, int n, 
						   double ws0, double ws1, 
						   double* beta, double* alpha);
						   
/* Analog low-pass prototype frequency transformation to high-pass 
filter with wp cutoff frequency   (dspl_filter_transform.c) */
DSPL_API int dspl_ap2high(double* b, double* a, int n, double wp, 
						 double* beta, double* alpha);
						 
						   
/* Analog low-pass prototype frequency transformation to low-pass 
filter with wp cutoff frequency    (dspl_filter_transform.c) */
DSPL_API int dspl_ap2low(double* b, double* a, int n, double wp, 
						 double* beta, double* alpha);
						 
						 
/* Arsine hyperbolic for real argument (dspl_math_hyperbolic.c) */
DSPL_API double dspl_asinh(double x);




/* Analog Butterworth Filter prototype (dspl_filter_ap.c) */
DSPL_API int dspl_butter_ap(double Rp, int ord, double* b, double* a);


/* Analog Chebyshev type 1 Filter prototype (dspl_filter_ap.c) */
DSPL_API int dspl_cheby1_ap(double Rp, int ord, double* b, double* a);


/* Analog Chebyshev type 2 Filter prototype (dspl_filter_ap.c) */
DSPL_API int dspl_cheby2_ap(double Rs, int ord, double *b, double *a);


/* Linear convolution for real vectors  (dspl_conv.c) */
DSPL_API int dspl_conv (double* a, int na, double* b,  int nb, double *c);


/* Rational composition  (dspl_compos.c) */
DSPL_API int dspl_compos(	double *b, double *a, int n, 
							double *c, double *d, int p, 
							double *beta, double *alpha);
							

/* Linear convolution for complex vectors  (dspl_conv.c) */
DSPL_API int dspl_conv_cmplx	(double* aR, double* aI, int na, 
                     double* bR, double* bI, int nb, 
					 double *cR, double *cI);


/* Hyperbolic cosine for real argument (dspl_math_hyperbolic.c) */
DSPL_API double dspl_cosh(double x);
					 
					 
/* Discrete Fourier Transform  (dspl_dft.c) */
DSPL_API int dspl_dft (double* xR, double* xI, int n, double* yR, double* yI);


/* Goertzel Algorithm for Discrete Fourier Transform  (dspl_goertzel.c) */
DSPL_API int dspl_goertzel(	double *xR, double *xI, int n, 
							int *ind, int k, 
							double *yR, double *yI);


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


/* DFT shift  (dspl_fft.c)*/
DSPL_API int dspl_fft_shift(double* xR, double* xI, int n, double* yR, double* yI);



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


/* fill vector x as linear from x0 to x1  (dspl_math_basic.c)*/
DSPL_API int dspl_linspace(double x0, double x1, int n, int type, double* x);


/* fill vector x in logarithmic scale from 10^x0 to 10^x1  (dspl_math_basic.c)*/
DSPL_API int dspl_logspace(double x0, double x1, int n, int type, double* x);


/* Polynomial calculation (dspl_polynom.c) */
DSPL_API int dspl_polyval(double* a, int ord, double* x, int n, double* y);



/* Complex polynom calculation (dspl_polynom.c) */
DSPL_API int dspl_polyval_cmplx(	double* aR, double* aI, int ord, 
									double* xR, double* xI, int n,
									double* yR, double* yI);

									
									
/* print error code (dspl_inout.c) */
DSPL_API void dspl_print_err (int res, int printCR);



/* print message (dspl_inout.c) */
DSPL_API void dspl_print_msg (char* msg, int printTime, int msgLen);



/* Hyperbolic sine for real argument (dspl_math_hyperbolic.c) */
DSPL_API double dspl_sinh(double x);

/* unwrap function (dspl_unwrap.c)*/
DSPL_API int dspl_unwrap(double* phi,  int n, double lev, double mar);

/* window function calculation (dspl_win.c)*/
DSPL_API int dspl_window(double* w, int n, int win_type, double param);


/* save vectors to text file (dspl_inout.c) */
DSPL_API int dspl_writebin (double* x, double *y, int n, char* fn);

/* save vectors to text file (dspl_inout.c) */
DSPL_API int dspl_writetxt (double* x, double *y, int n, char* fn);



#ifdef __cplusplus
}
#endif

#else
	
/* Analog low-pass prototype frequency transformation to band-pass 
filter with wp0 .. wp1 pass-band   (dspl_filter_transform.c) */
typedef int (*p_dspl_ap2bpass)(double* b, double* a, int n, 
						   double wp0, double wp1, 
						   double* beta, double* alpha);

/* Analog low-pass prototype frequency transformation to band-stop 
filter with ws0 .. ws1 stop-band   (dspl_filter_transform.c) */
typedef int (*p_dspl_ap2bstop)(double* b, double* a, int n, 
						   double ws0, double ws1, 
						   double* beta, double* alpha);
						   
/* Analog low-pass prototype frequency transformation to high-pass 
filter with wp cutoff frequency   (dspl_filter_transform.c) */
typedef int (*p_dspl_ap2high)(double* b, double* a, int n, double wp, 
						 double* beta, double* alpha);
						 


/* Analog low-pass prototype frequency transformation to low-pass 
filter with wp cutoff frequency   (dspl_filter_transform.c) */
typedef int (*p_dspl_ap2low)(double* b, double* a, int n, double wp, 
							 double* beta, double* alpha);
						 

/* Arsine hyperbolic for real argument (dspl_math_hyperbolic.c) */
typedef double (*p_dspl_asinh)(double x);



/* Analog  Butterworth Filter prototype (dspl_filter_ap.c) */
typedef int (*p_dspl_butter_ap)	(double Rp, int ord, double* b, double* a);


/* Analog Chebyshev type 1 Filter prototype (dspl_filter_ap.c) */
typedef int (*p_dspl_cheby1_ap) (double Rp, int ord, double* b, double* a);


/* Analog Chebyshev type 2 Filter prototype (dspl_filter_ap.c) */
typedef int (*p_dspl_cheby2_ap) (double Rp, int ord, double* b, double* a);


/* Rational composition  (dspl_compos.c) */
typedef int (*p_dspl_compos)(	double *b, double *a, int n, 
								double *c, double *d, int p, 
								double *beta, double *alpha);
							
							
							
/* Linear convolution for real vectors  (dspl_conv.c) */
typedef int (*p_dspl_conv) 			(double* a, int na, double* b,  int nb, double *c);



/* Linear convolution for complex vectors  (dspl_conv.c) */
typedef int (*p_dspl_conv_cmplx)	(	double* aR, double* aI, int na, 
                     					double* bR, double* bI, int nb, 
					 					double *cR, double *cI);

										
/* Hyperbolic cosine for real argument (dspl_math_hyperbolic.c) */
typedef double (*p_dspl_cosh)(double x);
										
										
										
/* Discrete Fourier Transform  (dspl_dft.c) */
typedef int (*p_dspl_dft) 			(double* xR, double* xI, int n, double* yR, double* yI);



/* Goertzel Algorithm for Discrete Fourier Transform  (dspl_goertzel.c) */
typedef int (*p_dspl_goertzel)(	double *xR, double *xI, int n, 
							int *ind, int k, 
							double *yR, double *yI);

							
/* Inverse Fast Fourier Transform  (dspl_fft.c)*/
typedef int (*p_dspl_ifft)			(double* xR, double* xI, int n, fft_t* pfft, 
											double* yR, double* yI);
		

		
/* Fast Fourier Transform  (dspl_fft.c)*/
typedef int (*p_dspl_fft)			(double* xR, double* xI, int n, fft_t *pfft, 
											double* yR, double* yI);


											
/* Create Fast Fourier Transform  (dspl_fft.c)*/
typedef int (*p_dspl_fft_create)	(fft_t *pfft, int n);



typedef void (*p_dspl_fft_free)(fft_t *pfft);


typedef int(*p_dspl_fft_shift)(double* xR, double* xI, int n, double* yR, double* yI);



/* IIR filter output for real IIR filter and real signal (dspl_filter_iir.c) */
typedef int (*p_dspl_filter_iir)	(double* b, double* a, int ord, double* x, int n, double* y);


/* Analog filter complex transfer function H(jw) (dspl_freqs.c) */
typedef int (*p_dspl_freqs)(double* b, double* a, int ord, 
							double* w, int n, 
							double *hR, double* hI);



/* IIR digital filter complex transfer function (dspl_freqz.c) */
typedef int (*p_dspl_freqz)(double* b, double* a, int ord, 
							double* w, int n, 
							double *hR, double* hI);


/* Get DSPL version  (dspl_inout.c) */
typedef int (*p_dspl_get_version) 	(int printFlag);


/* fill vector x as linear from x0 to x1 (dspl_math_basic.c)*/
typedef int (*p_dspl_linspace)(double x0, double x1, int n, int type, double* x);



/* fill vector x in logarithmic from 10^x0 to 10^x1 (dspl_math_basic.c) */
typedef int (*p_dspl_logspace)(double x0, double x1, int n, int type, double* x);



/* Polynom calculation (dspl_polyval.c) */
typedef int (*p_dspl_polyval)		(double* a, int ord, double* x, int n, double* y);



/* Complex polynom calculation (dspl_polyval.c) */
typedef int (*p_dspl_polyval_cmplx)	(	double* aR, double* aI, int ord, 
										double* xR, double* xI, int n,
										double* yR, double* yI);
									
										

/* print error code (dspl_inout.c) */
typedef void (*p_dspl_print_err) 	(int res, int printCR);

/* print message (dspl_inout.c) */
typedef void (*p_dspl_print_msg) 	(char* msg, int printTime, int msgLen);


/* Hyperbolic sine for real argument (dspl_math_hyperbolic.c) */
typedef double (*p_dspl_sinh)		(double x);

/* Unwrap phase response */
typedef int (*p_dspl_unwrap)(double* phi,  int n, double lev, double mar);

/* window function calculation (dspl_win.c)*/
typedef int (*p_dspl_window)		(double* w, int n, int win_type, double param);


/* save vectors to text file (dspl_inout.c) */
typedef int (*p_dspl_writebin) 		(double* x, double *y, int n, char* fn);


/* save vectors to text file (dspl_inout.c) */
typedef int (*p_dspl_writetxt) 		(double* x, double *y, int n, char* fn);




extern p_dspl_ap2bpass		dspl_ap2bpass		;
extern p_dspl_ap2bstop		dspl_ap2bstop		;
extern p_dspl_ap2high		dspl_ap2high		;
extern p_dspl_ap2low		dspl_ap2low			;
extern p_dspl_asinh			dspl_asinh			;
extern p_dspl_butter_ap		dspl_butter_ap		;
extern p_dspl_cheby1_ap		dspl_cheby1_ap		;
extern p_dspl_cheby2_ap		dspl_cheby2_ap		;
extern p_dspl_compos		dspl_compos			;
extern p_dspl_conv			dspl_conv			;         	
extern p_dspl_conv_cmplx   	dspl_conv_cmplx     ;  
extern p_dspl_cosh 			dspl_cosh 			;	
extern p_dspl_goertzel		dspl_goertzel		;			
extern p_dspl_dft 			dspl_dft 			; 
extern p_dspl_ifft			dspl_ifft		    ;
extern p_dspl_fft			dspl_fft		    ;
extern p_dspl_fft_create	dspl_fft_create	    ;
extern p_dspl_fft_free		dspl_fft_free		;
extern p_dspl_fft_shift		dspl_fft_shift		;
extern p_dspl_filter_iir	dspl_filter_iir	    ;
extern p_dspl_freqs			dspl_freqs		    ;
extern p_dspl_freqz			dspl_freqz		    ;
extern p_dspl_get_version 	dspl_get_version 	;
extern p_dspl_linspace 		dspl_linspace 		;
extern p_dspl_logspace 		dspl_logspace 		;
extern p_dspl_polyval		dspl_polyval   		;
extern p_dspl_polyval_cmplx	dspl_polyval_cmplx	;
extern p_dspl_print_err		dspl_print_err	    ;
extern p_dspl_print_msg 	dspl_print_msg 	    ;
extern p_dspl_sinh			dspl_sinh			;
extern p_dspl_unwrap		dspl_unwrap			;
extern p_dspl_window		dspl_window         ;
extern p_dspl_writebin		dspl_writebin     	;
extern p_dspl_writetxt		dspl_writetxt       ;

HINSTANCE dspl_load();



#endif /* ifdef DLL_EXPORT */

#endif


