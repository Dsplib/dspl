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
#define DSPL_ERROR_ELLIP_K				0x00008000
//#define	DSPL_ERROR_FFT_NTHREADS		0x00008800	
#define	DSPL_ERROR_FFT_SIZE				0x00009000	
#define DSPL_ERROR_FILTER_A0			0x00010000
#define	DSPL_ERROR_FILTER_ORD			0x00012000
#define	DSPL_ERROR_FILTER_RP			0x00012500	
#define	DSPL_ERROR_FILTER_RS			0x00012550 
#define	DSPL_ERROR_FILTER_WP			0x00012560 
#define DSPL_ERROR_FNAME				0x00020000	
#define DSPL_ERROR_FOPEN				0x00025000
#define DSPL_ERROR_FS					0x00026000
#define DSPL_ERROR_OVERLAP				0x00070000
#define DSPL_ERROR_POLY_ORD				0x00090000
#define DSPL_ERROR_PTR					0x00100000
#define DSPL_ERROR_RAND_SIGMA			0x00110000
#define DSPL_ERROR_RESAMPLE_FRAC_DELAY	0x00120000
#define	DSPL_ERROR_RESAMPLE_RATIO		0x00102100
#define	DSPL_ERROR_RESAMPLE_SIZE		0x00102200
#define DSPL_ERROR_SIZE					0x00400000
#define DSPL_ERROR_UNWRAP				0x00450000
#define	DSPL_ERROR_WIN_TYPE				0x00500000
	
	
/* data */	
#define DSPL_DAT_REAL				0
#define DSPL_DAT_COMPLEX			1


/* max message length */ 
#define DSPL_MSG_LENGTH				256


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

#define DSPL_WIN_SYM_MASK			0x000F0000
#define DSPL_SYMMETRIC				0x00000000
#define DSPL_PERIODIC				0x00010000
#define DSPL_WIN_SYMMETRIC			DSPL_SYMMETRIC
#define DSPL_WIN_PERIODIC			DSPL_PERIODIC
				

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

/* Cosine for complex argument (dspl_math_basic.c) */					 
DSPL_API int dspl_cos_cmplx(double *xR, double *xI, int n, double *yR, double *yI);					 
					 
/* Hyperbolic cosine for real argument (dspl_math_hyperbolic.c) */
DSPL_API double dspl_cosh(double x);					 
					 
/* Discrete Fourier Transform  (dspl_dft.c) */
DSPL_API int dspl_dft (double* xR, double* xI, int n, double* yR, double* yI);

/* elliptic CD function (dspl_math_ellip.c)*/
DSPL_API int dspl_ellip_cd_cmplx(double *uR, double *uI, int nu, 
								 double k, double *cdR, double *cdI);

/* elliptic SN function (dspl_math_ellip.c)*/
DSPL_API int dspl_ellip_sn_cmplx(double *uR, double *uI, int nu, 
								 double k, double *snR, double *snI);

/* Complete elliptic integral first kind (dspl_math_ellip.c)*/
DSPL_API int dspl_ellipk(double *pk, int k, double *pK);
		
/* Fast Fourier Transform  (dspl_fft.c)*/
DSPL_API int dspl_fft(	double* xR, double* xI, int n, void* pdspl, double* yR, double* yI);

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
                                                
/* IIR digital filter frequency_response (dspl_freqz.c) */
DSPL_API int dspl_freqz_resp(double* b, double* a, int ord, 
							 double* w, int n, 
							 double *h, double* phi, double* gd);


/* Get DSPL version  (dspl.c) */
DSPL_API int dspl_get_version (int printFlag);

/* Goertzel Algorithm for Discrete Fourier Transform  (dspl_goertzel.c) */
DSPL_API int dspl_goertzel(	double *xR, double *xI, int n, 
							int *ind, int k, 
							double *yR, double *yI);
							
/* Analytic signal calculation  (dspl_hilbert.c) */
DSPL_API int dspl_hilbert(double* x, int n, void* pdspl, double* y);							

/* Histogram calculation  (dspl_histogram.c) */
DSPL_API int dspl_histogram(double* x, int n, int nh, double *pedges, double *ph);

/* Normalized histogram calculation  (dspl_histogram.c) */
DSPL_API int dspl_histogram_norm(double *y, int n, int nh, double *x, double *w);
							
