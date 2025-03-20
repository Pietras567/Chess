//
// Created by Piotr on 10.05.2023.
//

#ifndef SOURCEFILES_QUEEN_H
#define SOURCEFILES_QUEEN_H
#include "model/Piece.h"
class Queen : public Piece {
private:
    const  std::string unicodeBlack = "\u2655";
    const  std::string unicodeWhite = "\u265B";
public:
    explicit Queen(const PlayerPtr &player);
    const std::string &getUnicodeWhite() const;
    const std::string &getUnicodeBlack() const;
    void showPieceImageWhite() override;
    void showPieceImageBlack() override;

    ~Queen() override;

    std::string getPieceInfo() override;

    std::vector<MovePtr>
    calculateAvailableMoves(const BoardPtr &board1, const std::vector<MovePtr> &moveHistory) override;
    std::string getClassName() override;
};

#endif //SOURCEFILES_QUEEN_H
