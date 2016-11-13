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


DSPL_API int dspl_fir_lpf(int ord, double wp, int win_type, double win_param, double *h)
{
	
	double *x = NULL;
	double *w = NULL;
	int k, d, res;
	double dx, alpha;
	
	if(!h)
	{
		res =DSPL_ERROR_PTR;
		goto exit_label;	
	}	
		
	if(ord<1)
	{
		res =DSPL_ERROR_SIZE;
		goto exit_label;	
	}	
	
	if(wp<=0.0 || wp>=1)
	{
		res =DSPL_ERROR_FILTER_WP;
		goto exit_label;	
	}
	
	x = (double*)malloc((ord+1)*sizeof(double));	
	w = (double*)malloc((ord+1)*sizeof(double));
	
	res = dspl_window(w, ord+1, win_type | DSPL_WIN_SYMMETRIC, win_param);
	if(res != DSPL_OK)
		goto exit_label;
	
	d = ord >> 1;
	dx = (ord % 2) ? -0.5 : 0.0; 
	
	for(k = 0 ; k<=ord; k++)
		x[k] = dx+k-d;
	
	alpha = M_PI * wp;
	
	res = dspl_sinc(x, ord+1, alpha, h);	
	if(res != DSPL_OK)
		goto exit_label;
	
	for(k = 0; k < ord+1; k++)
		h[k]*=w[k];
	
	alpha = 0;
	for(k = 0; k < ord+1; k++)
		alpha+=h[k];
	for(k = 0; k < ord+1; k++)
		h[k] /= alpha;
	
exit_label:
	dspl_print_err(res, "dspl_fir_lpf");
	if(x)
		free(x);
	if(w)
		free(w);
	return res;
	
	
} 