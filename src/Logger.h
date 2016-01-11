//
// Created by Stanislav on 06/01/16.
//

#ifndef CSLACK_LOG_H
#define CSLACK_LOG_H


#include <stdio.h>

class Logger {
private:
    FILE *_fd;
public:
    Logger(const char *file);
    ~Logger();
    void log(const char *format, ...);
};


#endif //CSLACK_LOG_H
