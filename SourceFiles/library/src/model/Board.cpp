//
// Created by Piotr on 10.05.2023.
//
#include <memory>
#include "model/Board.h"
#include "model/Square.h"
#include "model/Player.h"
#include "../../exceptions/BoardException.h"
#include "model/Knight.h"
#include "model/Bishop.h"
#include "model/Rook.h"
#include "model/Queen.h"
#include "model/King.h"
#include "model/Pawn.h"
#include "model/RookFactory.h"
#include "model/PawnFactory.h"
#include "model/BishopFactory.h"
#include "model/KnightFactory.h"


Board::Board() {
    for (int i = 0; i < 8; i++) { //wypelnianie tablicy obiektami o wspolrzednych zgodnych z tablica
        for (int j = 0; j < 8; j++) {
            SquarePtr square = std::make_shared<Square>(i,j, nullptr);
            squares[i][j] = square;
        }
    }

}

SquarePtr Board::getSquares(int i, int j) {
    if(i>=0 && i<8 && j>=0 && j<8){
        return squares[i][j];
    }
    return nullptr;
}

BoardPtr Board::duplicate() {
    BoardPtr board2=std::make_shared<Board>();
    PiecePtr newPiece;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            SquarePtr square=getSquares(x,y);
            PiecePtr piece=getSquares(x,y)->getPiece();
            if(piece){
                if(std::dynamic_pointer_cast<Pawn>(piece)){
                    newPiece=std::make_shared<Pawn>(piece->getPlayer());
                }
                else if (std::dynamic_pointer_cast<Knight>(piece)){
                    newPiece=std::make_shared<Knight>(piece->getPlayer());
                }
                else if (std::dynamic_pointer_cast<Bishop>(piece)){
                    newPiece=std::make_shared<Bishop>(piece->getPlayer());
                }
                else if (std::dynamic_pointer_cast<Rook>(piece)){
                    newPiece=std::make_shared<Rook>(piece->getPlayer());
                }
                else if (std::dynamic_pointer_cast<Queen>(piece)){
                    newPiece=std::make_shared<Queen>(piece->getPlayer());
                }
                else if (std::dynamic_pointer_cast<King>(piece)){
                    newPiece=std::make_shared<King>(piece->getPlayer());
                }
                else{
                    throw BoardException("conversion error while copying pieces from board");
                }
                newPiece->setSquare(board2->getSquares(x,y));
            }
        }
    }
    return board2;
}

void Board::fill(const PlayerPtr& player1,const PlayerPtr& player2) {
//    auto fillBoard = [this](const PlayerPtr& player1, const PlayerPtr& player2) {
//        RookFactory rookFactory;
//        PawnFactory pawnFactory;
//        BishopFactory bishopFactory;
//        KnightFactory knightFactory;
//        for (int i = 0; i < 8; ++i) {
//            for (int j = 0; j < 8; ++j) {
//                if (i == 0) {
//                    if (j == 0 || j == 7) {
//                        getSquares(i, j)->setPiece(rookFactory.create(player1));
//                    } else if (j == 1 || j == 6) {
//                        getSquares(i, j)->setPiece(knightFactory.create(player1));
//                    } else if (j == 2 || j == 5) {
//                        getSquares(i, j)->setPiece(bishopFactory.create(player1));
//                    } else if (j == 3) {
//                        getSquares(i, j)->setPiece(std::make_shared<Queen>(player1));
//                    } else if (j == 4) {
//                        getSquares(i, j)->setPiece(std::make_shared<King>(player1));
//                    }
//                } else if (i == 1) {
//                    getSquares(i, j)->setPiece(pawnFactory.create(player1));
//                } else if (i == 6) {
//                    getSquares(i, j)->setPiece(pawnFactory.create(player2));
//                } else if (i == 7) {
//                    if (j == 0 || j == 7) {
//                        getSquares(i, j)->setPiece(rookFactory.create(player2));
//                    } else if (j == 1 || j == 6) {
//                        getSquares(i, j)->setPiece(knightFactory.create(player2));
//                    } else if (j == 2 || j == 5) {
//                        getSquares(i, j)->setPiece(bishopFactory.create(player2));
//                    } else if (j == 3) {
//                        getSquares(i, j)->setPiece(std::make_shared<Queen>(player2));
//                    } else if (j == 4) {
//                        getSquares(i, j)->setPiece(std::make_shared<King>(player2));
//                    }
//                }
//            }
//        }
//    };
//    if (player2->isWhite()) {
//        fillBoard(player2,player1);
//    } else{
//        fillBoard(player1,player2);
//    }
    RookFactory rookFactory;
    PawnFactory pawnFactory;
    BishopFactory bishopFactory;
    KnightFactory knightFactory;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (i == 0) {
                if (j == 0 || j == 7) {
                    rookFactory.create(player2)->setOnBoard(getSquares(j,i ));
                } else if (j == 1 || j == 6) {
                    knightFactory.create(player2)->setOnBoard(getSquares(j,i));
                } else if (j == 2 || j == 5) {
                    bishopFactory.create(player2)->setOnBoard(getSquares(j,i));
                } else if (j == 3) {
                    std::make_shared<King>(player2)->setOnBoard(getSquares(j,i));
                } else if (j == 4) {
                    std::make_shared<Queen>(player2)->setOnBoard(getSquares(j,i));
                }
            } else if (i == 1) {
                pawnFactory.create(player2)->setOnBoard(getSquares(j,i));
            } else if (i == 6) {
                pawnFactory.create(player1)->setOnBoard(getSquares(j,i));
            } else if (i == 7) {
                if (j == 0 || j == 7) {
                    rookFactory.create(player1)->setOnBoard(getSquares(j,i));
                } else if (j == 1 || j == 6) {
                    knightFactory.create(player1)->setOnBoard(getSquares(j,i));
                } else if (j == 2 || j == 5) {
                    bishopFactory.create(player1)->setOnBoard(getSquares(j,i));
                } else if (j == 3) {
                    std::make_shared<King>(player1)->setOnBoard(getSquares(j,i));
                } else if (j == 4) {
                    std::make_shared<Queen>(player1)->setOnBoard(getSquares(j,i));
                }
            }
        }
    }
}








