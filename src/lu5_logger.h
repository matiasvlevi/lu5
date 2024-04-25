#ifndef __LU5_LOGGER_H__
#define __LU5_LOGGER_H__

typedef enum {
    LU5_ERROR_LOG,
    LU5_NONE_LOG,
    LU5_RUN_LOG,
    LU5_INFO_LOG,
    LU5_WARN_LOG
} lu5_log_level;

#include <lua.h>

void lu5_logger_trace(lua_State *L);
void lu5_logger_print(lu5_log_level level, const char* fmt, ...);

#define LU5_ERROR(msg, ...)   lu5_logger_print(LU5_ERROR_LOG, msg, ##__VA_ARGS__);
#define LU5_WARN(msg, ...)    lu5_logger_print(LU5_WARN_LOG , msg, ##__VA_ARGS__)
#define LU5_INFO(msg, ...)    lu5_logger_print(LU5_INFO_LOG , msg, ##__VA_ARGS__)
#define LU5_RUN_LOG(msg, ...) lu5_logger_print(LU5_RUN_LOG  , msg, ##__VA_ARGS__)
#define LU5_LOG(msg, ...)     lu5_logger_print(LU5_NONE_LOG , msg, ##__VA_ARGS__)

#define LU5_ERROR_TRACE(l, msg, ...)\
    LU5_ERROR(msg, ##__VA_ARGS__);\
    lu5_logger_trace(l);

#define LU5_WARN_TRACE(l, msg, ...)\
    LU5_WARN(msg, ##__VA_ARGS__);\
    lu5_logger_trace(l);

#define LU5_TRACE(l)   lu5_logger_trace(l);

#define LU5_FILE_NOT_SPECIFIED\
    "No source path found"

#define LU5_NO_WINDOW\
    "You need to create a window with the `createWindow` function"

#define LU5_INVALID_WINDOW\
    "Window was created, but GLFWwindow ptr is NULL"

#define LU5_EXIT_APP\
    "Terminating..."

#endif
