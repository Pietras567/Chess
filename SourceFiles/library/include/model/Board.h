//
// Created by Piotr on 10.05.2023.
//

#ifndef SOURCEFILES_BOARD_H
#define SOURCEFILES_BOARD_H
#include "typedefs.h"
#include "iostream"

class Board : public std::enable_shared_from_this<Board>{
    SquarePtr squares[8][8]; //tablica 8x8 obiektow Square
public:
    explicit Board();
    SquarePtr getSquares(int i, int j);
    BoardPtr duplicate();
    void fill(const PlayerPtr& player1,const PlayerPtr& player2);


};


#endif //SOURCEFILES_BOARD_H
