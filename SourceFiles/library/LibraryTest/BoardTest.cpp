//
// Created by Piotr on 10.05.2023.
//
#include "boost/test/unit_test.hpp"
#include "model/Pawn.h"
#include "model/Square.h"
#include "typedefs.h"
#include "model/Board.h"
#include "model/Rook.h"
#include "model/HumanPlayer.h"

BOOST_AUTO_TEST_SUITE(TestSuiteBoard)
    std::shared_ptr<Board> board1=std::make_shared<Board>();

    BOOST_AUTO_TEST_CASE(Board_duplicateTest){
        PlayerPtr player1=std::make_shared<HumanPlayer>("Bob",true);
        PlayerPtr player2=std::make_shared<HumanPlayer>("Bob", false);
        PiecePtr rook1=std::make_shared<Rook>(player1);
        rook1->setSquare(board1->getSquares(6,0));
        BoardPtr board2= board1->duplicate();
        BOOST_TEST(std::dynamic_pointer_cast<Rook>(board2->getSquares(6,0)->getPiece()));
        BOOST_TEST(player1==board2->getSquares(6,0)->getPiece()->getPlayer());
        PiecePtr pawn2=std::make_shared<Pawn>(player2);
        BOOST_TEST(board1->getSquares(5,5)->getPiece()== nullptr);
        pawn2->setSquare(board2->getSquares(5,5));
        BOOST_TEST(board2->getSquares(5,5)->getPiece()==pawn2);
        BOOST_TEST(board1->getSquares(5,5)->getPiece()== nullptr);
    }

BOOST_AUTO_TEST_SUITE_END()