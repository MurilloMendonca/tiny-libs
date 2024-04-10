#include "dyn-array.hpp"
#include <cstdio>
#include "tester.h"

typedef struct {
  int x;
  float y;
} Test;

TEST_CASE_BEGIN(CreateAndPushBack)
  DynamicArray<Test> vec;
  TEST_ASSERT(vec.size() == 0);
  TEST_ASSERT(vec.cap() == 5);
  for (int i = 0; i < 11; i++) {
    vec.push_back({i, 8.9});
  }
  TEST_ASSERT(vec.size() == 11);
  TEST_ASSERT(vec.cap() == 20);
TEST_CASE_END(CreateAndPushBack)

TEST_CASE_BEGIN(IteratorLoopOver)
    DynamicArray<Test> vec;
    for (int i = 0; i < 11; i++) {
        vec.push_back({i, 8.9});
    }
    for (int i = 0; i < 11; i++) {
        vec.push_back({i * 2, 8.9});
    }
    int i = 0;
    for (auto t: vec) {
        if (i < 11) {
            TEST_ASSERT(t.x == i);
        } else {
            TEST_ASSERT(t.x == (i-11) * 2);
        }
        i++;
    }
    TEST_ASSERT(i == 22);
TEST_CASE_END(IteratorLoopOver)


TEST_CASE_BEGIN(GetOptionalValue)
    DynamicArray<Test> vec;
    for (int i = 0; i < 11; i++) {
        vec.push_back({i, 8.9});
    }
    for (int i = 0; i < 11; i++) {
        vec.push_back({i * 2, 8.9});
    }
    auto x = vec.get(23);
    TEST_ASSERT(x.has_value() == false);
    TEST_ASSERT(vec.size() == 22);
    TEST_ASSERT(vec.cap() == 40);
TEST_CASE_END(GetOptionalValue)


TESTER_START(DynamicArrayTestCpp)
  RUN_TEST_CASE(CreateAndPushBack);
  RUN_TEST_CASE(IteratorLoopOver);
  RUN_TEST_CASE(GetOptionalValue);
TESTER_END(DynamicArrayTestCpp)
