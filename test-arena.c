#define ARENA_IMPL
#include "arena.h"
#include "tester.h"



TEST_CASE_BEGIN(DefaultArenaInitializationAndDestruction)
  HeapArena ha = heap_arena_create(10, false);
  TEST_ASSERT_MSG(ha._data != NULL, "data should not be NULL");
  TEST_ASSERT_MSG(ha.size == 0, "size should be 0");
  TEST_ASSERT_MSG(ha.cap == 10, "cap should be 10");
  TEST_ASSERT_MSG(ha.growable == false, "growable should be false");
  heap_arena_destroy(&ha);
  TEST_ASSERT_MSG(ha._data == NULL, "data should be NULL");
  TEST_ASSERT_MSG(ha.size == 0, "size should be 0");
  TEST_ASSERT_MSG(ha.cap == 0, "cap should be 0");
  TEST_ASSERT_MSG(ha.growable == false, "growable should be false");
TEST_CASE_END(DefaultArenaInitializationAndDestruction)


TEST_CASE_BEGIN(ArenaCanBeInitializedWithZeroSize)
  HeapArena ha = heap_arena_create(0, false);
  TEST_ASSERT_MSG(ha._data != NULL, "data should not be NULL");
  TEST_ASSERT_MSG(ha.size == 0, "size should be 0");
  TEST_ASSERT_MSG(ha.cap == 0, "cap should be 0");
  TEST_ASSERT_MSG(ha.growable == false, "growable should be false");
  heap_arena_destroy(&ha);
  TEST_ASSERT_MSG(ha._data == NULL, "data should be NULL");
  TEST_ASSERT_MSG(ha.size == 0, "size should be 0");
  TEST_ASSERT_MSG(ha.cap == 0, "cap should be 0");
  TEST_ASSERT_MSG(ha.growable == false, "growable should be false");
TEST_CASE_END(ArenaCanBeInitializedWithZeroSize)


TEST_CASE_BEGIN(ArenaCanGrow)
  HeapArena ha = heap_arena_create(10, true);
  char *ptr = heap_arena_alloc(&ha, 5);
  TEST_ASSERT_MSG(ptr != NULL, "ptr should not be NULL");
  TEST_ASSERT_MSG(ha.size == 5, "size should be 5");
  TEST_ASSERT_MSG(ha.cap == 10, "cap should be 10");
  ptr = heap_arena_alloc(&ha, 5);
  TEST_ASSERT_MSG(ptr != NULL, "ptr should not be NULL");
  TEST_ASSERT_MSG(ha.size == 10, "size should be 10");
  TEST_ASSERT_MSG(ha.cap == 10, "cap should be 10");
  ptr = heap_arena_alloc(&ha, 5);
  TEST_ASSERT_MSG(ptr != NULL, "ptr should not be NULL");
  TEST_ASSERT_MSG(ha.size == 15, "size should be 15");
  TEST_ASSERT_MSG(ha.cap == 20, "cap should be 20");
  heap_arena_destroy(&ha);
  TEST_ASSERT_MSG(ha._data == NULL, "data should be NULL");
  TEST_ASSERT_MSG(ha.size == 0, "size should be 0");
  TEST_ASSERT_MSG(ha.cap == 0, "cap should be 0");
  TEST_ASSERT_MSG(ha.growable == false, "growable should be false");
TEST_CASE_END(ArenaCanGrow)


TEST_CASE_BEGIN(ArenaReturnNullWhenNotGrowableAndFull)
  HeapArena ha = heap_arena_create(10, false);
  char *ptr = heap_arena_alloc(&ha, 10);
  TEST_ASSERT_MSG(ptr != NULL, "ptr should not be NULL");
  TEST_ASSERT_MSG(ha.size == 10, "size should be 10");
  TEST_ASSERT_MSG(ha.cap == 10, "cap should be 10");
  ptr = heap_arena_alloc(&ha, 1);
  TEST_ASSERT_MSG(ptr == NULL, "ptr should be NULL");
  TEST_ASSERT_MSG(ha.size == 10, "size should be 10");
  TEST_ASSERT_MSG(ha.cap == 10, "cap should be 10");
  heap_arena_destroy(&ha);
  TEST_ASSERT_MSG(ha._data == NULL, "data should be NULL");
  TEST_ASSERT_MSG(ha.size == 0, "size should be 0");
  TEST_ASSERT_MSG(ha.cap == 0, "cap should be 0");
  TEST_ASSERT_MSG(ha.growable == false, "growable should be false");
TEST_CASE_END(ArenaReturnNullWhenNotGrowableAndFull)



TESTER_START(TestArena)
  RUN_TEST_CASE(DefaultArenaInitializationAndDestruction)
  RUN_TEST_CASE(ArenaCanBeInitializedWithZeroSize)
  RUN_TEST_CASE(ArenaCanGrow)
  RUN_TEST_CASE(ArenaReturnNullWhenNotGrowableAndFull)
TESTER_END(TestArena)
