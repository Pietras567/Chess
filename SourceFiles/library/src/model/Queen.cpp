#include <memory>
#include "model/Piece.h"
#include "model/Queen.h"
#include <string>
#include <iostream>
//
// Created by Piotr on 10.05.2023.
//
Queen::Queen(const PlayerPtr &player) : Piece(player) {}

const std::string &Queen::getUnicodeWhite() const {
    return unicodeWhite;
}

const std::string &Queen::getUnicodeBlack() const {
    return unicodeBlack;
}

void Queen::showPieceImageWhite() {
    setlocale(LC_CTYPE,"");
    std::string a= getUnicodeWhite();
    std::cout << a;
}

void Queen::showPieceImageBlack() {
    setlocale(LC_CTYPE,"");
    std::string a= getUnicodeBlack();
    std::cout << a;
}

Queen::~Queen() {}

std::string Queen::getPieceInfo() {
    return "\nPiece: Queen\n"+Piece::getPieceInfo();
}

std::vector<MovePtr> Queen::calculateAvailableMoves(const BoardPtr &board1, const std::vector<MovePtr> &moveHistory) {
    std::vector<MovePtr> horizontal= getHorizontalMoves(board1,moveHistory);
    std::vector<MovePtr> vertical= getVerticalMoves(board1,moveHistory);
    std::vector<MovePtr> diagonal= getDiagonalMoves(board1,moveHistory);
    //laczenie wektorow horizontal=horizontal+vertical+diagonal
    horizontal.insert(horizontal.end(),std::make_move_iterator(vertical.begin()),std::make_move_iterator(vertical.end()));
    horizontal.insert(horizontal.end(),std::make_move_iterator(diagonal.begin()),std::make_move_iterator(diagonal.end()));
    return horizontal;
}

std::string Queen::getClassName() {
    return "Queen";
}