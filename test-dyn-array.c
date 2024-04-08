#define DYN_ARRAY_IMPL
#include "dyn-array.h"
#include <stdio.h>

typedef struct {
  int x;
  float y;
} Test;
int main() {
  Dyn_array vec = dyn_array_create(sizeof(Test));
  Test c = {.x = 10, .y = 98.77f};
  size_t i;
  for (i = 0; i < 11; i++) {
    dyn_array_push_back(&vec, &c);
  }
  c.x = 0;
  for (i = 0; i < 10; i++) {
    dyn_array_push_back(&vec, &c);
  }
  for (i = 0; i < vec.size; i++) {
      Test* elem = (Test *)dyn_array_get(&vec, i);
    printf("val is: {%d, %f}\n", elem->x, elem->y);
  }

  Test* t = (Test *)dyn_array_get(&vec, 23);
  if(t){
    printf("val is: {%d, %f}\n", t->x, t->y);
  }
  else{
      printf("got null reading 23[expected]\n");
  }

  printf("Final size is %zu and cap is %zu\n", vec.size, vec.cap);
  return 0;
}
