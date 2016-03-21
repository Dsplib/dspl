#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"


int main()
{


	HINSTANCE hInstDLL;

	/* Load dspl.dll */
	hInstDLL = dspl_load();
	if(!hInstDLL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}

	printf("dspl.dll has been loaded successfully!\n");
		
	FreeLibrary(hInstDLL);
	
	return 0;
}
