#include "error.h"

void put_error(errtype err, int32_t line, int32_t column, int8_t *format, ...){
    if (err == ERROR)
        fprintf(stderr, "[ERROR]:");
    else if (err == WARNING)
        fprintf(stderr, "[WARNING]:");

    if (line>0 || column>0)
        fprintf(stderr, " in");
    
    if (line > 0)
        fprintf(stderr, " line %d", line);
    if (column > 0)
        fprintf(stderr, " column %d", column);
    
    if (line>0 || column>0)
        fprintf(stderr, ",");
    
    va_list arg;
    
    va_start(arg, format);
    
    int8_t note[256];
    vsnprintf(note, 256, format, arg);
    
    va_end(arg);
    
    fprintf(stderr, " %s\n", note);
    
    return;
    
}
