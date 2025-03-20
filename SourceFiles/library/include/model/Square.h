
#ifndef CARRENTAL_SQUARE_H
#define CARRENTAL_SQUARE_H

#include <ostream>
#include "typedefs.h"
#include "string"
class Square: public std::enable_shared_from_this<Square>{
    int x;
    int y;
    PiecePtr piece;
public:
    Square(int x, int y, const PiecePtr &piece);

    int getX() const;

    int getY() const;

    const PiecePtr &getPiece() const;

    void setPiece(const PiecePtr &piecePtr);

    virtual ~Square();
    std::string getSquareInfo();
};


#endif //CARRENTAL_SQUARE_H
