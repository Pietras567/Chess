
#include "model/PawnFactory.h"
#include "model/Pawn.h"

PiecePtr PawnFactory::create(PlayerPtr player) {
    return std::make_shared<Pawn>(player);
}
