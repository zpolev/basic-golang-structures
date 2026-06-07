#ifndef SLICE_H
#define SLICE_H

#include <cstddef>
#include <stddef.h>

typedef struct {
  void *arr;
  size_t elemSize;
  size_t cap;
  size_t len;
} Slice;

Slice *NewSlice(size_t elemsize, size_t cap);
int SlicePush(Slice *s, const void *elem);
void *SliceGet(const Slice *s, size_t i);

#endif /* SLICE_H */
