#include "slice.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

Slice *NewSlice(size_t cap) {
  Slice *s = malloc(sizeof(Slice));
  if (!s) {
    return NULL;
  }
  s->arr = (int *)malloc(cap * sizeof(int));
  if (!s->arr) {
    return NULL;
  }
  s->len = 0;
  s->cap = cap;
  return s;
}

int SlicePush(Slice *s, const int elem) {
  if (s->len == s->cap) {
    printf("ARRAY IS FULLY REALLOC");
    size_t newCap = s->cap * 2;
    int *tmp = realloc(s->arr, newCap * sizeof(int));
    if (!tmp) {
      printf("MEMORY ERROR");
      return -1;
    }
    s->arr = tmp;
  }
  s->arr[s->len] = elem;
  s->len++;
  return s->len;
}
void SlicePrint(Slice *s) {
  for (size_t i = 0; i < s->len; i++) {
    printf("SLICE ELEM IDX: %ld; VALUE: %d", i, s->arr[i]);
  }
}
int SliceGet(const Slice *s, size_t i) {
  if (i >= s->len) {
    printf("INDEX: %ld OUT OF RANGE ERROR\n", i);
    return -1;
  }
  return s->arr[i];
}

void FreeSlice(Slice *slice) {
  free(slice->arr);
  free(slice);
}

int main() {
  Slice *slice = NewSlice(5);
  int idx_1 = SlicePush(slice, 1);
  int idx_2 = SlicePush(slice, 2);
  int idx_3 = SlicePush(slice, 3);
  int idx_4 = SlicePush(slice, 4);
  int idx_5 = SlicePush(slice, 5);
  int idx_6 = SlicePush(slice, 6);
  printf("idx_1: %d; idx_2: %d; idx_3: %d; idx_4: %d; idx_5: %d; idx_6: %d\n",
         idx_1, idx_2, idx_3, idx_4, idx_5, idx_6);
  SlicePrint(slice);
  int val = SliceGet(slice, 4);
  printf("GETTING VALUE: %d", val);
  FreeSlice(slice);
  return 1;
}
