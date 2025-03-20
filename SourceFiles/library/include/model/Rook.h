//
// Created by Piotr on 10.05.2023.
//

#ifndef SOURCEFILES_ROOK_H
#define SOURCEFILES_ROOK_H

#include "string"
#include "model/Piece.h"
class Rook : public Piece{
private:
    const  std::string unicodeBlack = "\u2656";
    const  std::string unicodeWhite = "\u265C";
public:
    explicit Rook(const PlayerPtr &player);

    const std::string &getUnicodeWhite() const;
    const std::string &getUnicodeBlack() const;
    void showPieceImageWhite() override;
    void showPieceImageBlack() override;

    ~Rook() override;

    std::string getPieceInfo() override;

    std::vector<MovePtr>
    calculateAvailableMoves(const BoardPtr &board1, const std::vector<MovePtr> &moveHistory) override;
    std::string getClassName() override;
};

#endif //SOURCEFILES_ROOK_H
