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
int SPush(Slice *s, const void *elem);
int appendArr(Slice *s, const void *arr, size_t lenArr);
int SAppendArr(Slice *s, const void *arr, size_t lenArr);
int SAppend(Slice *dst, const Slice *src);
int SReserve(Slice *s, size_t extra);
void SPrint(Slice *s, void (*printElem)(void *));
void *SGet(const Slice *s, size_t i);
void SPop(Slice *s);
void SRemove(Slice *s, size_t *i);
void SFree(Slice *slice);

#define APPEND_ARR(s, arr) appendArr((s), (arr), sizeof(arr) / sizeof((arr)[0]))
#endif /* SLICE_H */
