/*
*Copyright (c) 2015, 2016 Sergey Bakhurin
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
#include "dspl.h"




/*
 IIR filter output for real filter coefficients and real signals.
 Function Calculates IIR filter output. IIR filter transfer function is

         ord
         SUM b[n] * z^(-n)
         n=0
  H(z) = -------------------------------,    a[0] cannot be zero
               ord
         1.0 + SUM a[n] / a[0] * z^(-n)
               n=0
 ------------------------------------------------------------------------------------------
 Parameters:
	[in] 	double *b	-	IIR filter transfer function numerator coefficients pointer. 
							Vector size is [ord + 1 x 1]. 

	[in] 	double *a	-	IIR filter transfer function denominator coefficients pointer. 
							Vector size is [ord + 1 x 1]. This pointer can be NULL. 
							Filter becomes FIR in this case with impulse response 
							corresponds to vector b 
							 
	[in]	int		ord	-	Filter order.

	[in] 	double *x	-	Input signal pointer. Vector size is [n x 1]. 
   
	[in]	int		n	-	Input signal vector length.
                                                                       
	[out]	double *y	-	IIR filter output vector pointer. Vector size is [n x  1].	
							Memory must be allocated.
 	                                                                          
 ------------------------------------------------------------------------------------------
 Return:
	DSPL_OK 		if filter output is calculted successfuly

	DSPL_ERROR_PTR	if pointer are wrong. This situation can be if:
					b is NULL or x is NULL or y is NULL.


	DSPL_ERROR_SIZE if ord < 1 or n < 1.

	DSPL_ERROR_FILTER_A0 if a[0] is zero.
 ------------------------------------------------------------------------------------------
 Author:
	Sergey Bakhurin. 														www.dsplib.org	

*/
DSPL_API int dspl_filter_iir(double* b, double* a, int ord, double* x, int n, double* y)
{
	double* buf = NULL;
	double* an  = NULL;
	double  u;
	int 	k;
	int		m;
	int 	count;
	
	if(!b || !x || !y)
		return DSPL_ERROR_PTR;
	if(ord < 1 || n < 1)
		return DSPL_ERROR_SIZE;
	if(!a[0])
		return DSPL_ERROR_FILTER_A0;
	
	count = ord + 1;	
	buf = (double*) malloc(count*sizeof(double));
	an =  (double*) malloc(count*sizeof(double));
	
	memset(buf, 0, count*sizeof(double));
	
	if(!a)
		memset(an, 0, count*sizeof(double));
	else
		for(k = 0; k < count; k++)
			an[k] = a[k] / a[0];
	
	for(k = 0; k < n; k++)
	{
		for(m = ord; m > 0; m--)
			buf[m] = buf[m-1];
		u = 0.0;
		for(m = ord; m > 0; m--)
			u += buf[m]*an[m];
		
		buf[0] = x[k] - u;
		y[k] = 0.0;
		for(m = 0; m < count; m++)
			y[k] += buf[m] * b[m];		
	}
	free(buf);
	free(an);
	return DSPL_OK;
}


