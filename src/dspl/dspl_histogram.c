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
#include <math.h>
#include <string.h>

#include "dspl.h"




DSPL_API int dspl_histogram(double* x, int n, int nh, double *pedges, double *ph)
{
	double xmin, xmax;
	int k, ind;
	int res;
	
	if(!x || !pedges || !ph)
	{
		res = DSPL_ERROR_PTR;	
		goto exit_label;	
	}
	if(n<1 || nh<1)
	{
		res = DSPL_ERROR_SIZE;	
		goto exit_label;	
	}
	
	res = dspl_minmax(x, n, &xmin, &xmax);
	if(res != DSPL_OK)
		goto exit_label;
	
	res = dspl_linspace(xmin, xmax, nh+1, DSPL_SYMMETRIC, pedges);
	if(res != DSPL_OK)
		goto exit_label;
	
	memset(ph, 0, nh*sizeof(double));
	for(k = 0; k < n; k++)
	{
		ind = 0;
		while(ind<nh && x[k]>=pedges[ind])
			ind++;
		ph[ind-1]+=1.0;		
	}
	
	res = DSPL_OK;		
exit_label:
	dspl_print_err(res, "dspl_histogram");
	return res;

}





DSPL_API int dspl_histogram_norm(double *y, int n, int nh, double *x, double *w)
{
	double *pedges = NULL;
	int k, res;
	
	if(!y || !x || !w)
	{
		res = DSPL_ERROR_PTR;	
		goto exit_label;	
	}
	if(n<1 || nh<1)
	{
		res = DSPL_ERROR_SIZE;	
		goto exit_label;	
	}
	pedges = (double*)malloc((nh+1)*sizeof(double));
	
	res = dspl_histogram(y, n, nh, pedges, w);
	if(res != DSPL_OK)
		goto exit_label;

	for(k = 1; k < nh+1; k++)
	{
		x[k-1] = 0.5*(pedges[k] + pedges[k-1]);
		w[k-1] /= ((double)n * (pedges[k] - pedges[k-1]));
	}
	
	res = DSPL_OK;	
exit_label:	
	dspl_print_err(res, "dspl_histogram_norm");
	if(pedges)
		free(pedges);	
	return res;

}
