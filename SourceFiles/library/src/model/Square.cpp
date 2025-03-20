
#include <iostream>
#include "model/Square.h"
#include "model/Piece.h"
#include "sstream"
Square::Square(int x, int y, const PiecePtr &piece) : x(x), y(y){}

int Square::getX() const {
    return x;
}

int Square::getY() const {
    return y;
}

const PiecePtr &Square::getPiece() const {
    return piece;
}

void Square::setPiece(const PiecePtr &piecePtr) {
    Square::piece = piecePtr;
    if (piece!= nullptr && piece->getSquare()!=shared_from_this()){
        piece->setSquare(shared_from_this());
    }

}

Square::~Square() {

}

std::string Square::getSquareInfo() { //sstream test
    std::ostringstream os;
    os << " x: " << x << " y: " <<y << " piece: " << (piece!= nullptr ? piece->getPieceInfo(): " none" );
    return os.str();
}

