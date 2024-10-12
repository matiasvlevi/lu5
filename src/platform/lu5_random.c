#include "../lu5_random.h"
#include <time.h>

lua_Integer lu5_time_seed(void) 
{
    lua_Integer seed = (lua_Integer)time(NULL) ^ (lua_Integer)clock();

    return seed << (seed % 8);
}
