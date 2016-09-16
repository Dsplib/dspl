#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "dspl.h"

int main()
{	
	/* DSPL handle */
	HINSTANCE hDSPL;
	void *pdspl = NULL;
	
	/* attach DSPL */
	hDSPL = dspl_load();
	if(!hDSPL)
	{
		printf("dspl.dll loading ERROR!\n");
		return 0;
	}
	
	/* create DSPL object */
	dspl_obj_create(&pdspl);
	
	/*print DSPL version */ 
	dspl_get_version(1);
 	

	/* destroy DSPL object */
	dspl_obj_free(&pdspl);
		
	/* deattach DSPL */ 	
	FreeLibrary(hDSPL);
	system("Pause");
	return 0;
}

