#include <stdio.h>
#define SORT_N_SEARCH_IMPL
#include "sort-n-search.h"
#define DYN_ARRAY_IMPL
#include "dyn-array.h"

int char_comp(void *c1, void *c2) { return *((char *)c1) - *((char *)c2); }

typedef struct {
  int i;
  char c;
} Test;

int test_comp(void *a, void *b) { return ((Test *)a)->c - ((Test *)b)->c; }
int main() {
  char word[10];
  int i;
  char b = 'b';
  char z = 'z';
  size_t b_index;
  size_t z_index;
  Dyn_array da;
  Test t;
  for (i = 0; i < 10; i++) {
    word[i] = 'a' + i;
  }
  printf("word: %.*s\n", 10, word);

  b_index = linear_search(word, 10, sizeof(char), &b, char_comp);
  printf("index of b: %zu\n", b_index);

  z_index = linear_search(word, 10, sizeof(char), &z, char_comp);
  printf("index of z: %zu\n", z_index);

  quick_sort(word, 10, sizeof(char), char_comp);
  printf("word: %.*s\n", 10, word);

  b_index = binary_search(word, 10, sizeof(char), &b, char_comp);
  printf("index of b: %zu\n", b_index);

  da = dyn_array_create(sizeof(Test));

  for (i = 0; i < 10; i++) {
    t.i = i;
    t.c = 'a' + i;
    dyn_array_push_back(&da, &t);
  }

  printf("dyn word: ");
  for (i = 0; i < da.size; i++)
    printf("%c", ((Test *)dyn_array_get(&da, i))->c);
  printf("\n");

  t.i = 1;
  t.c = 'b';
  b_index = linear_search(da._data, da.size, sizeof(Test), &t, test_comp);
  printf("index of b: %zu\n", b_index);

  t.i = 100;
  t.c = 'z';
  z_index = linear_search(da._data, da.size, sizeof(Test), &t, test_comp);
  printf("index of z: %zu\n", z_index);

  quick_sort(da._data, da.size, sizeof(Test), test_comp);
  printf("dyn word: ");
  for (i = 0; i < da.size; i++)
    printf("%c", ((Test *)dyn_array_get(&da, i))->c);
  printf("\n");

  t.i = 1;
  t.c = 'b';
  b_index = binary_search(da._data, da.size, sizeof(Test), &t, test_comp);
  printf("index of b: %zu\n", b_index);

  dyn_array_destroy(&da);

  return 0;
}
