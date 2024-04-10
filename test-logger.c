#define DEBUG
#include "logger.h"
int main() {
  const char *msg = "Hello, world!";
  LOG_INFO("%s", msg);
  LOG_ERROR("Hello, world!");
  LOG_WARN("Hello, world!");
  LOG_DEBUG("Hello, world!");
  LOG_CUSTOM("CUSTOM", "Hello?");
  LOG_CUSTOM("CUSTOM RED", "%s WAT? %s", LOG_COLOR_RED, LOG_COLOR_RESET);
  return 0;
}
