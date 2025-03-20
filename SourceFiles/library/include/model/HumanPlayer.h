//
// Created by Piotr on 10.05.2023.
//

#ifndef SOURCEFILES_HUMANPLAYER_H
#define SOURCEFILES_HUMANPLAYER_H
#include "Player.h"
#include "model/Move.h"
class HumanPlayer : public Player{
public:

    HumanPlayer(const std::string &name, bool white);

    ~HumanPlayer() override;

    MovePtr getMove(const BoardPtr &board1, const std::vector<MovePtr> &movesHistory) override;

    int askForPromotion() override;


};

#endif //SOURCEFILES_HUMANPLAYER_H
