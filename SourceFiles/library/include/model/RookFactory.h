
#ifndef CHESSPROJECT_ROOKFACTORY_H
#define CHESSPROJECT_ROOKFACTORY_H
#include "PieceFactory.h"

class RookFactory: public PieceFactory{
public:
    PiecePtr create(PlayerPtr player) override;

};


#endif //CHESSPROJECT_ROOKFACTORY_H
