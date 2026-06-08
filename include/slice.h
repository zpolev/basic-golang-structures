#ifndef SLICE_H
#define SLICE_H

#include <stddef.h>

typedef struct {
  int *arr;
  size_t cap;
  size_t len;
} Slice;

Slice *NewSlice(size_t cap);
int SlicePush(Slice *s, const int elem);
void SlicePrint(Slice *s);
int SliceGet(const Slice *s, size_t i);

#endif /* SLICE_H */
