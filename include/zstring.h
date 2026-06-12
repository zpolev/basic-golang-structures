#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdio.h>

typedef struct {
  void *arr;
  int len;
} String;

#endif /* STRING */
