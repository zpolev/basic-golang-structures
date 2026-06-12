#ifndef SLICE_H
#define SLICE_H

#include <stddef.h>
#include <stdio.h>

typedef struct {
  void *arr;
  size_t elem_size;
  size_t cap;
  size_t len;
} Slice;

Slice *NewSlice(size_t cap, size_t elem_size);
int SlicePush(Slice *s, void *elem);
void SlicePop(Slice *s);
void SliceRemove(Slice *s, size_t *i);
void SliceAppend(Slice *s, void *arr);
int SliceLen(Slice *s);
void *SliceGet(const Slice *s, size_t i);
void SlicePrint(Slice *s, void (*printElem)(void *));
void FreeSlice(Slice *s);
#endif /* SLICE_H */
