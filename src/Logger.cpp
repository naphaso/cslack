//
// Created by Stanislav on 06/01/16.
//

#include "Logger.h"
#include <stdarg.h>

Logger::Logger(const char *file) {
    _fd = fopen(file, "a");
}

void Logger::log(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(_fd, format, args);
    va_end(args);
    fflush(_fd);
}

Logger::~Logger() {
    fclose(_fd);
}
