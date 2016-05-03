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



/* DSPL VERSION */
#define DSPL_VERSION 0x00100418


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





DSPL_API int dspl_obj_create(void **obj)
{
	dspl_t *pdspl;
	if(!obj || (*obj))
		return DSPL_ERROR_PTR;

	(*obj) = (void*)malloc(sizeof(dspl_t));
	
	memset(*obj, 0, sizeof(dspl_t));
	
	pdspl = (dspl_t*)(*obj);
	
	pdspl->pfft   = (fft_t*)malloc (sizeof(fft_t));
	memset(pdspl->pfft, 0, sizeof(fft_t));

	
	pdspl->pconv = (conv_t*) malloc (sizeof(conv_t));	
	memset(pdspl->pconv, 0, sizeof(conv_t));

	fftw_init_threads();

	return DSPL_OK;
}




DSPL_API int dspl_obj_free(void **obj)
{
	dspl_t *pdspl;
	if(!obj)
		return DSPL_ERROR_PTR;
	if((*obj) == NULL)
		return DSPL_OK;
	fftw_cleanup_threads();
	pdspl = (dspl_t*)(*obj);
	dspl_fft_free(pdspl->pfft);
	
	free(pdspl->pfft);
	free(pdspl->pconv);
	
	free(*obj);
	*obj = NULL;
	
	return DSPL_OK;
}




BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)  
{
	switch( fdwReason )
	{
		case DLL_PROCESS_ATTACH:			
			break;
		case DLL_THREAD_ATTACH: 
			break;        
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			break;    
	}    
	return TRUE;  
}
