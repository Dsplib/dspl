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
#include "dspl.h"




DSPL_API int dspl_histogram(double* x, int n, int nh, double *pedges, double *ph)
{
	double xmin, xmax, dx;
	int k, ind;
	
	if(!x || !pedges || !ph)
		return DSPL_ERROR_PTR;
	if(n<1 || nh<1)
		return DSPL_ERROR_SIZE;
	
	dspl_minmax(x, n, &xmin, &xmax);
	dspl_linspace(xmin, xmax, nh+1, DSPL_SYMMETRIC, pedges);
	memset(ph, 0, nh*sizeof(double));
	for(k = 0; k < n; k++)
	{
		ind = 0;
		while(ind<nh && x[k]>=pedges[ind])
			ind++;
		ph[ind-1]+=1.0;		
	}
	return DSPL_OK;

}





DSPL_API int dspl_histogram_norm(double *y, int n, int nh, double *x, double *w)
{
	double *pedges = NULL;
	int k, res;
	
	if(!y || !x || !w)
		return DSPL_ERROR_PTR;
	if(n<1 || nh<1)
		return DSPL_ERROR_SIZE;
	pedges = (double*)malloc((nh+1)*sizeof(double));
	
	res = dspl_histogram(y, n, nh, pedges, w);
	if(res != DSPL_OK)
		goto error_label;

	for(k = 1; k < nh+1; k++)
	{
		x[k-1] = 0.5*(pedges[k] + pedges[k-1]);
		w[k-1] /= ((double)n * (pedges[k] - pedges[k-1]));
	}
	
	
error_label:	
	if(pedges)
		free(pedges);
	
	return res;

}
