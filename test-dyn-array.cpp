#include "dyn-array.hpp"
#include <stdio.h>

typedef struct {
  int x;
  float y;
} Test;

int main() {
  DynamicArray<Test> vec;
  for (int i = 0; i < 11; i++) {
    vec.push_back({i, 8.9});
  }
  for (int i = 0; i < 11; i++) {
    vec.push_back({i * 2, 8.9});
  }
  for (auto t: vec) {
    printf("val is: {%d, %f}\n", t.x, t.y);
  }
  printf("Final size is %zu and cap is %zu\n", vec.size(), vec.cap());
  return 0;
}
