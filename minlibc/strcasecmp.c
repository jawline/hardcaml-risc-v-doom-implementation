/*
 * Copyright (C) 2014, Galois, Inc.
 * This sotware is distributed under a standard, three-clause BSD license.
 * Please see the file LICENSE, distributed with this software, for specific
 * terms and conditions.
 */
#include <ctype.h>
#include <strings.h>

int strcasecmp(const char *s1, const char *s2)
{
  int result;

  while (1) {
    result = tolower(*s1) - tolower(*s2);
    if (result != 0 || *s1 == '\0')
      break;

    ++s1;
    ++s2;
  }

  return result;
}

int 
strncasecmp(char const *s1,
    char const *s2, 
    unsigned int n)
{
  if (n == 0)
    return 0;

  while (n-- != 0 && tolower(*s1) == tolower(*s2))
    {
      if (n == 0 || *s1 == '\0' || *s2 == '\0')
    break;
      s1++;
      s2++;
    }

  return tolower(*(unsigned char *) s1) - tolower(*(unsigned char *) s2);
}
