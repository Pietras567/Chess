
#include "model/BishopFactory.h"
#include "model/Bishop.h"
PiecePtr BishopFactory::create(PlayerPtr player) {
    return std::make_shared<Bishop>(player);
}
