#include "log.h"

const char *log_level_str(LogLevel l) {
  switch (l) {
  case LOG_DEBUG:
    return "DEBUG";
  case LOG_INFO:
    return "INFO";
  case LOG_WARN:
    return "WARN";
  case LOG_ERROR:
    return "ERROR";
  default:
    return "?";
  }
}
