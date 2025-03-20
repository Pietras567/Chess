//
// Created by Piotr on 10.05.2023.
//
#ifndef SOURCEFILES_PAWN_H
#define SOURCEFILES_PAWN_H
#include "Piece.h"
#include "Move.h"


class Pawn: public Piece{
private:
    //bool firstMove;
    //bool enPassant;
    const  std::string unicodeBlack = "\u2659";
    const  std::string unicodeWhite = "\u265F";
public:

    explicit Pawn(const PlayerPtr &player);

    ~Pawn() override;

//    bool move(const SquarePtr sq) override;

    std::string getPieceInfo() override;

//    bool isFirstMove() const;

//    void setFirstMove(bool firstMove);

    std::vector<MovePtr> calculateAvailableMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory) override;

//    bool isEnPassant() const;

//    void setEnPassant(bool enPassant);

    const std::string &getUnicodeWhite() const;
    const std::string &getUnicodeBlack() const;
    void showPieceImageWhite() override;
    void showPieceImageBlack() override;
    std::string getClassName() override;

};

#endif //SOURCEFILES_PAWN_H
