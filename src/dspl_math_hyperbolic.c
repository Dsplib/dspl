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



DSPL_API double dspl_asinh(double x)
{
	return log(x +sqrt(x*x+1.0));
}



DSPL_API double dspl_cosh(double x)
{
	return 0.5*(exp(x) + exp(-x));
}



DSPL_API double dspl_sinh(double x)
{
	return 0.5*(exp(x) - exp(-x));
}


