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

Slice *SNew(size_t cap, size_t elem_size);
int SPush(Slice *s, void *elem);
void SPop(Slice *s);
void SRemove(Slice *s, size_t *i);
void SAppend(Slice *s, void *arr);
size_t SLen(Slice *s);
void *SGet(const Slice *s, size_t i);
void SPrint(Slice *s, void (*printElem)(void *));
void SFree(Slice *s);
#endif /* SLICE_H */
