
#include "model/KnightFactory.h"
#include "model/Knight.h"
PiecePtr KnightFactory::create(PlayerPtr player) {
    return std::make_shared<Knight>(player);
}
