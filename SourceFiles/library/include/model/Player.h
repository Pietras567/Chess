
#ifndef CARRENTAL_PLAYER_H
#define CARRENTAL_PLAYER_H

#include <vector>
#include "iostream"
#include "typedefs.h"

class Player : public std::enable_shared_from_this<Player>{
    std::string name;
    std::vector<PiecePtr> pieces;
    bool white;
    //BoardPtr board;
public:
    Player(const std::string &name, bool white);
    Player(bool white);

    virtual ~Player()=0;


    const std::string &getName() const;

    std::vector<PiecePtr> &getPieces();

    //const BoardPtr &getBoard() const;

    bool isWhite() const;

    virtual MovePtr getMove(const BoardPtr& board1,const std::vector<MovePtr>& movesHistory)=0;
    bool move(const MovePtr& move, const BoardPtr& board1, std::vector<MovePtr> &movesHistory);

    std::vector<MovePtr> getAvailableMoves(const BoardPtr& board1,const std::vector<MovePtr>& movesHistory);

    std::vector<MovePtr> checkMovesOnVirtualBoard(const BoardPtr &board1, const std::vector<MovePtr> &movesHistory,const std::vector<MovePtr> &availableMoves,const SquarePtr& kingLocation);

    void setName(const std::string &name);

    void setWhite(bool white);

    std::vector<MovePtr>
    convertMovesToDifferentBoard(const std::vector<MovePtr> &movesToConvert, const BoardPtr &newBoard);

    bool checkSpecialMoves(const MovePtr &move, const BoardPtr &board1, std::vector<MovePtr> &movesHistory);

    virtual int askForPromotion()=0;

    void promotion(const PiecePtr& piece, int a);
};


#endif //CARRENTAL_PLAYER_H
