
#ifndef CHESSPROJECT_KNIGHTFACTORY_H
#define CHESSPROJECT_KNIGHTFACTORY_H

#include "PieceFactory.h"

class KnightFactory : public PieceFactory{
public:
    PiecePtr create(PlayerPtr player) override;
};


#endif //CHESSPROJECT_KNIGHTFACTORY_H
