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
  return 0;
}

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
        //TODO 
  volatile  int* FAKE_ADDR = 0x0;
  return *FAKE_ADDR; 
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

char* ARGS[] = { "FAKE_EXE_PATH" };

void c_start() {
  printf("Start stub hit\n");
  main(1, ARGS);
}
