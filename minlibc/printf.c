/* 
 * Copyright (C) 2014, Galois, Inc.
 * This sotware is distributed under a standard, three-clause BSD license.
 * Please see the file LICENSE, distributed with this software, for specific
 * terms and conditions.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

int printf(const char *format, ...)
{
  va_list args;
  int res;

  va_start(args, format);
  res = vfprintf(stdout, format, args);
  va_end(args);
  return res;
}


int sscanf(const char *src, const char *format, ...) {
    va_list ap;
    va_start(ap, format);

    const char *sp = src; // Source string pointer
    const char *fp = format; // Format string pointer
    int conversions = 0;

    while (*fp != '\0' && *sp != '\0') {
        if (isspace(*fp)) {
            // Collapse whitespace: move format pointer past spaces,
            // and source pointer past any number of spaces.
            while (isspace(*fp)) fp++;
            while (isspace(*sp)) sp++;
        } else if (*fp == '%') {
            fp++; // Move past '%'
            
            // Extract the current "word" from the source string into a buffer
            char buf[256]; // Temporary buffer, adjust size as needed
            int index = 0;
            // Read until whitespace or end of source string
            while (*sp != '\0' && !isspace(*sp) && index < sizeof(buf) - 1) {
                buf[index++] = *sp++;
            }
            buf[index] = '\0';

            switch (*fp) {
                case 'd': {
                    int *i = va_arg(ap, int *);
                    *i = atoi(buf); // Convert string to integer
                    conversions++;
                    break;
                }
                case 'f': {
                    float *f = va_arg(ap, float *);
                    *f = (float)atof(buf); // Convert string to float
                    conversions++;
                    break;
                }
                case 's': {
                    char *s = va_arg(ap, char *);
                    // Copy the buffer content to the destination array
                    strncpy(s, buf, sizeof(buf));
                    s[sizeof(buf) - 1] = '\0'; // Ensure null termination
                    conversions++;
                    break;
                }
                // Other specifiers (%c, %x, etc) would go here
            }
            fp++; // Move past the specifier character
            // Skip any potential trailing whitespace in the source for the next scan
            while (isspace(*sp)) sp++;

        } else {
            // Mismatch with non-whitespace character in format string
            if (*sp != *fp) {
                break; // Stop parsing on mismatch
            }
            sp++;
            fp++;
        }
    }

    va_end(ap);
    return conversions; // Return number of items successfully assigned
}

double fabs(double x) {
	return x < 0 ? -x : x;
}

int abs(int x) {
  return x < 0 ? -x : x;
}

void runtime_exit() {
  printf("Program is exiting. Looping forever\n");
  for (;;) {
  }
}

int     runtime_memprotect(void *addr, size_t length, int prot) {
        printf("mprotect ignored - this CPU does not support it\n");
}

void* mmap_start_address = (void*) 16777216;

void   *runtime_alloc(void *start, size_t length, int prot) {
  void* last = mmap_start_address;
  mmap_start_address += length;
  return last;
}

void    runtime_free(void *start, size_t length) {
        // Ignore free, just slab allocate
}

int system_call(int ecall_mode, void* input_pointer, unsigned int input_length) {
  int output_mode;
  asm volatile("addi x5, %[mode], 0\n"
      "addi x6, %[iptr], 0\n"
      "addi x7, %[ilength], 0\n"
      "ecall\n"
      "addi %[output_mode], x5, 0"
      : [output_mode] "=r" (output_mode) 
      : [mode] "r" (ecall_mode),
         [iptr] "r" (input_pointer),
         [ilength] "r" (input_length));
  return output_mode;
}

void send_dma_l(char* msg, int len) {
	while (!system_call(0, msg, len)) {}
}

void runtime_write(size_t len, char *buffer) {
  send_dma_l(buffer, len);
}
