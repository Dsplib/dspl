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




DSPL_API int dspl_freqz(double* b, double* a, int ord, 
						double* w, int n, 
						double *hR, double* hI)
{

	double jwR;
	double jwI;
	double nR;
	double nI;
	double dR;
	double dI;
	double mag;
	int k;

	if(!b || !a || !w || !hR || !hI)
		return DSPL_ERROR_PTR;
	if(ord<0)
		return DSPL_ERROR_FILTER_ORD;
	if(n<1)
		return DSPL_ERROR_SIZE;


	for(k = 0; k < n; k++)
	{
		jwR =  cos(w[k]);
		jwI = -sin(w[k]);
		dspl_polyval_cmplx(b, NULL, ord, &jwR, &jwI, 1, &nR, &nI);	
		dspl_polyval_cmplx(a, NULL, ord, &jwR, &jwI, 1, &dR, &dI);
		mag = 1.0 / (dR * dR + dI * dI);
		hR[k] = (nR * dR + nI * dI) * mag;
		hI[k] = (nI * dR - nR * dI) * mag;
 
	}

	return DSPL_OK;
}  