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


#include <math.h>
#include "dspl.h"


DSPL_API int dspl_linspace(double x0, double x1, int n, int type, double* x)
{
	double dx;
	int k;
	int res;
	
	if(n < 2)
	{
		res = DSPL_ERROR_SIZE;	
		goto exit_label;	
	}
	if(!x)
	{
		res = DSPL_ERROR_PTR;	
		goto exit_label;	
	}

	if(type == DSPL_SYMMETRIC)
	{
		dx = (x1 - x0)/(double)(n-1);
		x[0] = x0;
		for(k = 1; k < n; k++)
			x[k] = x[k-1] + dx;
	}
	
	if(type == DSPL_PERIODIC)
	{
		dx = (x1 - x0)/(double)n;
		x[0] = x0;
		for(k = 1; k < n; k++)
			x[k] = x[k-1] + dx;
	}
	
	res = DSPL_OK;		
exit_label:
	dspl_print_err(res, "dspl_linspace");
	return res;
}


