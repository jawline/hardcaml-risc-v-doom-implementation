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

FILE *fopen(const char *path, const char *mode) {
  printf("Fake fopen called %s\n", path);

  if (strcmp(path, "doom1.wad") == 0) {
    // Just return a pointer to the start of the wad, fread will just increment after each read.
    errno = 0;
    return (FILE*)  DOOM1_WAD;
  } else {
    errno = EACCES;
    return NULL;
  }
}
