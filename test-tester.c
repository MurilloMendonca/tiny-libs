#include "tester.h"

TEST_CASE_BEGIN(OneEqualsOne)
    TEST_ASSERT_MSG(1 == 1, "Se isso nao der certo, entao fudeu")
TEST_CASE_END(OneEqualsOne)

TEST_CASE_BEGIN(TwoEqualsOne)
    TEST_ASSERT_MSG(2 == 1, "Se isso der certo, fudeu tambem")
TEST_CASE_END(TwoEqualsOne)

TESTER_START(main)
  RUN_TEST_CASE(TwoEqualsOne)
  RUN_TEST_CASE(OneEqualsOne)
TESTER_END(main)
