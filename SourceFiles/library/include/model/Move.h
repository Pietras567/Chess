//
// Created by Piotr on 10.05.2023.
//

#ifndef SOURCEFILES_MOVE_H
#define SOURCEFILES_MOVE_H
#include "typedefs.h"
class Piece;
class Square;
class Move {
    PiecePtr piece;
    SquarePtr oldSquare;
    SquarePtr destination;
public:
    Move(const PiecePtr &piece, const SquarePtr &destination);

    //bool isValid();

    const PiecePtr &getPiece() const;

    const SquarePtr &getOldSquare() const;

    const SquarePtr &getDestination() const;



    virtual ~Move();


};

#endif //SOURCEFILES_MOVE_H
