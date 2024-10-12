#ifndef __LU5_ERROR__
#define __LU5_ERROR__

#include "./lu5_logger.h"

#define LU5_ERROR(msg, ...) lu5_logger_print(LU5_ERROR_LOG, msg, ##__VA_ARGS__);

#endif