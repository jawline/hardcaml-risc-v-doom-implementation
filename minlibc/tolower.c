/*
 * Copyright (C) 2014, Galois, Inc.
 * This sotware is distributed under a standard, three-clause BSD license.
 * Please see the file LICENSE, distributed with this software, for specific
 * terms and conditions.
 */
#include <ctype.h>

int tolower(int c)
{
    if (c >= 'A' && c <= 'Z')
        return c + ('a' - 'A'); // Add the difference to move from 'A' to 'a'
    else
        return c;
}
