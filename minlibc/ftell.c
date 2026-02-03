/* 
 * Copyright (C) 2014, Galois, Inc.
 * This sotware is distributed under a standard, three-clause BSD license.
 * Please see the file LICENSE, distributed with this software, for specific
 * terms and conditions.
 */
#include <stdio.h>
#include <errno.h>
#include "doom1.h"

long ftell(FILE *stream __attribute__((unused)))
{
  printf("ftell\n");
  return (long) ((void*) stream - (void*) DOOM1_WAD);
}
