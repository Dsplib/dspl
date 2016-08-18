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




/* Analog low-pass prototype frequency transformation to band-pass 
filter with wp0 .. wp1 pass-band   (dspl_filter_transform.c) */
DSPL_API int dspl_ap2bpass(double* b, double* a, int n, 
						   double wp0, double wp1, 
						   double* beta, double* alpha)
{
	double p[3] = {0.0, 0.0, 1.0};
	double q[3] = {0.0, 0.0, 0.0};
	int res;
	
	if(!b || !a || !beta || !alpha)
	{
		res =DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(n < 0)
	{
		res =DSPL_ERROR_FILTER_ORD;
		goto exit_label;	
	}
	if(wp0<=0.0 || wp1<wp0)
	{
		res =DSPL_ERROR_FILTER_WP;
		goto exit_label;	
	}
		
	p[0] = wp0 * wp1;
	q[1] = wp1 - wp0;
	res = dspl_compos(b, a, n, p, q, 2, beta, alpha);

	
exit_label:
	dspl_print_err(res, "dspl_ap2bpass");
	return res;
}





/* Analog low-pass prototype frequency transformation to band-stop 
filter with ws0 .. ws1 stop-band   (dspl_filter_transform.c) */
DSPL_API int dspl_ap2bstop(double* b, double* a, int n, 
						   double ws0, double ws1, 
						   double* beta, double* alpha)
{
	double p[3] = {0.0, 0.0, 0.0};
	double q[3] = {0.0, 0.0, 1.0};
	int res;
	
	if(!b || !a || !beta || !alpha)
	{
		res =DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(n < 0)
	{
		res =DSPL_ERROR_FILTER_ORD;
		goto exit_label;	
	}
	if(ws0<=0.0 || ws1<ws0)
	{
		res =DSPL_ERROR_FILTER_WP;
		goto exit_label;	
	}
		
	q[0] = ws0 * ws1;
	p[1] = ws1 - ws0;
	res =  dspl_compos(b, a, n, p, q, 2, beta, alpha);
	
exit_label:
	dspl_print_err(res, "dspl_ap2bstop");
	return res;
}




/* Analog low-pass prototype frequency transformation to high-pass 
filter with wp cutoff frequency   (dspl_filter_transform.c) */
DSPL_API int dspl_ap2high(double* b, double* a, int n, double wp, 
						 double* beta, double* alpha)
{
	double p[2] = {0.0, 0.0};
	double q[2] = {0.0, 1.0};
	int res;
	
	if(!b || !a || !beta || !alpha)
	{
		res = DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(n < 0)
	{
		res = DSPL_ERROR_FILTER_ORD;
		goto exit_label;	
	}
	if(wp<=0.0)
	{
		res = DSPL_ERROR_FILTER_WP;
		goto exit_label;	
	}
		
	p[0] = wp; 
	res =   dspl_compos(b, a, n, p, q, 1, beta, alpha);
		
exit_label:
	dspl_print_err(res, "dspl_ap2high");
	return res;
}








/* Analog low-pass prototype frequency transformation to low-pass 
filter with wp cutoff frequency    (dspl_filter_transform.c) */
DSPL_API int dspl_ap2low(double* b, double* a, int n, double wp, 
						 double* beta, double* alpha)
{
	double p[2] = {0.0, 1.0};
	double q[2] = {0.0, 0.0};
	int res;
	
	
	if(!b || !a || !beta || !alpha)
	{
		res = DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(n < 0)
	{
		res = DSPL_ERROR_FILTER_ORD;
		goto exit_label;	
	}
	if(wp<=0.0)
	{
		res =  DSPL_ERROR_FILTER_WP;
		goto exit_label;	
	}
		
	q[0] = wp; 
	res = dspl_compos(b, a, n, p, q, 1, beta, alpha);
			
exit_label:
	dspl_print_err(res, "dspl_ap2low");
	return res;
}




