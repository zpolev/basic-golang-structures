#ifndef LOG_H
#define LOG_H
#include <stdio.h>

typedef enum { LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR } LogLevel;

#define LOG(level, fmt, ...)                                                   \
  fprintf(stderr, "[%s] %s:%d: " fmt "\n", log_level_str(level), __FILE__,     \
          __LINE__, ##__VA_ARGS__)

const char *log_level_str(LogLevel l);
#endif
