
#ifndef CHESSPROJECT_BISHOPFACTORY_H
#define CHESSPROJECT_BISHOPFACTORY_H

#include "PieceFactory.h"
class BishopFactory : public PieceFactory{
public:
    PiecePtr create(PlayerPtr player) override;
};


#endif //CHESSPROJECT_BISHOPFACTORY_H
