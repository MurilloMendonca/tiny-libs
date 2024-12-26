#ifndef _ARENA_
#define _ARENA_

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef STACK_ARENA_SIZE
#define STACK_ARENA_SIZE 1024
#endif
typedef struct {
  char *_data;
  size_t size;
  size_t cap;
  bool growable;
} HeapArena;

typedef struct {
  size_t size;
  char _data[STACK_ARENA_SIZE];
} StackArena;

HeapArena heap_arena_create(size_t initial_cap, bool growable);
void heap_arena_destroy(HeapArena *ha);
void *heap_arena_alloc(HeapArena *ha, size_t size);

StackArena stack_arena_create();
void stack_arena_destroy(StackArena *sa);
void *stack_arena_alloc(StackArena *sa, size_t size);

#endif

#ifdef ARENA_IMPL


StackArena stack_arena_create() {
  StackArena sa = {.size = 0, ._data = {0}};
  return sa;
}

void stack_arena_destroy(StackArena *sa) {
  sa->size = 0;
  memset(sa->_data, 0, STACK_ARENA_SIZE);
}

void *stack_arena_alloc(StackArena *sa, size_t size) {
  if (sa->size + size > STACK_ARENA_SIZE) {
    return NULL;
  }
  void *ptr = sa->_data + sa->size;
  sa->size += size;
  return ptr;
}

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
