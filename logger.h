#ifndef _LOGGER_
#define _LOGGER_
#include <stdio.h>
#define LOG_COLOR_RED "\033[0;31m"
#define LOG_COLOR_GREEN "\033[0;32m"
#define LOG_COLOR_YELLOW "\033[1;33m"
#define LOG_COLOR_RESET "\033[0m"

#define LOG_TO_FILE(file, ...) fprintf(file, __VA_ARGS__)

#define LOG_INFO(...)                                                          \
  LOG_TO_FILE(stdout, LOG_COLOR_GREEN);                                        \
  LOG_TO_FILE(stdout, "[INFO]: ");                                             \
  LOG_TO_FILE(stdout, __VA_ARGS__);                                            \
  LOG_TO_FILE(stdout, LOG_COLOR_RESET);                                       \
  LOG_TO_FILE(stdout, "\n")
#define LOG_ERROR(...)                                                         \
  LOG_TO_FILE(stderr, LOG_COLOR_RED);                                          \
  LOG_TO_FILE(stderr, "[ERROR]: ");                                            \
  LOG_TO_FILE(stderr, __VA_ARGS__);                                            \
  LOG_TO_FILE(stderr, LOG_COLOR_RESET);                                       \
  LOG_TO_FILE(stderr, "\n")
#define LOG_WARN(...)                                                          \
  LOG_TO_FILE(stdout, LOG_COLOR_YELLOW);                                       \
  LOG_TO_FILE(stdout, "[WARN]: ");                                             \
  LOG_TO_FILE(stdout, __VA_ARGS__);                                            \
  LOG_TO_FILE(stdout, LOG_COLOR_RESET);                                       \
  LOG_TO_FILE(stdout, "\n")
#define LOG_CUSTOM_F(file, prefix, ...)                                        \
  LOG_TO_FILE(file, "[%s]: ", prefix);                                         \
  LOG_TO_FILE(file, __VA_ARGS__);                                              \
  LOG_TO_FILE(file, "\n")
#define LOG_CUSTOM(prefix, ...) LOG_CUSTOM_F(stdout, prefix, __VA_ARGS__)

#ifdef DEBUG
#define LOG_DEBUG(...)                                                         \
  LOG_TO_FILE(stdout, "[DEBUG]: ");                                            \
  LOG_TO_FILE(stdout, __VA_ARGS__);                                            \
  LOG_TO_FILE(stdout, "\n")
#else
#define LOG_DEBUG(...)
#endif

#endif
