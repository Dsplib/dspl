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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "dspl.h"
#include "dspl_main.h"


/* global FFT Object */
fft_t fftObj;


/* global Convolution Object */
conv_t convObj;

/* DSPL VERSION */
#define DSPL_VERSION 0x00100401


/*
* Get DSPL version.
* This function return DSPL version
*/
DSPL_API int dspl_get_version(int printFlag)
{
	int ver = DSPL_VERSION;
	int yy;
	int mm;
	int dd;
	

	if(printFlag)
	{
		yy = (ver & 0x00FF0000) >> 16;
		mm = (ver & 0x0000FF00) >> 8;
		dd = (ver & 0x000000FF);
		printf("\n\n     D S P L\n");
		printf("     version %.2d.%.2d.%.2d\n\n", yy,mm,dd);
		printf("     Copyright (c) 2015, 2016  Sergey Bakhurin\n");
		printf("     home page: www.dsplib.org\n\n");		
	}
	return ver;
}





BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)  
{
	switch( fdwReason ){
		case DLL_PROCESS_ATTACH:
			dspl_get_version(1);				
			memset(&fftObj,  0, sizeof(fft_t));
			memset(&convObj, 0, sizeof(conv_t));
			break;
		case DLL_THREAD_ATTACH:         

			break;        
		case DLL_THREAD_DETACH:

			break;
		case DLL_PROCESS_DETACH:
			dspl_fft_free();
			dspl_conv_free();
			break;    
	}    
	return TRUE;  
}
