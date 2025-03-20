#ifndef CARRENTAL_PIECEEXCEPTION_H
#define CARRENTAL_PIECEEXCEPTION_H
#include <iostream>

class PieceException : public std::logic_error{
public:
    explicit PieceException(const std::string &arg) : logic_error(arg) {}

};
#endif //CARRENTAL_RENTEXCEPTION_H
