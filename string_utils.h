#ifndef _STRING_UTILS_
#define _STRING_UTILS_

#include <stddef.h>
#include <stdint.h>


typedef struct {
  char *data;
  size_t size;
  size_t cursor;
  char separator;
} StringView;

StringView sv_create(char *data, size_t size);
StringView sv_create_from_cstr(char *cstr);
StringView sv_next_word(StringView *sv);
char *sv_to_cstr(StringView *sv);
void sv_destroy(StringView *sv);
StringView sv_substr(StringView *sv, size_t start, size_t end);

typedef struct {
  char *data;
  size_t size;
  size_t cap;
} StringBuilder;

StringBuilder sb_create(size_t initial_cap);
void sb_destroy(StringBuilder *sb);
void sb_append(StringBuilder *sb, char *data, size_t size);
void sb_append_cstr(StringBuilder *sb, char *cstr);
void sb_append_char(StringBuilder *sb, char c);
void sb_clear(StringBuilder *sb);
#endif

#ifdef STRING_UTILS_IMPL

char *sv_to_cstr(StringView *sv) {
  char *cstr = (char *)malloc(sv->size + 1);
  size_t i = 0;
  for (; i < sv->size; i++) {
    cstr[i] = sv->data[i];
  }
  cstr[i] = '\0';
  return cstr;
}

void sv_destroy(StringView *sv) {
  sv->data = NULL;
  sv->size = 0;
  sv->cursor = 0;
  sv->separator = ' ';
}
StringView sv_next_word(StringView *sv) {
  size_t start = sv->cursor;
  while (sv->cursor < sv->size && sv->data[sv->cursor] != sv->separator) {
    sv->cursor++;
  }
  size_t end = sv->cursor - 1;
  if (sv->cursor < sv->size) {
    sv->cursor++;
  }
  return sv_substr(sv, start, end);
}

StringView sv_create(char *data, size_t size) {
  StringView sv = {.data = data, .size = size, .cursor = 0, .separator = ' '};
  return sv;
}

StringView sv_create_from_cstr(char *cstr) {
  size_t size = 0;
  while (cstr[size] != '\0') {
    size++;
  }
  return sv_create(cstr, size);
}

StringView sv_substr(StringView *sv, size_t start, size_t end) {
  if (start >= sv->size || end >= sv->size || start > end) {
    return sv_create(NULL, 0);
  }
  return sv_create(sv->data + start, end - start + 1);
}

#endif
