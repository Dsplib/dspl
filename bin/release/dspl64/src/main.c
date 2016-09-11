#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <sys/stat.h>
#include <errno.h>


#define DEFAULT_MODE      S_IRWXU | S_IRGRP |  S_IXGRP | S_IROTH | S_IXOTH

/** Utility function to create directory tree */
int mkdirp(char* path, mode_t mode = DEFAULT_MODE);




int mkdirp(char* path, mode_t mode) {
  // const cast for hack
  char* p = path;
 char v;
  // Do mkdir for each slash until end of string or error
  while (*p != '\0') {
    // Skip first character
    p++;

    // Find first slash or end
    while(*p != '\0' && *p != '/') p++;

    // Remember value from p
    v = *p;

    // Write end of string at p
    *p = '\0';

    // Create folder from path to '\0' inserted at p
    if(mkdir(path, mode) == -1 && errno != EEXIST) {
      *p = v;
      return 0;
    }

    // Restore path to it's former glory
    *p = v;
  }

  return 1;
}


int main()
{
    mkdirp("/tmp/a/b/c", DEFAULT_MODE);
    return 0;
}


//#include <stdio.h>
//#include <stdlib.h>
//#include <windows.h>
//#include "dspl.h"
//
//int main()
//{	
//	/* DSPL handle */
//	HINSTANCE hDSPL;
//	void *pdspl = NULL;
//	
//	/* attach DSPL */
//	hDSPL = dspl_load();
//	if(!hDSPL)
//	{
//		printf("dspl.dll loading ERROR!\n");
//		return 0;
//	}
//	
//	/* create DSPL object */
//	dspl_obj_create(&pdspl);
//	
//	/*print DSPL version */ 
//	dspl_get_version(1);
// 	
//	/* destroy DSPL object */
//	dspl_obj_free(&pdspl);
//		
//	/* deattach DSPL */ 	
//	FreeLibrary(hDSPL);
//	
//	return 0;
//}

