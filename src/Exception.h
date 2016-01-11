//
// Created by Stanislav on 09/01/16.
//

#ifndef CSLACK_EXCEPTION_H
#define CSLACK_EXCEPTION_H


#include <string>

class Exception {
private:
    std::string _message;
public:
    Exception(const std::string& message) : _message(message) {}
};


#endif //CSLACK_EXCEPTION_H
