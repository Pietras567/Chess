//
// Created by Piotr on 10.05.2023.
//
#ifndef SOURCEFILES_PIECE_H
#define SOURCEFILES_PIECE_H

#include <ostream>
#include "vector"
#include "typedefs.h"
#include "string"


class Square;
class MovementType;
class Move;
class Board;

class Piece: public std::enable_shared_from_this<Piece>{
    SquarePtr square; //wskaznik na pole pionka
    PlayerPtr player;

public:

    explicit Piece(const PlayerPtr &player);

    virtual ~Piece()=0;

    const SquarePtr &getSquare() const;

    void setSquare(const SquarePtr &squarePtr);



    virtual std::string getPieceInfo();

    void makeMove(const SquarePtr& sq);

    const PlayerPtr &getPlayer() const;


    virtual std::vector<MovePtr> calculateAvailableMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory)=0;

    //const BoardPtr &getBoard() const;

    void capture(const SquarePtr& squarePtr);

    int getDirection() const;

    ///funkcje zwracajace dostepne ruchy
    std::vector<MovePtr> getPawnMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory);
    std::vector<MovePtr> getLshapedMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory);
    std::vector<MovePtr> getDiagonalMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory);
    std::vector<MovePtr> getVerticalMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory);
    std::vector<MovePtr> getHorizontalMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory);
    std::vector<MovePtr> getKingMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory);
    virtual void showPieceImageWhite() = 0;
    virtual void showPieceImageBlack() = 0;
    virtual std::string getClassName() = 0;

    void setOnBoard(const SquarePtr &squarePtr);
};

#endif //SOURCEFILES_PIECE_H
