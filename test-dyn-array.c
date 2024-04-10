#define DYN_ARRAY_IMPL
#include "dyn-array.h"
#include "tester.h"
#include <stdio.h>

typedef struct {
  int x;
  float y;
} Test;

TEST_CASE_BEGIN(CreateCustomTypeDynArray)
    Dyn_array vec = dyn_array_create(sizeof(Test));
    TEST_ASSERT_MSG(vec.size == 0, "Size should be 0");
    TEST_ASSERT_MSG(vec.cap == 5, "Cap should be 5");
    dyn_array_destroy(&vec);
    TEST_ASSERT_MSG(vec.size == 0, "Size should be 0");
    TEST_ASSERT_MSG(vec.cap == 0, "Cap should be 0");
    TEST_ASSERT_MSG(vec._data == NULL, "Data should be NULL");
TEST_CASE_END(CreateCustomTypeDynArray)

TEST_CASE_BEGIN(PushBackCustomTypeDynArray)
    Dyn_array vec = dyn_array_create(sizeof(Test));
    Test c = {.x = 10, .y = 98.77f};
    size_t i;
    for (i = 0; i < 11; i++) {
      dyn_array_push_back(&vec, &c);
    }
    TEST_ASSERT_MSG(vec.size == 11, "Size should be 11");
    TEST_ASSERT_MSG(vec.cap == 20, "Cap should be 20");
    dyn_array_destroy(&vec);
TEST_CASE_END(PushBackCustomTypeDynArray)

TEST_CASE_BEGIN(GetDefinedValue)
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
      Test *elem = (Test *)dyn_array_get(&vec, i);
      if (i < 11) {
        TEST_ASSERT_MSG(elem->x == 10, "x should be 10");
      } else {
        TEST_ASSERT_MSG(elem->x == 0, "x should be 0");
      }
      TEST_ASSERT_MSG(elem->y == 98.77f, "y should be 98.77f");
    }
    Test *t = (Test *)dyn_array_get(&vec, 23);
    TEST_ASSERT_MSG(t == NULL, "Should be NULL");
    dyn_array_destroy(&vec);
TEST_CASE_END(GetDefinedValue)

TESTER_START(TestDynArray)
    RUN_TEST_CASE(CreateCustomTypeDynArray)
    RUN_TEST_CASE(PushBackCustomTypeDynArray)
    RUN_TEST_CASE(GetDefinedValue)
TESTER_END(TestDynArray)
