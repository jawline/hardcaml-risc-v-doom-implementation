#include "doomkeys.h"
#include "doomgeneric.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

void DG_Init()
{
  printf("Init called\n");  
}


void DG_DrawFrame()
{
  printf("Draw Frame\n");
}

void DG_SleepMs(uint32_t ms)
{
  // Manually for loop 
  printf("TODO: DG_SleepMs");
}

uint32_t DG_GetTicksMs()
{
  printf("TODO: GetTickMS (Use RiscV hardware registers");
}

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
  return 0; 
}

void DG_SetWindowTitle(const char * title)
{
  printf("SetWindowTitle %s\n", title);
}

int main(int argc, char **argv)
{
  printf("Entering Create\n");
  doomgeneric_Create(argc, argv);

  while(1) {
    printf("Entering tick\n");
    doomgeneric_Tick(); 
  }

  return 0;
}

void _start() {
  printf("Start stub hit\n");
  main(0, NULL);
}
