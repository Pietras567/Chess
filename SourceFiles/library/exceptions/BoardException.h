#ifndef CARRENTAL_BOARDEXCEPTION_H
#define CARRENTAL_BOARDEXCEPTION_H
#include "iostream"

class BoardException : public std::logic_error{
public:
    explicit BoardException(const std::string &arg) : logic_error(arg) {}
};


#endif //CARRENTAL_VEHICLEEXCEPTION_H
