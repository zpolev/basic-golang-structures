#include "zslice.h"
#include "log.h"
#include "zutils.h"
#include <stdatomic.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Slice *SNew(size_t cap, size_t elem_size) {
  if (cap <= 0) {
    cap = 1;
  }
  Slice *s = malloc(sizeof(Slice));
  if (!s) {
    return NULL;
  }
  s->arr = malloc(cap * elem_size);
  if (!s->arr) {
    free(s);
    return NULL;
  }
  s->len = 0;
  s->cap = cap;
  s->elem_size = elem_size;
  return s;
}

int SPush(Slice *s, const void *elem) {
  if (s->len == s->cap) {
    size_t newCap = s->cap * 2;
    LOG(LOG_WARN, "slice is full, reallocating to cap=%zu", newCap);
    void *tmp = realloc(s->arr, newCap * s->elem_size);
    if (!tmp) {
      LOG(LOG_ERROR, "realloc failed");
      return -1;
    }
    s->arr = tmp;
    s->cap = newCap;
  }
  // arithmetic of pointers
  // pointer to chars
  // byteAssembly + 1 = + 1 byte
  // int *byteAssembly = (int *)s->arr
  // byteAssembly + 1 = + 4 byte
  char *byteAssembly = (char *)s->arr;
  // void *memcpy(void *dest, const void *src, size_t n)
  // copy n byte form src to dest
  memcpy(byteAssembly + s->len * s->elem_size, elem, s->elem_size);
  s->len++;
  return 0; //
}

void SPrint(Slice *s, void (*printElem)(void *)) {
  char *byteAssembly = (char *)s->arr;
  for (size_t i = 0; i < s->len; i++) {
    printElem(byteAssembly + i * s->elem_size);
  }
}
void *SGet(const Slice *s, size_t i) {
  if (i >= s->len)
    return NULL;
  char *byteAssembly = (char *)s->arr;
  return byteAssembly + i * s->elem_size;
}

void SPop(Slice *s) {
  if (s->len == 0)
    return;
  s->len--;
}
void SRemove(Slice *s, size_t *i) {
  if (*i >= s->len)
    return;
  char *byteAssembly = (char *)s->arr;
  for (size_t j = *i; j < s->len - 1; j++) {
    memcpy(byteAssembly + j * s->elem_size,
           byteAssembly + (j + 1) * s->elem_size, s->elem_size);
  }
  s->len--;
}

void SFree(Slice *slice) {
  free(slice->arr);
  free(slice);
}

void enreachSlice(Slice *slice) {
  int values[] = {1, 2, 3, 4, 5, 6};
  APPEND_ARR(slice, values);
}

int SAppend(Slice *dst, const Slice *src) {
  if (dst->elem_size != src->elem_size)
    return -1;
  if (SReserve(dst, src->len) == -1)
    return -1;
  const char *base = (const char *)src->arr;
  for (size_t i = 0; i < src->len; i++) {
    SPush(dst, base + i * src->elem_size);
  }
  return 0;
}
int SAppendArr(Slice *s, const void *arr, size_t lenArr) {
  if (SReserve(s, lenArr) == -1)
    return -1;
  const char *src = (const char *)arr;
  for (size_t i = 0; i < lenArr; i++) {
    SPush(s, src + i * s->elem_size);
  }
  return 0;
}

int main() {
  Slice *slice = SNew(5, sizeof(int));
  LOG(LOG_INFO, "enreaching slice");
  enreachSlice(slice);

  SPrint(slice, printInt);

  printf("---------------------\n");

  LOG(LOG_INFO, "pop slice");
  SPop(slice);

  SPrint(slice, printInt);

  SFree(slice);
  return 0;
}
