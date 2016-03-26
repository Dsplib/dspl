#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"



int main()
{


	HINSTANCE hDSPL;

	/* Load dspl.dll */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	printf("dspl.dll has been loaded successfully!\n");
		
	FreeLibrary(hDSPL);
	
	return 0;
}
