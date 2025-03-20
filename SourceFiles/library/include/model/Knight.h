//
// Created by student on 31.05.23.
//

#ifndef CARRENTAL_KNIGHT_H
#define CARRENTAL_KNIGHT_H
#include "iostream"
#include "Piece.h"
#include "model/Piece.h"
class Knight : public Piece{
private:
    const  std::string unicodeBlack = "\u2658";
    const  std::string unicodeWhite = "\u265E";
public:
    explicit Knight(const PlayerPtr &player);

    ~Knight() override;

    std::string getPieceInfo() override;

    std::vector<MovePtr> calculateAvailableMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory) override;

    const std::string &getUnicodeWhite() const;
    const std::string &getUnicodeBlack() const;
    void showPieceImageWhite() override;
    void showPieceImageBlack() override;
    std::string getClassName() override;
};


#endif //CARRENTAL_KNIGHT_H
