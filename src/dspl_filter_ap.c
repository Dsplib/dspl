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
#include <math.h>
#include "dspl.h"


DSPL_API int dspl_butter_ap(double Rp, int ord, double* b, double* a)
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
		/* all poles are complex if filter order is even   */
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




DSPL_API int dspl_cheby1_ap(double Rp, int ord, double* b, double* a)
{
	double ep;
	double alpha;
	double beta; 
	double shbeta;
	double chbeta;
	double sigma;
	double omega;
	double gain;
	
	
	double p[3] = {0.0, 0.0, 1.0};
	
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
	
	beta = dspl_asinh(1.0/ep)/(double)ord;
	chbeta = dspl_cosh(beta);
	shbeta = dspl_sinh(beta);
	
	/* first pole according to filter order */
	if(r)
	{ 
		/* we have one real pole if filter order is odd */
		acc[0] = -shbeta;
		acc[1] = 1.0;
		k = 2;
		gain = shbeta;
	}
	else
	{
		/* all poles are complex if filter order is even   */
		acc[0] = 1.0;
		k = 1;
		gain = 1.0/sqrt(1.0 + ep*ep);
	}
	
	
	/* coeff calculation */
	for(n = 0; n < L; n++)
	{
		alpha = M_PI*(double)(2*n + 1)/(double)(2*ord);
		sigma = -sin(alpha)*shbeta;
		omega =  cos(alpha)*chbeta;
		
		p[0] = sigma * sigma + omega * omega;
		gain*=p[0];
		p[1] = -2.0 * sigma;
		
		dspl_conv(p, 3, acc, k, a);
		k+=2;
		memcpy(acc, a, k*sizeof(double));
	}
	b[0] = gain;
	free(acc);
	return DSPL_OK;
}



