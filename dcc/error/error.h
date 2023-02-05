#ifndef __ERROR_H__

#define __ERROR_H__

#include "../global.h"

void put_error(errtype err, int32_t line, int32_t column, int8_t *format, ...);

#endif
