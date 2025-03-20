
#include "model/RookFactory.h"
#include "model/Rook.h"
PiecePtr RookFactory::create(PlayerPtr player) {
    return std::make_shared<Rook>(player);
}
