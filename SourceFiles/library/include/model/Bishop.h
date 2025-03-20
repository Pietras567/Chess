//
// Created by Piotr on 10.05.2023.
//

#ifndef SOURCEFILES_BISHOP_H
#define SOURCEFILES_BISHOP_H
#include "Piece.h"
#include "../typedefs.h"

class Bishop : public Piece {
private:
    const std::string unicodeBlack = "\u2657";
    const std::string unicodeWhite = "\u265D";
public:
    explicit Bishop(const PlayerPtr &player);

    ~Bishop() override;

    std::string getPieceInfo() override;
    std::vector<MovePtr> calculateAvailableMoves(const BoardPtr &board1, const std::vector<MovePtr> &moveHistory) override;
    const std::string &getUnicodeWhite() const;

    const std::string &getUnicodeBlack() const;
    void showPieceImageWhite() override;
    void showPieceImageBlack() override;
    std::string getClassName() override;
};

#endif //SOURCEFILES_BISHOP_H
