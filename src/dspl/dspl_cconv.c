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
#include "dspl_main.h"



conv_t convObj;

/*
int dspl_cconv(double* a, double *b, int n, double* c)
{
		
	
}

*/



int  dspl_conv_create(int n)
{
	int n2 = n << 1;
	int p2 = 0;
	
	if(n<1)
		return DSPL_ERROR_SIZE;
	
	while (n2 >>= 1)
		p2++;
	
	p2++;
	n2 = 1 << p2;
	
	if(convObj.n >= n2)
		return DSPL_OK;
	
	convObj.n  = n2;
	convObj.aR = (double*)realloc(convObj.aR, n2*sizeof(double));
	convObj.aR = (double*)realloc(convObj.aR, n2*sizeof(double));
	convObj.bR = (double*)realloc(convObj.bR, n2*sizeof(double));
	convObj.bR = (double*)realloc(convObj.bR, n2*sizeof(double));
	convObj.cR = (double*)realloc(convObj.cR, n2*sizeof(double));
	convObj.cR = (double*)realloc(convObj.cR, n2*sizeof(double));	
	return DSPL_OK;	
}






void dspl_conv_free()
{
	if(convObj.aR) free(convObj.aR);
	if(convObj.aR) free(convObj.aR);
	if(convObj.bR) free(convObj.bR);
	if(convObj.bR) free(convObj.bR);
    if(convObj.cR) free(convObj.cR);
    if(convObj.cR) free(convObj.cR);
	convObj.n = 0;	
}