/* Inverse Fast Fourier Transform  (dspl_fft.c)*/
DSPL_API int dspl_ifft(double* xR, double* xI, int n, void* pdspl, double* yR, double* yI);

/* fill vector x as linear from x0 to x1  (dspl_math_basic.c)*/
DSPL_API int dspl_linspace(double x0, double x1, int n, int type, double* x);

/* Complex logarithm   (dspl_math_basic.c)*/
DSPL_API int dspl_log_cmplx(double *xR, double *xI, int n, double *yR, double *yI);

/* fill vector x in logarithmic scale from 10^x0 to 10^x1  (dspl_math_basic.c)*/
DSPL_API int dspl_logspace(double x0, double x1, int n, int type, double* x);

/* min and max value calculation  (dspl_math_stat.c)*/
DSPL_API int dspl_minmax(double* x, int n, double *xmin, double *xmax);

/* create DSPL object */
DSPL_API int dspl_obj_create(void **obj);

/*delete DSPL object */
DSPL_API int dspl_obj_free(void **obj);

/* Polynomial calculation (dspl_polynom.c) */
DSPL_API int dspl_polyval(double* a, int ord, double* x, int n, double* y);

/* Complex polynom calculation (dspl_polynom.c) */
DSPL_API int dspl_polyval_cmplx(	double* aR, double* aI, int ord, 
									double* xR, double* xI, int n,
									double* yR, double* yI);									
									
/* print error code (dspl_inout.c) */
DSPL_API void dspl_print_err (int res, char* funcName);

/* print message (dspl_inout.c) */
DSPL_API void dspl_print_msg (char* msg, int printTime, int msgLen);

/* PSD estimation by using Welch method  (dspl_pwelch.c) */
DSPL_API int dspl_pwelch(double *xR, double *xI, int n, 
						int win_type, double win_param, 
						int npsd, int noverlap, void *pdspl, 
						double fs, double *ppsd, double *pfrq);						

/* uniform random numbers generation (dspl_rand_gen.c) */
DSPL_API int dspl_rand(double* x, int n);

/* Gaussian random numbers generation (dspl_rand_gen.c) */
DSPL_API int dspl_randn(double* x, int n, double mu, double sigma);

/* resampling by using Farrow structure (dspl_resample.c) */
DSPL_API int dspl_resample_lagrange(double *x, int n, int p, int q, 
									double frd, double **y, int *ny);

/* Sine for complex argument (dspl_math_basic.c) */					 
DSPL_API int dspl_sin_cmplx(double *xR, double *xI, int n, double *yR, double *yI);

/* Hyperbolic sine for real argument (dspl_math_hyperbolic.c) */
DSPL_API double dspl_sinh(double x);

/* complex square root (dspl_math_basic.c) */
DSPL_API int dspl_sqrt_cmplx(double *xR, double *xI, int n, double * yR, double * yI);

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

/* Cosine for complex argument (dspl_math_basic.c) */					 
typedef int (*p_dspl_cos_cmplx)(double *xR, double *xI, int n, double *yR, double *yI); 	
									
/* Hyperbolic cosine for real argument (dspl_math_hyperbolic.c) */
typedef double (*p_dspl_cosh)(double x);
										
/* Discrete Fourier Transform  (dspl_dft.c) */
typedef int (*p_dspl_dft) 			(double* xR, double* xI, int n, double* yR, double* yI);

/* Elliptic CD function (dspl_math_ellip.c)*/
typedef int (*p_dspl_ellip_cd_cmplx)(double *uR, double *uI, int nu, double k, double *cdR, double *cdI);

/* Elliptic SN function (dspl_math_ellip.c)*/
typedef int (*p_dspl_ellip_sn_cmplx)(double *uR, double *uI, int nu, double k, double *snR, double *snI);

/* Complete elliptic integral first kind (dspl_math_ellip.c)*/
typedef int (*p_dspl_ellipk)(double *pk, int k, double *pK);
		
/* Fast Fourier Transform  (dspl_fft.c)*/
typedef int (*p_dspl_fft)			(double* xR, double* xI, int n, void* pdspl, double* yR, double* yI);

/* DFT shift  (dspl_fft.c)*/
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

/* IIR digital filter frequency_response (dspl_freqz.c) */
typedef int (*p_dspl_freqz_resp)(double* b, double* a, int ord, 
							 double* w, int n, 
							 double *h, double* phi, double* gd); 

