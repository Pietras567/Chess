//
// Created by Piotr on 10.05.2023.
//

#ifndef SOURCEFILES_KING_H
#define SOURCEFILES_KING_H
#include "model/Piece.h"
class King : public Piece {
private:
    bool checked;
    const  std::string unicodeWhite = "\u265A";
    const  std::string unicodeBlack = "\u2654";
public:

    bool isChecked() const;

    void setChecked(bool checked);

    explicit King(const PlayerPtr &player);

    const std::string &getUnicodeWhite() const;
    const std::string &getUnicodeBlack() const;
    void showPieceImageWhite() override;
    void showPieceImageBlack() override;

    ~King() override;

    std::string getPieceInfo() override;

    std::vector<MovePtr>
    calculateAvailableMoves(const BoardPtr &board1, const std::vector<MovePtr> &moveHistory) override;
    std::string getClassName() override;
};

#endif //SOURCEFILES_KING_H
