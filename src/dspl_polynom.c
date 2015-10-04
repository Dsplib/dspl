/*
*Copyright (c) 2015 Sergey Bakhurin
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





/*
* Real polynom calculation
* Function calculates a polynom 
* 
* y(x) = a0 + a1*x + a2*x^2 + a3*x^3 + ... aord*x^ord.
* 
* for vector argument x. Output is vector y which contains polynom value for each x
* This function use follow polynom facotization:
*
* y(x) = a[0] + x*(a[1] + x*(a[2] + x*(... x*(a[ord-1] + x*a[ord]) ...))) 
*
* ------------------------------------------------------------------------------------------
* Parameters:
*	[in]	double* a	-	Polynom coefficients vector pointer. Vector size is [ord+1 x 1].
*							Coefficient a[0] corresponds to a0 polynom coefficent
*  
*	[in]	int ord		-	Polynom order. 
*					  
*	[in]	double* x	- 	Polynom argument vector pointer. Vector size ia [n x 1].
*							Polynom will be calculated for all x values.
*
*	[in]	int n		-	Polynom argument vector size. 		
*
*	[out]	double* y	- 	Polynom values for all arguments x. Vector size is [n x 1]
*							Memory must be allocated. 
* 	                                                                          
* ------------------------------------------------------------------------------------------
* Return:
*	DSPL_OK 		if filter output is calculted successfuly
*
*	DSPL_ERROR_PTR	if pointer are wrong. This situation can be if:
*					a is NULL or x is NULL or y is NULL.
*
*	DSPL_ERROR_SIZE if n < 1.
*
*	DSPL_ERROR_POLY_ORD if polynom order less than 0.
* ------------------------------------------------------------------------------------------
* Example
*	double a[3] = {0, 0, 1};
*	double x[5] = {0, 0.5, 1, 2, 4};
*	double y[5];
*	dspl_polynom(a, 2, x, 5, y);
*
*	y will keep values: 0, 0.25, 1, 4, 16
* Author:
*	Sergey Bakhurin. 														www.dsplib.org	
*
*/
DSPL_API int dspl_polynom(double* a, int ord, double* x, int n, double* y)

{
	int k;
	int m;      
	if(!a || !x || !y)
		return DSPL_ERROR_PTR;
	if(ord<0)
		return DSPL_ERROR_POLY_ORD;
	if(n<1)
		return DSPL_ERROR_SIZE;
	
	for(k = 0; k < n; k++)
	{
		y[k] = a[ord];
	 	for(m = ord-1; m>-1; m--)
			y[k] = y[k]*x[k] + a[m];			
	}            
}








DSPL_API int dspl_polynom_cmplx(	double* aR, double* aI, int ord, 
									double* xR, double* xI, int n,
									double* yR, double* yI)
{
	int k;
	int m;
	double pR;
	double pI;
	double tR;
	double tI;
	double *cI;
	double *tI; 
    
	if(!aR || !xR || !yR)
		return DSPL_ERROR_PTR;
	if(ord<0)
		return DSPL_ERROR_POLY_ORD;
	if(n<1)
		return DSPL_ERROR_SIZE;
	if((aI || xI)&& !yI)
		return DSPL_ERROR_PTR;

	if(!aI && !xI && !yI)
		return dspl_polynom(aR, ord, xR, n, yR);
	
	cI = aI;
	if(!cI)
	{
		cI = (double*)malloc((ord+1)*sizeof(double));
		memset(cI, 0, (ord+1)*sizeof(double));
	}

	tI = xI;
	if(!tI)
	{
		tI = (double*)malloc(n*sizeof(double));
		memset(tI, 0, n*sizeof(double));
	}

	for(k = 0; k < n; k++)
	{
		pR = aR[ord];
		pI = cI[ord];
	 	for(m = ord-1; m>-1; m--)
		{
			tR = pR*xR[k] - pI*tI[k] + aR[m];
			tI = pR*tI[k] + pI*xR[k] + cI[m];
			pR = tR;
			pI = tI;	 	
		}	        			
	} 

	if(cI!=aI)
		free(cI);

	if(tI!=xI)
		free(tI);

	return DSPL_OK;

}