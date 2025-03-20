//
// Created by Piotr on 10.05.2023.
//

#ifndef SOURCEFILES_COMPUTERPLAYER_H
#define SOURCEFILES_COMPUTERPLAYER_H
#include "Player.h"
#include "model/Move.h"
class ComputerPlayer: public Player{
public:
    ComputerPlayer(bool white);

    ///do zrobienia: metoda losujaca ruch
    ~ComputerPlayer() override;

    MovePtr getMove(const BoardPtr& board1,const std::vector<MovePtr>& movesHistory) override;

    int askForPromotion() override;
};

#endif //SOURCEFILES_COMPUTERPLAYER_H
