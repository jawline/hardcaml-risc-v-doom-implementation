/* 
 * Copyright (C) 2014, Galois, Inc.
 * This sotware is distributed under a standard, three-clause BSD license.
 * Please see the file LICENSE, distributed with this software, for specific
 * terms and conditions.
 */
#include <string.h>
#include <stdio.h>

void  *memcpy(void *dest, const void *src, size_t count)
{
  /* This would be a prime candidate for reimplementation in assembly */
  char *in_src = (char*)src;
  char *in_dest = (char*)dest;
  printf("memcpy %x %x %i\n", dest, src, count);

  while(count--) {
    *in_dest++ = *in_src++;
  }

  return dest;
}

