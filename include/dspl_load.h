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


#ifndef DSPL_LOAD_H
#define DSPL_LOAD_H


/* Linear convolution for real vectors  (dspl_conv.c) */
typedef int (*p_dspl_conv) 			(double* a, int na, double* b,  int nb, double *c);

/* Linear convolution for complex vectors  (dspl_conv.c) */
typedef int (*p_dspl_conv_cmplx)	(	double* aR, double* aI, int na, 
                     					double* bR, double* bI, int nb, 
					 					double *cR, double *cI);

/* Discrete Fourier Transform  (dspl_dft.c) */
typedef int (*p_dspl_dft) 			(double* xR, double* xI, int n, double* yR, double* yI);

/* Fast Fourier Transform  (dspl_fft.c)*/
typedef int (*p_dspl_fft)			(double* xR, double* xI, int n, fft_t *pfft, 
											double* yR, double* yI);


/* Create Fast Fourier Transform  (dspl_fft.c)*/
typedef int (*p_dspl_fft_create)	(fft_t *pfft, int n);

typedef void (*p_dspl_fft_free)(fft_t *pfft);

/* IIR filter output for real IIR filter and real signal (dspl_filter_iir.c) */
typedef int (*p_dspl_filter_iir)	(double* b, double* a, int ord, double* x, int n, double* y);

/* Get DSPL version  (dspl_inout.c) */
typedef int (*p_dspl_get_version) 	(int printFlag);

/* print error code (dspl_inout.c) */
typedef void (*p_dspl_print_err) 	(int res, int printCR);

/* print message (dspl_inout.c) */
typedef void (*p_dspl_print_msg) 	(char* msg, int printTime, int msgLen);

/* save vectors to text file (dspl_inout.c) */
typedef int (*p_dspl_savetxt) 		(double* x, double *y, int n, char* fn);



extern p_dspl_conv			dspl_conv			;         	
extern p_dspl_conv_cmplx   	dspl_conv_cmplx     ;   				
extern p_dspl_dft 			dspl_dft 			; 
extern p_dspl_fft			dspl_fft		    ;
extern p_dspl_fft_create	dspl_fft_create	    ;
extern p_dspl_fft_free		dspl_fft_free    ;
extern p_dspl_filter_iir	dspl_filter_iir	    ;
extern p_dspl_get_version 	dspl_get_version 	; 
extern p_dspl_print_err		dspl_print_err	    ;
extern p_dspl_print_msg 	dspl_print_msg 	    ;
extern p_dspl_savetxt		dspl_savetxt        ;


HINSTANCE dspl_load();


#endif







		 