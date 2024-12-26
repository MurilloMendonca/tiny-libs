#define STACK_ARENA_SIZE 1024
#define ARENA_IMPL
#include "arena.h"
#include "tester.h"



TEST_CASE_BEGIN(DefaultArenaInitializationAndDestruction)
  StackArena ha = stack_arena_create();
  TEST_ASSERT_MSG(ha._data != NULL, "data should not be NULL");
  TEST_ASSERT_MSG(ha.size == 0, "size should be 0");
  stack_arena_destroy(&ha);
  TEST_ASSERT_MSG(ha._data != NULL, "data should be NULL");
  TEST_ASSERT_MSG(ha.size == 0, "size should be 0");
TEST_CASE_END(DefaultArenaInitializationAndDestruction)


TEST_CASE_BEGIN(ArenaReturnNullWhenFull)
  StackArena ha = stack_arena_create();
  char *ptr = stack_arena_alloc(&ha, STACK_ARENA_SIZE);
  TEST_ASSERT_MSG(ptr != NULL, "ptr should not be NULL");
  TEST_ASSERT_MSG(ha.size == STACK_ARENA_SIZE, "size should be 1024");
  ptr = stack_arena_alloc(&ha, 1);
  TEST_ASSERT_MSG(ptr == NULL, "ptr should be NULL");
  TEST_ASSERT_MSG(ha.size == STACK_ARENA_SIZE, "size should be 1024");
  stack_arena_destroy(&ha);
  TEST_ASSERT_MSG(ha.size == 0, "size should be 0");
TEST_CASE_END(ArenaReturnNullWhenFull)



TESTER_START(TestStackArena)
  RUN_TEST_CASE(DefaultArenaInitializationAndDestruction)
  RUN_TEST_CASE(ArenaReturnNullWhenFull)
TESTER_END(TestStackArena)

