#include "doomkeys.h"
#include "doomgeneric.h"
#include "m_argv.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

void DG_Init()
{
  printf("Init called\n");  
}


uint32_t* framebuffer_ptr = (uint32_t*) 134217728;

void DG_DrawFrame()
{ 
        printf("DG_DrawFrame\n");
  // Since we hard code DG_ScreenBuffer to our frame buffer address we do not need to memcpy, saves some cache thrashing.
  //memcpy(framebuffer_ptr, DG_ScreenBuffer, DOOMGENERIC_RESX * DOOMGENERIC_RESY * sizeof(uint32_t));
}

uint32_t last = 0;

uint64_t get_time_ms(void) {
    last += 250;

    return last;
    //uint32_t low, high, temp;

    //printf("Enter get_time_ms\n");

    //__asm__ __volatile__ (
    //    "1:\n"
    //    "rdtimeh %0\n"   // Read upper 32 bits
    //    "rdtime  %1\n"   // Read lower 32 bits
    //    "rdtimeh %2\n"   // Read upper 32 bits again
    //    "bne %0, %2, 1b"  // If high word changed during read, retry
    //    : "=&r"(high), "=&r"(low), "=&r"(temp)
    //);

    //printf("Leave get_time_ms\n");

    //uint64_t ns = ((uint64_t)high << 32) | low;
    //return ns / 1000000; // Convert nanoseconds to milliseconds
}

void DG_SleepMs(uint32_t ms)
{
 //uint32_t last = get_time_ms();
 //uint32_t end = last + ms;
 //printf("Enter DG_SleepMs %i %i\n", last, end);
 //while (get_time_ms() < end) {
 //}
 //printf("Exit DG_SleepMs\n");
 return;
}


uint32_t DG_GetTicksMs()
{
  // TODO: Fake for now
  return get_time_ms();
}

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
  return 0;
}

void DG_SetWindowTitle(const char * title)
{
  //printf("SetWindowTitle %s\n", title);
  return;
}

extern uint32_t _sbss;
extern uint32_t _ebss;

void clear_bss(void) {
    uint32_t *dest = &_sbss;

    while (dest < &_ebss) {
        *dest++ = 0;
    }
}


void main() {
  clear_bss();
  printf("Entering Create\n");

  doomgeneric_Create();
  printf("Done with create\n");

  while(1) {
    doomgeneric_Tick(); 
  }

  return;
}


void c_start() {
  printf("Start stub hit\n");
  main();
}
