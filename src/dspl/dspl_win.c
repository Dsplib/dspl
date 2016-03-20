/*
* Copyright (c) 2015, 2016 Sergey Bakhurin
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

/*#include <stdlib.h>
#include <string.h>*/

#include <math.h>
#include "dspl.h"

void dspl_win_bartlett			(double *w, int n, int win_type);
void dspl_win_bartlett_hann		(double *w, int n, int win_type);
void dspl_win_blackman			(double *w, int n, int win_type);
void dspl_win_blackman_harris	(double *w, int n, int win_type);
void dspl_win_blackman_nuttall	(double *w, int n, int win_type);
void dspl_win_flat_top			(double *w, int n, int win_type);
void dspl_win_gaussian			(double *w, double sigma, int n, int win_type);
void dspl_win_hamming			(double *w, int n, int win_type);
void dspl_win_hann				(double *w, int n, int win_type);
void dspl_win_lanczos			(double *w, int n, int win_type);
void dspl_win_nuttall			(double *w, int n, int win_type);
void dspl_win_rect				(double *w, int n);
void dspl_win_cos				(double *w, int n, int win_type);



DSPL_API int dspl_window(double* w, int n, int win_type, double param)
{
	if(!w)
		return DSPL_ERROR_PTR;
	if(n<2)
		return DSPL_ERROR_SIZE;
	switch(win_type & DSPL_WIN_MASK){
		case  DSPL_WIN_BARTLETT			:	dspl_win_bartlett			(w, n, win_type);	break; 
		case  DSPL_WIN_BARTLETT_HANN	:	dspl_win_bartlett_hann		(w, n, win_type);	break; 
		case  DSPL_WIN_BLACKMAN			:	dspl_win_blackman			(w, n, win_type);	break; 
		case  DSPL_WIN_BLACKMAN_HARRIS	:	dspl_win_blackman_harris	(w, n, win_type);	break; 
		case  DSPL_WIN_BLACKMAN_NUTTALL	:	dspl_win_blackman_nuttall	(w, n, win_type);	break; 
		case  DSPL_WIN_FLAT_TOP			:	dspl_win_flat_top			(w, n, win_type);	break; 
		case  DSPL_WIN_GAUSSIAN			:	dspl_win_gaussian			(w, param, n, win_type);		break; 
		case  DSPL_WIN_HAMMING			:	dspl_win_hamming			(w, n, win_type);	break; 
		case  DSPL_WIN_HANN				:	dspl_win_hann				(w, n, win_type);	break; 
		case  DSPL_WIN_LANCZOS			:	dspl_win_lanczos			(w, n, win_type);	break; 
		case  DSPL_WIN_NUTTALL			:	dspl_win_nuttall			(w, n, win_type);	break; 
		case  DSPL_WIN_RECT				:	dspl_win_rect				(w, n);				break; 
		case  DSPL_WIN_COS				:	dspl_win_cos				(w, n, win_type);	break;
		default 						:	return DSPL_ERROR_WIN_TYPE;			
	}
	return DSPL_OK;
}


/* Barlett window */
void dspl_win_bartlett(double *w, int n, int win_type)
{
	double x = 0.0; 
	int i;
	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_SYMMETRIC)
		x = (double)(n-1);

	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_PERIODIC)
		x = (double)n;

	for(i = 0; i < n; i++)
	{
		w[i] = 2.0 / x * (x * 0.5-fabs((double)i - x * 0.5));
	}
}




/* Barlett - Hann window */
void dspl_win_bartlett_hann(double *w, int n, int win_type)
{
	double y;
	double x = 0.0;
	int i;
	
	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_SYMMETRIC)
		x = 1.0/(double)(n-1);

	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_PERIODIC)
		x = 1.0/(double)n;

	y = 0.0;
	for(i = 0; i<n; i++)
	{
		w[i] = 0.62 - 0.48*fabs(y-0.5)-0.38*cos(M_2PI*y);
		y += x;
	}
}



/* Blackman window */
void dspl_win_blackman(double *w, int n, int win_type)
{
	double y;
	double x = 0.0;
	int i;
	
	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_SYMMETRIC)
		x = M_2PI/(double)(n-1);

	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_PERIODIC)
		x = M_2PI/(double)n;

	y = 0.0;
	for(i = 0; i<n; i++)
	{
		w[i] = 0.42 - 0.5* cos(y)+0.08*cos(2.0*y);
		y += x;
	}
}



/* Blackman - Harris window */
void dspl_win_blackman_harris(double *w, int n, int win_type)
{
	double y;
	double x  = 0.0;
	double a0 = 0.35875;
	double a1 = 0.48829;
	double a2 = 0.14128;
	double a3 = 0.01168;
	int i;
	
	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_SYMMETRIC)
		x = M_2PI/(double)(n-1);

	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_PERIODIC)
		x = M_2PI/(double)n;

	y = 0.0;	
	for(i = 0; i<n; i++)
	{
		w[i] = a0 - a1* cos(y)+a2*cos(2.0*y)-a3*cos(3.0*y);
		y += x;
	}
}



