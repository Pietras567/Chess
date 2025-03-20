
#ifndef CHESSPROJECT_PIECEFACTORY_H
#define CHESSPROJECT_PIECEFACTORY_H

#include "../typedefs.h"

class PieceFactory{
public:
    virtual PiecePtr create(PlayerPtr player)=0;
};


#endif //CHESSPROJECT_PIECEFACTORY_H

