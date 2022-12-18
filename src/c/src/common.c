#include <pthread.h>
#include <stdarg.h>
#include "../lib/common.h"

void my_fprintf(FILE* stream, color_t color, effect_t effect, bool_t newline, char* format, ...){
    va_list args;
    va_start(args, format);

    fprintf(stream, "\033[%i;%im", effect, color);
    vfprintf(stream, format, args);
    fprintf(stream, "\033[0m");
    if(newline) fprintf(stream, "\n");

    va_end(args);
    fflush(stream);
}