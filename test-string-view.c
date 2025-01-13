/*
*  functions to test here:
*
*StringView sv_create(char *data, size_t size);
*StringView sv_create_from_cstr(char *cstr);
*char sv_at(StringView *sv, size_t index);
*StringView sv_substr(StringView *sv, size_t start, size_t end);
*int sv_compare(StringView *sv1, StringView *sv2);
*int sv_find(StringView *sv, StringView *substr);
*int sv_find_cstr(StringView *sv, char* substr);
*int sv_find_char(StringView *sv, char c);
*StringView sv_next_word(StringView *sv);
*char *sv_to_cstr(StringView *sv);
//*/

#include <string.h>
#define STRING_UTILS_IMPL
#include "string_utils.h"
#include "tester.h"

TEST_CASE_BEGIN(DefaultSVInitializationAndDestruction)
    StringView sv = sv_create(NULL, 0);
    TEST_ASSERT_MSG(sv.data == NULL, "data should be NULL");
    TEST_ASSERT_MSG(sv.size == 0, "size should be 0");
    TEST_ASSERT_MSG(sv.cursor == 0, "cursor should be 0");
    TEST_ASSERT_MSG(sv.separator == ' ', "separator should be ' '");
    sv_destroy(&sv);
    TEST_ASSERT_MSG(sv.data == NULL, "data should be NULL");
    TEST_ASSERT_MSG(sv.size == 0, "size should be 0");
    TEST_ASSERT_MSG(sv.cursor == 0, "cursor should be 0");
    TEST_ASSERT_MSG(sv.separator == ' ', "separator should be ' '");
    char s[] = "hello";
    sv = sv_create(s, 5);
    TEST_ASSERT_MSG(sv.data != NULL, "data should not be NULL");
    TEST_ASSERT_MSG(sv.size == 5, "size should be 5");
    TEST_ASSERT_MSG(sv.cursor == 0, "cursor should be 0");
    TEST_ASSERT_MSG(sv.separator == ' ', "separator should be ' '");
    sv_destroy(&sv);
    TEST_ASSERT_MSG(sv.data == NULL, "data should be NULL");
    TEST_ASSERT_MSG(sv.size == 0, "size should be 0");
    TEST_ASSERT_MSG(sv.cursor == 0, "cursor should be 0");
    TEST_ASSERT_MSG(sv.separator == ' ', "separator should be ' '");
TEST_CASE_END(DefaultSVInitializationAndDestruction)

TEST_CASE_BEGIN(SVCreateFromCstr)
    StringView sv = sv_create_from_cstr("hello");
    TEST_ASSERT_MSG(sv.data != NULL, "data should not be NULL");
    TEST_ASSERT_MSG(sv.size == 5, "size should be 5");
    TEST_ASSERT_MSG(sv.cursor == 0, "cursor should be 0");
    TEST_ASSERT_MSG(sv.separator == ' ', "separator should be ' '");
    sv_destroy(&sv);
    TEST_ASSERT_MSG(sv.data == NULL, "data should be NULL");
    TEST_ASSERT_MSG(sv.size == 0, "size should be 0");
    TEST_ASSERT_MSG(sv.cursor == 0, "cursor should be 0");
    TEST_ASSERT_MSG(sv.separator == ' ', "separator should be ' '");
TEST_CASE_END(SVCreateFromCstr)

TEST_CASE_BEGIN(SVNextWord)
    StringView sv = sv_create_from_cstr("hello world");
    StringView word = sv_next_word(&sv);
    TEST_ASSERT_MSG(word.data != NULL, "data should not be NULL");
    TEST_ASSERT_MSG(strcmp(sv_to_cstr(&word), "hello")==0, "content should be 'hello'");
    TEST_ASSERT_MSG(word.size == 5, "size should be 5");
    TEST_ASSERT_MSG(word.cursor == 0, "cursor should be 0");
    TEST_ASSERT_MSG(word.separator == ' ', "separator should be ' '");
    TEST_ASSERT_MSG(sv.cursor == 6, "cursor should be 6");
    sv_destroy(&word);
    word = sv_next_word(&sv);
    TEST_ASSERT_MSG(word.data != NULL, "data should not be NULL");
    TEST_ASSERT_MSG(strcmp(sv_to_cstr(&word), "world")==0, "content should be 'hello'");
    TEST_ASSERT_MSG(word.size == 5, "size should be 5");
    TEST_ASSERT_MSG(word.cursor == 0, "cursor should be 0");
    TEST_ASSERT_MSG(word.separator == ' ', "separator should be ' '");
    TEST_ASSERT_MSG(sv.cursor == 11, "cursor should be 12");
    sv_destroy(&word);
    word = sv_next_word(&sv);
    TEST_ASSERT_MSG(word.data == NULL, "data should be NULL");
    TEST_ASSERT_MSG(word.size == 0, "size should be 0");
    TEST_ASSERT_MSG(word.cursor == 0, "cursor should be 0");
    TEST_ASSERT_MSG(word.separator == ' ', "separator should be ' '");
    TEST_ASSERT_MSG(sv.cursor == 11, "cursor should be 12");
    sv_destroy(&word);
    sv_destroy(&sv);
TEST_CASE_END(SVNextWord)



TESTER_START(TestStringView)
    RUN_TEST_CASE(DefaultSVInitializationAndDestruction)
    RUN_TEST_CASE(SVCreateFromCstr)
    RUN_TEST_CASE(SVNextWord)
TESTER_END(TestStringView)
