//
// Created by Piotr on 10.05.2023.
//
#include "model/ComputerPlayer.h"
#include "model/Piece.h"
#include "model/Square.h"
#include "ctime"
#include "cstdlib"
#include "model/Knight.h"
#include "model/Bishop.h"
#include "model/Rook.h"
#include "model/Queen.h"


ComputerPlayer::ComputerPlayer(bool white) : Player(white) {}

ComputerPlayer::~ComputerPlayer() {

}

MovePtr ComputerPlayer::getMove(const BoardPtr& board1,const std::vector<MovePtr>& movesHistory) {
    srand(time(NULL));
    MovePtr randomMove;
    std::vector<MovePtr> availableMoves= getAvailableMoves(board1,movesHistory);
    int size=availableMoves.size();
    int number=rand() % size;
    randomMove=availableMoves.at(number);
    return randomMove;
}

int ComputerPlayer::askForPromotion() {
    int a= (rand() % 3) +1;
    return a;
}








