#include "lu5_types.h"

#include <lualib.h>
#include <lauxlib.h>
#include "lu5_state.h"

LU5_TYPE_BIND(lua_Number  , number);
LU5_TYPE_BIND(lua_Integer , integer);
LU5_TYPE_BIND(const char *, string);

#ifdef WIN32
#define LU5_SIZEOF_FMT "%lli"
#else
#define LU5_SIZEOF_FMT "%li"
#endif

void lu5_log_types() 
{
	if (LU5_DEBUG_LOG <= lu5.log_level) 
	{
		fputs("number: ", stdout);
		switch(LUA_FLOAT_TYPE) {
			case LUA_FLOAT_FLOAT: fputs("float", stdout); break;
			case LUA_FLOAT_DOUBLE: fputs("double", stdout); break;
			case LUA_FLOAT_LONGDOUBLE: fputs("long double", stdout); break;
			default: fputs("unknown", stdout); break;
		}
		
		printf(" (" LU5_SIZEOF_FMT " bytes)\n", sizeof(lua_Number));

		fputs("integer: ", stdout);
		switch(LUA_INT_TYPE) {
			case LUA_INT_INT: fputs("int", stdout); break;
			case LUA_INT_LONG: fputs("long", stdout); break;
			case LUA_INT_LONGLONG: {
				if (sizeof(long) == sizeof(long long)) 
				{
					fputs("long", stdout);
				} 
				else 
				{
					fputs("long long", stdout);
				} 
				break;
			}
			default: fputs("unknown", stdout); break;
		}
		printf(" (" LU5_SIZEOF_FMT  " bytes)\n", sizeof(lua_Integer));

	}
}