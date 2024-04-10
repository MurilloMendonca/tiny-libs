#ifndef _TESTER_
#define _TESTER_
#include "logger.h"

#define TEST_ASSERT(cond)                                                      \
  if (!(cond)) {                                                               \
    LOG_ERROR("Test failed at line %d in file %s", __LINE__, __FILE__);        \
    return 1;                                                                  \
  }

#define TEST_ASSERT_MSG(cond, msg)                                             \
  if (!(cond)) {                                                               \
    LOG_ERROR("Test failed at line %d in file %s: %s", __LINE__, __FILE__,     \
              msg);                                                            \
    return 1;                                                                  \
  }

#define TEST_CASE_BEGIN(name)                                                  \
  int name() {                                                                 \
    LOG_INFO("Running test case %s", #name);

#define TEST_CASE_END(name2)                                                   \
  LOG_INFO("Test case %s passed", #name2);                                     \
  return 0;                                                                    \
  }

#define RUN_TEST_CASE(name)                                                    \
  {                                                                            \
    int ret = name();                                                          \
    if (ret) {                                                                 \
      LOG_ERROR("Test case %s failed", #name);                                 \
      errors++;                                                                \
    }                                                                          \
  }
#define TESTER_START(name)                                                     \
  int main() {                                                                 \
    LOG_INFO("Running test suite %s", #name);                                  \
    int errors = 0;

#define TESTER_END(name2)                                                      \
  if (errors) {                                                                \
    LOG_ERROR("Test suite %s failed with %d errors", #name2, errors);          \
  } else {                                                                     \
    LOG_INFO("Test suite %s passed", #name2);                                  \
  }                                                                            \
  return errors;                                                               \
  }
#endif
