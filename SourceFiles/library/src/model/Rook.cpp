//
// Created by Piotr on 10.05.2023.
//
#include <string>
#include "model/Rook.h"
#include <iostream>

Rook::Rook(const PlayerPtr &player) : Piece(player) {}

const std::string &Rook::getUnicodeWhite() const {
    return unicodeWhite;
}

const std::string &Rook::getUnicodeBlack() const {
    return unicodeBlack;
}

void Rook::showPieceImageWhite() {
    setlocale(LC_CTYPE,"");
    std::string a= getUnicodeWhite();
    std::cout << a;
}

void Rook::showPieceImageBlack() {
    setlocale(LC_CTYPE,"");
    std::string a= getUnicodeBlack();
    std::cout << a;
}

Rook::~Rook() {
}

std::string Rook::getPieceInfo() {
    return "\nPiece: Rook: "+Piece::getPieceInfo();
}

std::vector<MovePtr> Rook::calculateAvailableMoves(const BoardPtr &board1, const std::vector<MovePtr> &moveHistory) {
    std::vector<MovePtr> horizontal= getHorizontalMoves(board1,moveHistory);
    std::vector<MovePtr> vertical= getVerticalMoves(board1,moveHistory);
    horizontal.insert(horizontal.end(),std::make_move_iterator(vertical.begin()),std::make_move_iterator(vertical.end()));//laczenie wektorow
    return horizontal;
}

std::string Rook::getClassName() {
    return "Rook";
}

