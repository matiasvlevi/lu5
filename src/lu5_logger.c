#include "lu5_logger.h"

#include "lu5_state.h"

#include <stdio.h>
#include <stdarg.h>

void lu5_logger_trace(lua_State *L) {
    lua_getglobal(L, "debug");
    if (lua_istable(L, -1)) {
        lua_getfield(L, -1, "traceback");
        if (lua_isfunction(L, -1)) {
            // Call debug.traceback() with 0 arguments and 1 result
            lua_call(L, 0, 1);

            // Print result
            printf("%s\n", lua_tostring(L, -1));

            // Pop the result and debug table
            lua_pop(L, 2); 
        } else {
            // Non-function or non-existence of debug table
            lua_pop(L, 2); 
        }
    } else {
        // Clean up the global state stack
        lua_pop(L, 1); 
    }
}

void lu5_logger_print(lu5_log_level level, const char* fmt, ...) 
{
    if (level > lu5.log_level) return;

    va_list args;
    va_start(args, fmt);

    FILE *out = stdout;

    switch(level) {
        case LU5_INFO_LOG:
            printf("\x1b[30;44m Info \x1b[0m ");
            break;

        case LU5_RUN_LOG:
            printf("\x1b[30;46m Running >>> \x1b[0m ");
            break;

        case LU5_ERROR_LOG:
            out = stderr;
            fprintf(out, "\x1b[30;41m ERROR \x1b[0m ");
            break;

        case LU5_WARN_LOG:
            out = stderr;
            fprintf(out, "\x1b[30;43m WARN \x1b[0m ");
            break;

        default: break;
    }

    vfprintf(out, fmt, args);
    fputc('\n', out);
    
    va_end(args);
}
