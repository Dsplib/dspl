/*
* Copyright 2015 Sergey Bakhurin
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "dspl.h"



/*
* Get DSPL version.
* This function return DSPL version
* ------------------------------------------------------------------------------------------
* Parameters:
*	[in] 	int printFlag -	Print DSPL version to console. 
*
* ------------------------------------------------------------------------------------------
* Author:
*	Sergey Bakhurin. 														www.dsplib.org	
*
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
		printf("     version %d.%d.%d\n\n", yy,mm,dd);
		printf("     Copyright (c) 2015       Sergey Bakhurin\n");
		printf("     home page: www.dsplib.org\n\n");		
	}
	return ver;
}







/*
* Print DSPL error code 
* ------------------------------------------------------------------------------------------
* Parameters:
*	[in] 	int res		-	DSPL function returned value
*
*	[in]	int printCR	-	Print CR symbol	
*
* ------------------------------------------------------------------------------------------
* Author:
*	Sergey Bakhurin. 														www.dsplib.org	
*
*/
DSPL_API void dspl_print_err(int res, int printCR)
{
	switch(res)
	{
		case DSPL_OK:
			printf("OK");
			break;
		case DSPL_ERROR_PTR:
			printf("ERROR: pointer is wrong!");
			break;
		case DSPL_ERROR_SIZE:
			printf("ERROR: input arrray size is wrong!");
			break;
		case DSPL_ERROR_FILTER_A0:
			printf("ERROR: IIR filter coefficient a[0] cannot be zero!");
			break;
		default:
			printf("Unknown error");		
	}
	if(printCR)
		printf("\n");	
	
}






/*
* Print DSPL message to console.
* ------------------------------------------------------------------------------------------
* Parameters:
*	[in] 	char* msg 		-	Text nessage
*
*	[in]	int printTime	-	Print current time in format [yyyy-mm-dd hh:mm:ss]	
*
*	[in]	int msgLen		- 	Message length
* ------------------------------------------------------------------------------------------
* Author:
*	Sergey Bakhurin. 														www.dsplib.org	
*
*/
DSPL_API void dspl_print_msg(char* msg, int printTime, int msgLen)
{
	int len;
	time_t t;
	struct tm *ti;
	char msgout[DSPL_MSG_LENGTH];
	
	memset(msgout, 0, DSPL_MSG_LENGTH);
	if(printTime)
	{
		time(&t);
		ti = localtime(&t);
		sprintf(msgout, "[%.4d-%.2d-%.2d %.2d:%.2d:%.2d] > ", ti->tm_year+1900, 
				ti->tm_mon+1, ti->tm_mday, ti->tm_hour, ti->tm_min, ti->tm_sec);

	}
	sprintf(msgout, "%s%s", msgout, msg);
	len = strlen(msgout);
	while(len<msgLen)
	{
		sprintf(msgout, "%s.", msgout);
		len++;	
	}
	printf("%s", msgout);
}







/*
* Save data to text file.
* Result file has format
* x[0]	y[0]
* x[1]	y[1]
* ...
* x[n-1]	y[n-1]
*
* ------------------------------------------------------------------------------------------
* Parameters:
*
*	double* x	-	First array pointer. Vector size is [n x 1].
* 
*	double* y	-	Second array pointer. Vector size is [n x 1]. Can be NULL. 
*					Text file will contain only x vector if y == NULL
*
*	int n		-	Input vector size
*
*	char* fn 	-	File name
*
* ------------------------------------------------------------------------------------------
* 
* Author:
*	Sergey Bakhurin. 														www.dsplib.org	
*
*/
DSPL_API int dspl_savetxt(double* x, double *y, int n, char* fn)
{
	int k;
	FILE* pFile = NULL;
	
	if(!x)
		return DSPL_ERROR_PTR;
	if(n < 1)
		return DSPL_ERROR_SIZE;
	if(!fn)
		return DSPL_ERROR_FNAME;
	
	pFile = fopen(fn, "w");
	if(pFile == NULL)
		return DSPL_ERROR_FOPEN;
	if(y)
		for(k = 0; k < n; k++)
			fprintf(pFile, "%+.12E\t%+.12E\n", x[k], y[k]);
	else
		for(k = 0; k < n; k++)
			fprintf(pFile, "%+.12E\n", x[k]);
	fclose(pFile);
	return DSPL_OK;	
}







