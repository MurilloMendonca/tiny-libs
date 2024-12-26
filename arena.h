#ifndef _ARENA_
#define _ARENA_

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
  char *_data;
  size_t size;
  size_t cap;
  bool growable;
} HeapArena;

HeapArena heap_arena_create(size_t initial_cap, bool growable);
void heap_arena_destroy(HeapArena *ha);
void *heap_arena_alloc(HeapArena *ha, size_t size);

#endif

#ifdef ARENA_IMPL

HeapArena heap_arena_create(size_t initial_cap, bool growable) {
  HeapArena ha = {._data = (char *)malloc(initial_cap),
                  .size = 0,
                  .cap = initial_cap,
                  .growable = growable};
  return ha;
}

void heap_arena_destroy(HeapArena *ha) {
  free(ha->_data);
  ha->_data = NULL;
  ha->size = 0;
  ha->cap = 0;
  ha->growable = false;
}

void *heap_arena_alloc(HeapArena *ha, size_t size) {
  if (!ha->_data || ha->cap == 0 || ha->cap < ha->size + size) {
    if (!ha->growable) {
      return NULL;
    }
    size_t newCap = ha->cap == 0 ? size : ha->cap * 2;
    ha->_data = (char *)realloc(ha->_data, newCap);
    ha->cap = newCap;
  }
  void *ptr = ha->_data + ha->size;
  ha->size += size;
  return ptr;
}
#endif
