#ifndef COMMON_H_
#define COMMON_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum boolean{
    FALSE,
    TRUE
}bool_t;

typedef enum colors{
    CURRENT = 30,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    GREY,
    CYAN,
    WHITE
} color_t;

typedef enum effects{
    NONE,
    BOLD,
    DARKNESS,
    ITALIC,
    UNDERLINE,
    BLINK,
    BLINK2,
    HIGHTLIGHT,
    MASK,
    STRIKETHROUGH
} effect_t;

void my_fprintf(FILE* stream, color_t color, effect_t effect, bool_t newline, char* format, ...);

#endif