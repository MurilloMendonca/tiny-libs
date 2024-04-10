#include <stdio.h>
#define SORT_N_SEARCH_IMPL
#include "sort-n-search.h"
#define DYN_ARRAY_IMPL
#include "dyn-array.h"

#include "tester.h"
int char_comp(char *c1, char *c2) { return *(c1) - *(c2); }

typedef struct {
  int i;
  char c;
} Test;

int test_comp(Test *a, Test *b) { return a->c - b->c; }

TEST_CASE_BEGIN(LinearSearch)
  char word[10];
  int i;
  char b = 'b';
  char z = 'z';
  size_t b_index;
  size_t z_index;
  for (i = 0; i < 10; i++) {
    word[i] = 'a' + i;
  }
  b_index = linear_search(word, 10, sizeof(char), &b, (bin_op_comp_t)char_comp);
  TEST_ASSERT_MSG(b_index == 1, "index of b should be 1");

  z_index = linear_search(word, 10, sizeof(char), &z, (bin_op_comp_t)char_comp);
  TEST_ASSERT_MSG(z_index == 10, "index of z should be 10");
TEST_CASE_END(LinearSearch)

TEST_CASE_BEGIN(BinarySearch)
  char word[10];
  int i;
  char b = 'b';
  char z = 'z';
  size_t b_index;
  size_t z_index;
  for (i = 0; i < 10; i++) {
    word[i] = 'a' + i;
  }
  quick_sort(word, 10, sizeof(char), (bin_op_comp_t)char_comp);
  TEST_ASSERT_MSG(strncmp(word,"jihgfedcba",10) == 0, "word should be reversed");

  b_index = binary_search(word, 10, sizeof(char), &b, (bin_op_comp_t)char_comp);
  TEST_ASSERT_MSG(b_index == 8, "index of b should be 8");

  z_index = binary_search(word, 10, sizeof(char), &z, (bin_op_comp_t)char_comp);
  TEST_ASSERT_MSG(z_index == 10, "index of z should be 10");
TEST_CASE_END(BinarySearch)


TEST_CASE_BEGIN(InteropWithDynArray)
  Dyn_array da;
  Test t;
  int i;
  size_t b_index;
  size_t z_index;
  da = dyn_array_create(sizeof(Test));

  for (i = 0; i < 10; i++) {
    t.i = i;
    t.c = 'a' + i;
    dyn_array_push_back(&da, &t);
  }


  t.i = 1;
  t.c = 'b';
  b_index = linear_search(da._data, da.size, sizeof(Test), &t, (bin_op_comp_t)test_comp);
  TEST_ASSERT_MSG(b_index == 1, "index of b should be 1");

  t.i = 100;
  t.c = 'z';
  z_index = linear_search(da._data, da.size, sizeof(Test), &t, (bin_op_comp_t)test_comp);
  TEST_ASSERT_MSG(z_index == da.size, "index of z should be the size of the array");

  quick_sort(da._data, da.size, sizeof(Test), (bin_op_comp_t)test_comp);

  t.i = 1;
  t.c = 'b';
  b_index = binary_search(da._data, da.size, sizeof(Test), &t, (bin_op_comp_t)test_comp);
  TEST_ASSERT_MSG(b_index == 8, "index of b should be 8");

  dyn_array_destroy(&da);
TEST_CASE_END(InteropWithDynArray)

TESTER_START(TestSortNSearch)
  RUN_TEST_CASE(LinearSearch)
  RUN_TEST_CASE(BinarySearch)
  RUN_TEST_CASE(InteropWithDynArray)
TESTER_END(TestSortNSearch)
