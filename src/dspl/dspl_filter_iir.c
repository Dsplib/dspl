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




DSPL_API int dspl_filter_iir(double* b, double* a, int ord, double* x, int n, double* y)
{
	double* buf = NULL;
	double* an  = NULL;
	double  u;
	int 	k;
	int		m;
	int 	count;
	int 	res; 
	
	if(!b || !x || !y)
	{
		res =DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(ord < 1 || n < 1)
	{
		res =DSPL_ERROR_SIZE;
		goto exit_label;	
	}
	if(a && !a[0])
	{
		res =DSPL_ERROR_FILTER_A0;
		goto exit_label;	
	}
	
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
	
	res = DSPL_OK;
exit_label:
	dspl_print_err(res, "dspl_filter_iir");
	if(buf)
		free(buf);
	if(an)
		free(an);
	return res;
}


