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

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dspl.h"




DSPL_API int dspl_freqs(double* b, double* a, int ord, 
						double* w, int n, 
						double *hR, double* hI)
{

	double jwR;
	
	double nR;
	double nI;
	double dR;
	double dI;
	double mag;
	int k;
	int res;
	
	if(!b || !a || !w || !hR || !hI)
	{
		res = DSPL_ERROR_PTR;
		goto exit_label;	
	}
	if(ord<0)
	{
		res = DSPL_ERROR_FILTER_ORD;
		goto exit_label;	
	}
	if(n<1)
	{
		res = DSPL_ERROR_SIZE;
		goto exit_label;	
	}

    jwR = 0.0;

	for(k = 0; k < n; k++)
	{
		res = dspl_polyval_cmplx(b, NULL, ord, &jwR, w+k, 1, &nR, &nI);	
		if(res != DSPL_OK)
			goto exit_label;
		res = dspl_polyval_cmplx(a, NULL, ord, &jwR, w+k, 1, &dR, &dI);
		if(res != DSPL_OK)
			goto exit_label;
		mag = 1.0 / (dR * dR + dI * dI);
		hR[k] = (nR * dR + nI * dI) * mag;
		hI[k] = (nI * dR - nR * dI) * mag;
 
	}
	
	res = DSPL_OK;		
exit_label:
	dspl_print_err(res, "dspl_freqs");
	return res;
}  