/* Get DSPL version  (dspl_inout.c) */
typedef int (*p_dspl_get_version) 	(int printFlag);

/* Goertzel Algorithm for Discrete Fourier Transform  (dspl_goertzel.c) */
typedef int (*p_dspl_goertzel)(	double *xR, double *xI, int n, 
							int *ind, int k, 
							double *yR, double *yI);

/* Analytic signal calculation  (dspl_hilbert.c) */
typedef int (*p_dspl_hilbert)(double* x, int n, void* pdspl, double* y);	

/* Histogram calculation  (dspl_histogram.c) */
typedef int (*p_dspl_histogram)(double* x, int n, int nh, double *pedges, double *ph);

/* Normalized histogram calculation  (dspl_histogram.c) */
typedef int (*p_dspl_histogram_norm)(double *y, int n, int nh, double *x, double *w);
							
/* Inverse Fast Fourier Transform  (dspl_fft.c)*/
typedef int (*p_dspl_ifft) (double* xR, double* xI, int n, void* pdspl, double* yR, double* yI);

/* fill vector x as linear from x0 to x1 (dspl_linspace.c)*/
typedef int (*p_dspl_linspace)(double x0, double x1, int n, int type, double* x);

/* complex logarithm function (dspl_math_basic.c)*/
typedef int (*p_dspl_log_cmplx)(double *xR, double *xI, int n, double *yR, double *yI);

/* fill vector x in logarithmic from 10^x0 to 10^x1 (dspl_logspace.c) */
typedef int (*p_dspl_logspace)(double x0, double x1, int n, int type, double* x);

/* min and max value calculation  (dspl_math_stat.c)*/
typedef int (*p_dspl_minmax)(double* x, int n, double *xmin, double *xmax);

/* create DSPL object */
typedef int (*p_dspl_obj_create)(void **obj);

/* free DSPL object */
typedef int (*p_dspl_obj_free)(void **obj);

/* Polynomial calculation (dspl_polyval.c) */
typedef int (*p_dspl_polyval)		(double* a, int ord, double* x, int n, double* y);

/* Complex polynom calculation (dspl_polyval.c) */
typedef int (*p_dspl_polyval_cmplx)	(	double* aR, double* aI, int ord, 
										double* xR, double* xI, int n,
										double* yR, double* yI);

/* print error code (dspl_inout.c) */
typedef void (*p_dspl_print_err) 	(int res, char* funcName);

/* print message (dspl_inout.c) */
typedef void (*p_dspl_print_msg) 	(char* msg, int printTime, int msgLen);

/* PSD estimation by using Welch method  (dspl_pwelch.c) */
typedef int (*p_dspl_pwelch)(double *xR, double *xI, int n, 
						int win_type, double win_param, 
						int npsd, int noverlap, void *pdspl, 
						double fs, double *ppsd, double *pfrq);
						
/* uniform random numbers generation (dspl_rand_gen.c) */
typedef int (*p_dspl_rand)(double* x, int n);

/* Gaussian random numbers generation (dspl_rand_gen.c) */
typedef int (*p_dspl_randn)(double* x, int n, double mu, double sigma);

/* resampling by using Farrow structure (dspl_resample.c) */
typedef int (*p_dspl_resample_lagrange)(double *x, int n, int p, int q, 
										double frd, double **y, int *ny);

/* Cosine for complex argument (dspl_math_basic.c) */					 
typedef int (*p_dspl_sin_cmplx)(double *xR, double *xI, int n, double *yR, double *yI); 	

/* Hyperbolic sine for real argument (dspl_math_hyperbolic.c) */
typedef double (*p_dspl_sinh)		(double x);

/* Complex square root (dspl_math_basic.c) */
typedef int (*p_dspl_sqrt_cmplx)(double *xR, double *xI, int n, double * yR, double * yI);

/* Unwrap phase response */
typedef int (*p_dspl_unwrap)(double* phi,  int n, double lev, double mar);

/* window function calculation (dspl_win.c)*/
typedef int (*p_dspl_window)		(double* w, int n, int win_type, double param);

/* save vectors to a binary file (dspl_inout.c) */
typedef int (*p_dspl_writebin) 		(double* x, double *y, int n, char* fn);

/* save vectors to text file (dspl_inout.c) */
typedef int (*p_dspl_writetxt) 		(double* x, double *y, int n, char* fn);


