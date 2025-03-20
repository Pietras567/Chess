//
// Created by Piotr on 10.05.2023.
//

#ifndef SOURCEFILES_GAME_H
#define SOURCEFILES_GAME_H

#include <memory>
#include "vector"
#include "string"
#include "typedefs.h"


class Player;
class Board;
class Piece;
class Square;
class Game {
private:
    std::vector<MovePtr> movesHistory;
    BoardPtr GameBoard;
    PlayerPtr player1;
    PlayerPtr player2;
public:
    Game(const BoardPtr &gameBoard, const PlayerPtr &player1, const PlayerPtr &player2);
    void updateScreen();
    bool loadGame();
    bool saveGame();
    //void endGame();

    const BoardPtr &getGameBoard() const;

    std::vector<MovePtr> &getMovesHistory();

    const PlayerPtr &getPlayer1() const;

    const PlayerPtr &getPlayer2() const;

    void askPlayer1ToMove();
    void askPlayer2ToMove();

    void endGame();

    //void additionalInfo();

    void getMovesHistoryInfo();

    void draw();
};

#endif //SOURCEFILES_GAME_H
