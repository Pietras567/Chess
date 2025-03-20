#include <memory>
#include <iostream>
#include "model/Pawn.h"
#include "model/Square.h"
#include "model/HumanPlayer.h"
#include "model/Board.h"
#include <string>
#include "../exceptions/PieceException.h"
//
// Created by Piotr on 10.05.2023.
//
Pawn::Pawn(const PlayerPtr &player) : Piece(player) {}

Pawn::~Pawn() {

}

std::string Pawn::getPieceInfo() {
    return "\nPiece: Pawn\n"+Piece::getPieceInfo();
}

std::vector<MovePtr> Pawn::calculateAvailableMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory) {
    return Piece::getPawnMoves(board1,moveHistory);
}


std::vector<MovePtr> Piece::getPawnMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory) {
    if(board1== nullptr){
        throw PieceException("Piece::getPawnMoves: board is nullptr");
    }
    std::vector<MovePtr> availableMoves;
    MovePtr move;
    int direction=getDirection();
    int x=getSquare()->getX();
    int y=getSquare()->getY();
    SquarePtr twoSquares;
    if(getPlayer()->isWhite() && getSquare()->getY()==6){
        twoSquares = board1->getSquares(x, y + (2 * direction));
    } else if(!getPlayer()->isWhite() && getSquare()->getY()==1){
        twoSquares = board1->getSquares(x, y + (2 * direction));
    }

    SquarePtr oneSquare = board1->getSquares(x, y + direction);
    if( !oneSquare){
        return availableMoves;
    }

    if(moveHistory.empty()){
        move=std::make_shared<Move>(shared_from_this(), oneSquare);
        availableMoves.push_back(move);
        move=std::make_shared<Move>(shared_from_this(), twoSquares);
        availableMoves.push_back(move);
        return availableMoves;
    }

    if( !oneSquare->getPiece()){
        move=std::make_shared<Move>(shared_from_this(), oneSquare);
        availableMoves.push_back(move);
    }
    SquarePtr rightLeftSquare;
    for (int j = -1; j < 2; j+=2) { //czy mozna zbic przeciwnego pionka
        if(board1->getSquares(x+j, y+direction ) && board1->getSquares(x+j, y+direction )->getPiece() && board1->getSquares(x+j, y+direction )->getPiece()->getPlayer()!=getPlayer()){
            move=std::make_shared<Move>(shared_from_this(), board1->getSquares(x+j, y+direction) ); // pola wzgledem pionka: (x+1 lub x-1),y+1
            availableMoves.push_back(move);

        }
        rightLeftSquare = board1->getSquares(x + (direction*j), y );
        //sprawdz czy jest pionek przeciwnika po prawej/lewej
        if(rightLeftSquare && std::dynamic_pointer_cast<Pawn>(rightLeftSquare->getPiece()) && rightLeftSquare->getPiece()->getPlayer() != getPlayer() ){
            //sprawdz czy jest w historii i ruszyl sie o 2
            if (rightLeftSquare->getPiece() == moveHistory.back()->getPiece() && abs(moveHistory.back()->getDestination()->getY() - moveHistory.back()->getOldSquare()->getY() ) == 2 ){
                move=std::make_shared<Move>(shared_from_this(), board1->getSquares(x+1, y+direction) );
                availableMoves.push_back(move);
            }
        }
    }

//    for (int i = 0; i < moveHistory.size(); ++i) {
//        if(moveHistory.at(i)->getPiece()==shared_from_this()){
//            return availableMoves;
//        }
//    }
    if( twoSquares && !twoSquares->getPiece() && !oneSquare->getPiece()){
        move=std::make_shared<Move>(shared_from_this(),twoSquares);
        availableMoves.push_back(move);
    }
    return availableMoves;
}



const std::string &Pawn::getUnicodeWhite() const {
    return unicodeWhite;
}

const std::string &Pawn::getUnicodeBlack() const {
    return unicodeBlack;
}

void Pawn::showPieceImageWhite() {
    setlocale(LC_CTYPE,"");
    std::string a= getUnicodeWhite();
    std::cout << a;
}

void Pawn::showPieceImageBlack() {
    setlocale(LC_CTYPE,"");
    std::string a= getUnicodeBlack();
    std::cout << a;
}

std::string Pawn::getClassName() {
    return "Pawn";
}