extern p_dspl_ap2bpass					dspl_ap2bpass			;	/* ru, en */
extern p_dspl_ap2bstop					dspl_ap2bstop			;	/* ru, en */
extern p_dspl_ap2high					dspl_ap2high			;	/* ru, en */
extern p_dspl_ap2low					dspl_ap2low				;   /* ru, en */
extern p_dspl_asinh						dspl_asinh				;	/* ru, en */
extern p_dspl_butter_ap					dspl_butter_ap			;	/* ru, en */
extern p_dspl_cheby1_ap					dspl_cheby1_ap			;   /* ru, en */
extern p_dspl_cheby2_ap					dspl_cheby2_ap			;   /* ru, en */
extern p_dspl_compos					dspl_compos				;	/* --, -- */
extern p_dspl_conv						dspl_conv				;   /* ru, en */      	
extern p_dspl_conv_cmplx   				dspl_conv_cmplx     	;   /* ru, en */
extern p_dspl_cos_cmplx					dspl_cos_cmplx			;	/* ru, en */
extern p_dspl_cosh 						dspl_cosh 				;   /* ru, en */			
extern p_dspl_dft 						dspl_dft 				;   /* ru, en */ 
extern p_dspl_ellip_cd_cmplx			dspl_ellip_cd_cmplx		;   /* --, -- */
extern p_dspl_ellip_sn_cmplx 			dspl_ellip_sn_cmplx		;	/* --, -- */
extern p_dspl_ellipk					dspl_ellipk				;	/* ru, -- */
extern p_dspl_fft						dspl_fft		    	;   /* ru, en */ 
extern p_dspl_fft_shift					dspl_fft_shift			;	/* ru, -- */
extern p_dspl_filter_iir				dspl_filter_iir	    	;	/* ru, en */
extern p_dspl_freqs						dspl_freqs		    	;	/* ru, en */
extern p_dspl_freqz						dspl_freqz		    	;	/* ru, en */
extern p_dspl_get_version 				dspl_get_version 		;	/* ru, en */
extern p_dspl_freqz_resp				dspl_freqz_resp			;
extern p_dspl_goertzel					dspl_goertzel			;	/* ru, en */
extern p_dspl_hilbert					dspl_hilbert			;	/* ru, en */
extern p_dspl_histogram					dspl_histogram			;	/* ru, -- */
extern p_dspl_histogram_norm			dspl_histogram_norm		;	/* ru, -- */
extern p_dspl_ifft						dspl_ifft		    	;	/* ru, en */
extern p_dspl_log_cmplx					dspl_log_cmplx			;	/* ru, en */
extern p_dspl_linspace 					dspl_linspace 			;	/* ru, en */
extern p_dspl_logspace 					dspl_logspace 			;	/* ru, en */
extern p_dspl_minmax					dspl_minmax				;	/* ru, -- */
extern p_dspl_obj_create				dspl_obj_create			;	/* ru, en */ 
extern p_dspl_obj_free					dspl_obj_free			;	/* ru, en */ 
extern p_dspl_polyval					dspl_polyval   			;	/* ru, en */
extern p_dspl_polyval_cmplx				dspl_polyval_cmplx		;	/* ru, en */
extern p_dspl_print_err					dspl_print_err	    	;	/* --, -- */
extern p_dspl_print_msg 				dspl_print_msg 	    	;	/* --, -- */ 
extern p_dspl_pwelch					dspl_pwelch				;	/* ru, en */
extern p_dspl_rand						dspl_rand				;	/* ru, en */ 
extern p_dspl_randn						dspl_randn				;	/* --, -- */ 
extern p_dspl_resample_lagrange			dspl_resample_lagrange	;	/* ru, -- */	
extern p_dspl_sin_cmplx					dspl_sin_cmplx			;	/* ru, en */
extern p_dspl_sinh						dspl_sinh				;	/* ru, en */
extern p_dspl_sqrt_cmplx				dspl_sqrt_cmplx			;	/* ru, en */
extern p_dspl_unwrap					dspl_unwrap				;	/* ru, en */
extern p_dspl_window					dspl_window         	;	/* ru, en */
extern p_dspl_writebin					dspl_writebin     		;	/* ru, en */
extern p_dspl_writetxt					dspl_writetxt       	;	/* ru, en */

HINSTANCE dspl_load();

#endif /* ifdef DLL_EXPORT */

#endif


