#include <stdio.h>

#include "m_argv.h"

#include "doomgeneric.h"


void M_FindResponseFile(void);
void D_DoomMain (void);


void doomgeneric_Create()
{
	M_FindResponseFile();
  printf("found response file\n");

	DG_Init();

  printf ("call dg_init\n");

	D_DoomMain ();
  
  printf("done with D_DoomMain\n");
}

