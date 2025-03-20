//
// Created by Piotr on 10.05.2023.
//
#include "typedefs.h"
#include "model/Bishop.h"
#include <string>
#include "model/Bishop.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <ios>
#include <fcntl.h>
#include <iomanip>
#include <locale>
Bishop::Bishop(const PlayerPtr &player) : Piece(player) {}

Bishop::~Bishop() {

}

std::string Bishop::getPieceInfo() {
    return "\nPiece: Bishop \n"+Piece::getPieceInfo();
}

std::vector<MovePtr> Bishop::calculateAvailableMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory) {
    return Piece::getDiagonalMoves(board1,moveHistory);
}

const std::string &Bishop::getUnicodeWhite() const {
    return unicodeWhite;
}

const std::string &Bishop::getUnicodeBlack() const {
    return unicodeBlack;
}

void Bishop::showPieceImageWhite() {
    setlocale(LC_CTYPE,"");
    std::string a= getUnicodeWhite();
    std::cout << a;
}

void Bishop::showPieceImageBlack() {
    setlocale(LC_CTYPE,"");
    std::string a= getUnicodeBlack();
    std::cout << a;
}

std::string Bishop::getClassName() {
    return "Bishop";
}
