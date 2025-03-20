
#ifndef CHESSPROJECT_PAWNFACTORY_H
#define CHESSPROJECT_PAWNFACTORY_H

#include "PieceFactory.h"

class PawnFactory: public PieceFactory {
public:
    PiecePtr create(PlayerPtr player) override;
};


#endif //CHESSPROJECT_PAWNFACTORY_H