/* Blackman - Nuttul window */
void dspl_win_blackman_nuttall(double *w, int n, int win_type)
{
	double y;
	double x  = 0.0;
	double a0 = 0.3635819;
	double a1 = 0.4891775;
	double a2 = 0.1365995;
	double a3 = 0.0106411;
	int i;
	
	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_SYMMETRIC)
		x = M_2PI/(double)(n-1);

	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_PERIODIC)
		x = M_2PI/(double)n;

	y = 0.0;	
	for(i = 0; i<n; i++)
	{
		w[i] = a0 - a1* cos(y)+a2*cos(2.0*y)-a3*cos(3.0*y);
		y += x;
	}
}




/* Flat - Top window */
void dspl_win_flat_top(double *w, int n, int win_type)
{
	double y;
	double x  = 0.0;
	double a0 = 1.0;
	double a1 = 1.93;
	double a2 = 1.29;
	double a3 = 0.388;
	double a4 = 0.032;
	int i;	
	
	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_SYMMETRIC)
		x = M_2PI/(double)(n-1);

	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_PERIODIC)
		x = M_2PI/(double)n;

	y = 0.0;		
	for(i = 0; i<n; i++)
	{
		w[i] = a0 - a1* cos(y)+a2*cos(2.0*y)-a3*cos(3.0*y)+a4*cos(4.0*y);
		y += x;
	}
}



/* Gaussian window */
void dspl_win_gaussian(double *w, double alpha, int n, int win_type)
{
	double x = 0.0; 
	double y;
	double sigma;
	int i;
	
	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_SYMMETRIC)
		x = (double)(n-1)*0.5;

	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_PERIODIC)
		x = (double)(n)*0.5;
	sigma = alpha / x;
	for(i = 0; i<n; i++)
	{
		y = ((double)i - x)*sigma;
		w[i] = exp(-0.5*y*y);
	}
}




/* Hamming window */
void dspl_win_hamming(double *w, int n, int win_type)
{
	double x = 0.0;
	double y;
	int i;
	
	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_SYMMETRIC)
		x = M_2PI/(double)(n-1);

	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_PERIODIC)
		x = M_2PI/(double)n;
	
	y = 0.0;
	for(i = 0; i < n; i++)
	{
		w[i] = 0.54-0.46*cos(y);
		y += x;
	}
}



/* Hann window */
void dspl_win_hann(double *w, int n, int win_type)
{
	double x = 0.0;
	double y;
	int i;
	
	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_SYMMETRIC)
		x = M_2PI/(double)(n-1);

	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_PERIODIC)
		x = M_2PI/(double)n;
	
	y = 0.0;
	for(i = 0; i < n; i++)
	{
		w[i] = 0.5*(1-cos(y));
		y += x;
	}
}



/* Lanczos window */
void dspl_win_lanczos(double *w, int n, int win_type)
{
	double y;
	double x = 0.0; 
	int i;
	
	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_SYMMETRIC)
		x = M_2PI/(double)(n-1);

	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_PERIODIC)
		x = M_2PI/(double)n;
	
	y = 0.0;
	for(i = 0; i < n; i++)
	{
		if((y - M_PI)==0.0) 
			w[i] = 1.0;
		else 
			w[i] = sin(y - M_PI)/(y - M_PI);
		y += x;
	}
	
}


/* Nuttal window */
void dspl_win_nuttall(double *w, int n, int win_type)
{
	double y;
	double x  = 0.0;
	double a0 = 0.355768;
	double a1 = 0.487396;
	double a2 = 0.144232;
	double a3 = 0.012604;
	int i;
	
	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_SYMMETRIC)
		x = M_2PI/(double)(n-1);

	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_PERIODIC)
		x = M_2PI/(double)n;
	
	y = 0.0;	
	for(i = 0; i < n; i++)
	{
		w[i] = a0 - a1* cos(y)+a2*cos(2.0*y)-a3*cos(3.0*y);
		y += x;
	}
}



/* Rectangle window  */ 
void dspl_win_rect(double *w, int n)
{
	int i;
	for(i = 0; i < n; i++)
		w[i] = 1.0;
}



/* Sine window */
void dspl_win_cos(double *w, int n, int win_type)
{
	double y;
	double x = 0.0;
	int i;
	
	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_SYMMETRIC)
		x = M_PI/(double)(n-1);

	if((win_type & DSPL_WIN_SYM_MASK) == DSPL_WIN_PERIODIC)
		x = M_PI/(double)n;
	
	y = 0.0;
	for(i = 0; i<n; i++)
	{
		w[i] = sin(y);
		y += x;
	}
}



















