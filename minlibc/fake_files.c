/* 
 * Copyright (C) 2014, Galois, Inc.
 * This sotware is distributed under a standard, three-clause BSD license.
 * Please see the file LICENSE, distributed with this software, for specific
 * terms and conditions.
 */
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "doom1.h"

// TODO: To be cheap we just have a single global file pointer. This might need reworking.
void* CUR_POS;

FILE *fopen(const char *path, const char *mode) {
  printf("Fake fopen called %s\n", path);

  if (strcmp(path, "doom1.wad") == 0) {
    // Just return a pointer to the start of the wad, fread will just increment after each read.
    errno = 0;
    CUR_POS = DOOM1_WAD;
    printf("fopened DOOM1_WAD %x %p\n", DOOM1_WAD, (void*) DOOM1_WAD);
    return (FILE*) DOOM1_WAD;
  } else {
    errno = EACCES;
    return NULL;
  }
}

long ftell(FILE *stream __attribute__((unused)))
{
  if (stream == DOOM1_WAD) {
    printf("ftell on DOOM1_WAD\n");
    errno = 0;
    return (long) ((void*) CUR_POS - (void*) DOOM1_WAD);
  }
  else {
    printf("ftell unknown file\n");
    errno = EBADF;
    return -1;
  }
}


int fseek(FILE *stream __attribute__((unused)),
          long offset  __attribute__((unused)),
          int whence   __attribute__((unused)))
{

  if (stream >= DOOM1_WAD && stream <= DOOM1_WAD) {
    printf("fseek on DOOM1_WAD\n");
    errno = 0;

    if (whence == SEEK_SET) {
      if (offset > DOOM1_WAD_len) {
        errno = EACCES;
        return -1; 
      }
      CUR_POS = DOOM1_WAD + offset;
      printf("SEEK_SET offset %x %x %x\n", DOOM1_WAD, offset, CUR_POS);
      errno = 0;
      return 0;
    } else if (whence == SEEK_CUR) {
      void* new_pos = CUR_POS + offset;
      if (new_pos <= DOOM1_WAD || new_pos >= DOOM1_WAD + DOOM1_WAD_len) {
        errno = EACCES;
        return -1;
      } 
      CUR_POS = new_pos;
      printf("SEEK_CUR offset %x %x %x\n", DOOM1_WAD, offset, CUR_POS);
      return 0; 
    } else if (whence == SEEK_END) {
      if (offset > DOOM1_WAD_len) {
        errno = EACCES;
        return -1; 
      }
      CUR_POS = DOOM1_WAD + (DOOM1_WAD_len - offset);
      printf("SEEK_END offset %x %x %x\n", DOOM1_WAD, offset, CUR_POS);
      errno = 0;
      return 0;
    } else {
      printf("illegal whence\n");
      errno = EBADF;
      return -1;
    }
  } else {
    printf("fseek unknown file\n");
    errno = EBADF;
    return -1;
  }
}


size_t fread(void *ptr    __attribute__((unused)),
             size_t size  __attribute__((unused)),
             size_t nmemb __attribute__((unused)),
             FILE *stream __attribute__((unused)))
{
  if (stream == DOOM1_WAD) {

    unsigned long remaining_bytes = (unsigned long) ((((void*)DOOM1_WAD) + DOOM1_WAD_len) - CUR_POS);
    unsigned long max_chunks = remaining_bytes / size;

    if (max_chunks > nmemb) {
      max_chunks = nmemb;
    }

    unsigned long max_bytes = max_chunks * size;

    printf("fread DOOM1_WAD can %i %i %i %i\nstack pos %p ptr %p\n", size, nmemb, max_chunks, max_bytes,  &remaining_bytes, ptr);

    memcpy(ptr, CUR_POS, max_bytes);
    CUR_POS += max_bytes;

    errno = 0;
    return max_chunks;
  } else {
    printf("fread unknown file\n");
    errno = EACCES;
    return 0;
  }
}


int feof(FILE *stream __attribute__((unused)))
{
  printf("feof called\n");
  errno = EBADF;
  return -1;
}
