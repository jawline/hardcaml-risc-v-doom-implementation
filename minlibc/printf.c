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
