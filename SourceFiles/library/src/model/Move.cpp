#include "model/Move.h"
#include "model/Piece.h"
#include "model/Square.h"
#include "typedefs.h"

Move::Move(const PiecePtr &piece, const SquarePtr &destination) : piece(piece), destination(destination) {
    oldSquare=piece->getSquare();

}

const PiecePtr &Move::getPiece() const {
    return piece;
}

const SquarePtr &Move::getOldSquare() const {
    return oldSquare;
}
//bool Move::move(PiecePtr piece, SquarePtr square) {
//    if(isValid(piece, square)) {
//        piece->setSquare(square);
//        return true;
//    }
//    return false;
//}

//bool Move::isValid() {
//    for(int i = 0; i < piece->getAvailableMoves().size(); i++) {
//        if(piece->getAvailableMoves().at(i)==destination)
//            return true;
//        }
//    return false;
//}

const SquarePtr &Move::getDestination() const {
    return destination;
}

Move::~Move() {

}





