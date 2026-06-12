#include "zslice.h"
#include "zutils.h"
#include <_stdio.h>
#include <stdatomic.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Slice *SNew(size_t cap, size_t elem_size) {
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

int SPush(Slice *s, void *elem) {
  if (s->len == s->cap) {
    printf("ARRAY IS FULLY - REALLOC\n");
    size_t newCap = s->cap * 2;
    void *tmp = realloc(s->arr, newCap * s->elem_size);
    if (!tmp) {
      exit(EXIT_FAILURE);
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
  return s->len;
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
  size_t n = sizeof(values) / sizeof(values[0]);

  for (size_t i = 0; i < n; i++) {
    SPush(slice, &values[i]);
  }
}

int main() {
  Slice *slice = SNew(5, sizeof(int));
  printf("ENREACH SLICE\n");
  enreachSlice(slice);

  SPrint(slice, printInt);

  printf("---------------------\n");

  printf("POP SLICE\n");
  SPop(slice);

  SPrint(slice, printInt);

  SFree(slice);
  return 0;
}
