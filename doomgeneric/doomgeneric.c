#include <stdio.h>

#include "m_argv.h"

#include "doomgeneric.h"

pixel_t* DG_ScreenBuffer = NULL;

void M_FindResponseFile(void);
void D_DoomMain (void);


void doomgeneric_Create(int argc, char **argv)
{
	// save arguments
    myargc = argc;
    myargv = argv;

  printf("enter doomgeneric_Create\n");

	M_FindResponseFile();

  printf("found response file\n");



	DG_ScreenBuffer = malloc(DOOMGENERIC_RESX * DOOMGENERIC_RESY * 4);

  printf("malloc screenbuffer\n");

	DG_Init();

  printf ("call dg_init\n");

	D_DoomMain ();
}

