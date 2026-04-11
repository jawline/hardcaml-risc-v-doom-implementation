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

uint64_t get_time_ms(void) {
    uint32_t low, high, temp;
    
    __asm__ __volatile__ (
        "1:\n"
        "rdtimeh %0\n"   
        "rdtime  %1\n"   
        "rdtimeh %2\n"   
        "bne %0, %2, 1b\n" 
        : "=&r"(high), "=&r"(low), "=&r"(temp)
        : /* no inputs */
        : "memory" 
    );

    uint64_t ns = ((uint64_t)high << 32) | low;
    uint64_t ms = ns / 1000000;
    return ms;
}


uint32_t* framebuffer_ptr = (uint32_t*) 134217728;

uint32_t draws  = 0;
uint32_t last = 0;

void DG_DrawFrame()
{ 
  // Since we hard code DG_ScreenBuffer to our frame buffer address we do not need to memcpy, saves some cache thrashing.
  //memcpy(framebuffer_ptr, DG_ScreenBuffer, DOOMGENERIC_RESX * DOOMGENERIC_RESY * sizeof(uint32_t));
  uint32_t next = get_time_ms();
  draws++;
  if (next - last > 1000) {
          printf("FPS: %i\n", draws);
          draws = 0;
          last = next;
  }
}


void DG_SleepMs(uint32_t ms)
{
 //uint32_t last = get_time_ms();
 //uint32_t end = last + ms;
 //printf("Enter DG_SleepMs %i %i\n", last, end);
 //while (get_time_ms() < end) {
 //}
 //printf("Exit DG_SleepMs\n");
 printf("sleep %i\n", ms);
 return;
}


uint32_t DG_GetTicksMs()
{
  // TODO: Fake for now
  return get_time_ms();
}

bool flip = false;

#define KEYMAP_PTR 134216704
#define KEYMAP_SIZE 128

// This is a simple event ring that allows us to process up to four events a frame. If we miss an event it's gone forever.
static size_t keymap_i= 0;

int DG_GetKey(int* pressed, unsigned char* doomKey)
{
  
  uint32_t* keymap_cur = (((uint32_t*) KEYMAP_PTR) + keymap_i);
  uint32_t val = *keymap_cur;

  bool event_occured = val != 0;
  uint8_t key_in_event = val;
  bool key_is_pressed = (val & 0b100000000) != 0;

  if (event_occured) {
    //printf("Key event detected I: %i V: %p KEY: %i PRESSED:%i U32:%p UP:%i DN:%i L:%i R:%i\n", keymap_i, val, key_in_event, key_is_pressed, keymap_cur, KEY_UPARROW, KEY_DOWNARROW, KEY_LEFTARROW, KEY_RIGHTARROW);
    keymap_i = (keymap_i + 1) % KEYMAP_SIZE;

    *doomKey = key_in_event;
    *pressed = key_is_pressed;
    *keymap_cur = 0;

    return true;
  } else { 
    return false;
  }
}

void DG_SetWindowTitle(const char * title)
{
  //printf("SetWindowTitle %s\n", title);
  return;
}

void main() {
  printf("Entering Create\n");

  doomgeneric_Create();
  printf("Done with create\n");

  printf("Clearing key event buffer\n");

  memset((void*) KEYMAP_PTR, 0, sizeof(uint32_t) * KEYMAP_SIZE);

  while(1) {
    doomgeneric_Tick(); 
  }

  return;
}


void c_start() {
  printf("Start stub hit\n");
  main();
}
