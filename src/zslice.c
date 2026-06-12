#include "zslice.h"
#include "zutils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Slice *NewSlice(size_t cap, size_t elem_size) {
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

int SlicePush(Slice *s, void *elem) {
  if (s->len == s->cap) {
    printf("ARRAY IS FULLY - REALLOC\n");
    size_t newCap = s->cap * 2;
    void *tmp = realloc(s->arr, newCap * s->elem_size);
    if (!tmp) {
      printf("MEMORY ERROR\n");
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
  return s->len - 1;
}
void SlicePrint(Slice *s, void (*printElem)(void *)) {
  char *byteAssembly = (char *)s->arr;
  for (size_t i = 0; i < s->len; i++) {
    printElem(byteAssembly + i * s->elem_size);
  }
}
void *SliceGet(const Slice *s, size_t i) {
  if (i >= s->len)
    return NULL;
  char *byteAssembly = (char *)s->arr;
  return byteAssembly + i * s->elem_size;
}

void FreeSlice(Slice *slice) {
  free(slice->arr);
  free(slice);
}

int main() {
  Slice *slice = NewSlice(5, sizeof(int));
  int val_1 = 1;
  int val_2 = 2;
  int val_3 = 3;
  int val_4 = 4;
  int val_5 = 5;
  int val_6 = 6;
  int idx_1 = SlicePush(slice, &val_1);
  int idx_2 = SlicePush(slice, &val_2);
  int idx_3 = SlicePush(slice, &val_3);
  int idx_4 = SlicePush(slice, &val_4);
  int idx_5 = SlicePush(slice, &val_5);
  int idx_6 = SlicePush(slice, &val_6);
  printf("idx_1: %d; idx_2: %d; idx_3: %d; idx_4: %d; idx_5: %d; idx_6: %d\n",
         idx_1, idx_2, idx_3, idx_4, idx_5, idx_6);
  SlicePrint(slice, printInt);
  int *val = SliceGet(slice, 4);
  if (val)
    printf("GETTING VALUE: %d\n", *val);
  FreeSlice(slice);
  return 1;
}
