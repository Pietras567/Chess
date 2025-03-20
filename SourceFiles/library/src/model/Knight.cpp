//
// Created by student on 31.05.23.
//

#include "model/Knight.h"
#include "model/Square.h"
#include <string>
#include "model/Knight.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <ios>
#include <fcntl.h>
#include <iomanip>
#include <locale>
Knight::Knight(const PlayerPtr &player) : Piece(player) {}

Knight::~Knight() {

}


std::string Knight::getPieceInfo() {
    return "\nPiece: Knight \n"+Piece::getPieceInfo();
}

std::vector<MovePtr> Knight::calculateAvailableMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory) {
    return Piece::getLshapedMoves(board1,moveHistory);
}


const std::string &Knight::getUnicodeWhite() const {
    return unicodeWhite;
}

const std::string &Knight::getUnicodeBlack() const {
    return unicodeBlack;
}

void Knight::showPieceImageWhite() {
    setlocale(LC_CTYPE,"");
    std::string a= getUnicodeWhite();
    std::cout << a;
}

void Knight::showPieceImageBlack() {
    setlocale(LC_CTYPE,"");
    std::string a= getUnicodeBlack();
    std::cout << a;
}

std::string Knight::getClassName() {
    return "Knight";
}