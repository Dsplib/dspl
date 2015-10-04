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

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dspl.h"



/*
* Analog Normalized Butterworth Low-pass Filter Calculation
* Function calculates 
* 
* 		  b[0] + b[1]*s + b[2]*s^2 + ... + b[ord]*s^ord
* H(s) = ---------------------------------------------------
* 		  a[0] + a[1]*s + a[2]*s^2 + ... + a[ord]*s^ord
* 
* of analog lowpass Batterworth filter with pass frequency wp = 1 rad/sec.  
* ------------------------------------------------------------------------------------------
* Parameters:
*	[in]	double Rp	-	Passband distortion (dB). |H(j*1)| = Rp dB for s = j*1. 
*  
*	[in]	int ord		-	Filter order. Filter numerator and denominator 
*					  
*	[out]	double* b	- 	H(s) numerator	coefficients vector b[0] + b[1]*s + b[2]*s^2... 
*							Memory must be allocated.
*
*	[out]	double* a	- 	H(s) denominator coefficients vector a[0] + a[1]*s +a[2]*s^2 ...
*							Memory must be allocated 
* 	                                                                          
* ------------------------------------------------------------------------------------------
* Return:
*	DSPL_OK 		if filter output is calculted successfuly
*
*	DSPL_ERROR_PTR	if pointer are wrong. This situation can be if:
*					b is NULL or x is NULL or y is NULL.
*
*
*	DSPL_ERROR_SIZE if ord < 1 or n < 1.
*
*	DSPL_ERROR_FILTER_A0 if a[0] is zero.
* ------------------------------------------------------------------------------------------
* Author:
*	Sergey Bakhurin. 														www.dsplib.org	
*
*/
DSPL_API int dspl_butter_norm(double Rp, int ord, double* b, double* a)
{
	double ep;
	double p[3] = {0.0, 0.0, 1.0};
	double alpha;
	double teta;
	double *acc = NULL;
	int r;
	int L;
	int n;
	int k;
	
	if(Rp < 0 || Rp == 0)
		return DSPL_ERROR_FILTER_RP;
	if(ord < 1)
		return DSPL_ERROR_FILTER_ORD;
	if(!b || !a)
		return DSPL_ERROR_PTR;
	
	acc = (double*)malloc((ord+1)*sizeof(double));

	memset(acc, 0,  (ord+1)*sizeof(double));
	memset(a,   0,  (ord+1)*sizeof(double));
	memset(b,   0,  (ord+1)*sizeof(double));


	ep = sqrt(pow(10.0, Rp*0.1) - 1.0);
	r = ord % 2;
	L = (int)((ord-r)/2);
	
	b[0] = 1.0/ep;
	
	alpha = pow(ep, -1.0/(double)ord);
	/* first pole according to filter order */
	if(r)
	{
		/* we have one real pole if filter order is odd */
		acc[0] = alpha;
		acc[1] = 1.0;
		k = 2;
	}
	else
	{
		/* all poles are TCOMPLEX if filter order is even   */
		acc[0] = 1.0;
		k = 1;
	}
	
	/* coeff calculation */
	for(n = 0; n < L; n++)
	{
		teta = M_PI*(double)(2*n + 1)/(double)(2*ord);
		p[0] = alpha * alpha;
		p[1] = 2.0 * alpha * sin(teta);
		dspl_conv(p, 3, acc, k, a);
		k+=2;
		memcpy(acc, a, k*sizeof(double));
	}

	free(acc);
	return DSPL_OK;
}




