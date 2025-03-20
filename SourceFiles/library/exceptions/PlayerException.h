#ifndef CARRENTAL_PLAYEREXCEPTION_H
#define CARRENTAL_PLAYEREXCEPTION_H
#include "iostream"

class PlayerException : public std::logic_error{
public:
    explicit PlayerException(const std::string &arg) : logic_error(arg) {}
};


#endif //CARRENTAL_CLIENTEXCEPTION_H
