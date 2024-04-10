#ifndef _SORT_N_SEARCH_
#define _SORT_N_SEARCH_
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
typedef void *Val_t;
typedef size_t Index_t;
typedef char Byte_t;
typedef int(*bin_op_comp_t)(Val_t,Val_t) ;
/*  All this functions depend on an user-defined callback function
 *  called bin_op_comp .
 *  bin_op_comp is defined as comparison binary operator
 *  it receives 2 parameters, being valid void pointer to values 'a' and 'b'
 *  it is expected to return 0 if both values are equal
 *  it is expected to return >0 if value a > b
 */

void quick_sort(Val_t begin, Index_t size, Index_t elem_size, 
                bin_op_comp_t comparison_callback);
Index_t linear_search(Val_t begin, Index_t size, Index_t elem_size,
                      Val_t target, bin_op_comp_t comparison_callback);

Index_t binary_search(Val_t begin, Index_t size, Index_t elem_size,
                      Val_t target, bin_op_comp_t camparison_callback);
#endif

#ifdef SORT_N_SEARCH_IMPL

Index_t linear_search(const Val_t begin, const Index_t size,
                      const Index_t elem_size, const Val_t target,
                      int (*bin_op_comp)(Val_t, Val_t)) {
  int i = 0;
  Val_t elem = NULL;
  for (; i < size; i++) {
    elem = (begin + i * elem_size);
    if (bin_op_comp(elem, target) == 0)
      return i;
  }
  return size;
}

void swap(Val_t a, Val_t b, Val_t temp, Index_t elem_size) {
  if (a == b)
    return;
  memcpy(temp, a, elem_size);
  memcpy(a, b, elem_size);
  memcpy(b, temp, elem_size);
}

void swap_xor(Val_t a, Val_t b, Index_t elem_size) {
  int i;
  if (a == b)
    return;
  for (i = 0; i < elem_size; i++) {
    *((Byte_t *)(a + i)) ^= *((Byte_t *)(b + i));
  }
  for (i = 0; i < elem_size; i++) {
    *((Byte_t *)(b + i)) ^= *((Byte_t *)(a + i));
  }
  for (i = 0; i < elem_size; i++) {
    *((Byte_t *)(a + i)) ^= *((Byte_t *)(b + i));
  }
}
int partition(Val_t arr, int l, int h, Index_t elem_size,
              int (*bin_op_comp)(Val_t, Val_t)) {
  Val_t x = (arr + h * elem_size);
  int i = (l - 1);
  int j;

  for (j = l; j <= h - 1; j++) {
    if (bin_op_comp(arr + j * elem_size, x) > 0) {
      i++;
      swap_xor((arr + i * elem_size), (arr + j * elem_size), elem_size);
    }
  }
  swap_xor((arr + (i + 1) * elem_size), (arr + h * elem_size), elem_size);
  return (i + 1);
}

#define MAX_STACK_SIZE 100
void quick_sort(Val_t begin, const Index_t size, const Index_t elem_size,
                int (*bin_op_comp)(Val_t, Val_t)) {

  int aux[MAX_STACK_SIZE];

  int ind = -1;

  int l = 0;
  int h = size - 1;
  int p;
  assert(size + 1 <= MAX_STACK_SIZE);
  aux[++ind] = l;
  aux[++ind] = h;

  while (ind >= 0) {
    h = aux[ind--];
    l = aux[ind--];

    p = partition(begin, l, h, elem_size, bin_op_comp);

    if (p - 1 > l) {
      aux[++ind] = l;
      aux[++ind] = p - 1;
    }

    if (p + 1 < h) {
      aux[++ind] = p + 1;
      aux[++ind] = h;
    }
  }
}

Index_t binary_search(Val_t begin, Index_t size, Index_t elem_size,
                      Val_t target, int (*bin_op_comp)(Val_t, Val_t)) {
  Index_t left = 0;
  Index_t right = size - 1;
  while (left <= right) {
    Index_t m = left + (right - left) / 2;

    if (bin_op_comp(begin + m * elem_size, target) == 0)
      return m;

    if (bin_op_comp(begin + m * elem_size, target) > 0)
      left = m + 1;

    else{
      if (m == 0)
            return size;
      right = m - 1;
    }
  }

  return size;
}
#endif
