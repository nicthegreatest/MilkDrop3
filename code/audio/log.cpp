// log.cpp

#include "log.h"
#include <stdarg.h>

void LOG(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    printf("\n");
    va_end(args);
}

void ERR(const char* format, ...) {
    fprintf(stderr, "Error: ");
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}