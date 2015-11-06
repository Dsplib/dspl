#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"
#include "dspl_load.h"


int main()
{

	HINSTANCE hInstDLL;

	/* Load dspl.dll */
	hInstDLL = dspl_load();
	if(!hInstDLL)
	{
		printf("dspl.dll Loading Error!\n");
		return 0;
	}

	
	/*print current dspl.dll version */
	dspl_get_version(1);
	
	FreeLibrary(hInstDLL);
	
	return 0;
}
