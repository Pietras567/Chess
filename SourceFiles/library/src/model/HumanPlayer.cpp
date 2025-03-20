//
// Created by Piotr on 10.05.2023.
//

#include "model/HumanPlayer.h"
#include "model/Piece.h"
#include "model/Square.h"
#include "model/Board.h"
#include "model/Knight.h"
#include "model/Rook.h"
#include "model/Queen.h"
#include "model/Bishop.h"

HumanPlayer::HumanPlayer(const std::string &name, bool white) : Player(name, white) {}

HumanPlayer::~HumanPlayer() {}


MovePtr HumanPlayer::getMove(const BoardPtr &board1, const std::vector<MovePtr> &movesHistory) {
    int x=0,y=0;
    PiecePtr piece;
    SquarePtr square;
    do {
        std::cout<<"\nPodaj wspolrzedne figury : \n";
        std::cout<<"x: ";
        std::cin>>x;
        std::cout<<"y: ";
        std::cin>>y;
        std::cin.sync();
    } while (board1->getSquares(x,y) == nullptr || !board1->getSquares(x,y)->getPiece() || board1->getSquares(x,y)->getPiece()->getPlayer()!=shared_from_this());
    piece=board1->getSquares(x,y)->getPiece();
    //std::cout<<piece->getPieceInfo();
    do {
        std::cout<<"Podaj lokalizacje docelowa : \n";
        std::cout<<"x: ";
        std::cin>>x;
        std::cout<<"y: ";
        std::cin>>y;
        //std::cout<<board1->getSquares(x,y)->getSquareInfo();
    } while (!board1->getSquares(x,y));
    square=board1->getSquares(x,y);
//    std::cout<<square->getSquareInfo();
    MovePtr move=std::make_shared<Move>(piece,square);
    return move;
}

int HumanPlayer::askForPromotion() {
    int a=0;
    do {
        std::cout<<"\nWybierz figure w jaka chcesz zmienic pionka: \n (1- Skoczek, 2- Goniec 3- Wieza, 4- Krolowa )";
        std::cin>>a;
    } while (a<=0 || a>4);
    return a;
}






