#include <boost/test/unit_test.hpp>
#include "model/Pawn.h"
#include "model/Square.h"
#include "typedefs.h"
#include "model/Board.h"
#include "model/HumanPlayer.h"

BOOST_AUTO_TEST_SUITE(TestSuiteSquare)
    BoardPtr board1=std::make_shared<Board>();
    PlayerPtr player1=std::make_shared<HumanPlayer>("Bob",true);
    PlayerPtr player2=std::make_shared<HumanPlayer>("Josh",false);
    PiecePtr pawn=std::make_shared<Pawn>(player1);
    BOOST_AUTO_TEST_CASE(Square_getXYTest){
        BOOST_TEST(board1->getSquares(4,7)->getX()==4);
        BOOST_TEST(board1->getSquares(4,7)->getY()==7);
    }
    BOOST_AUTO_TEST_CASE(Square_setPieceTest){
        board1->getSquares(1,1)->setPiece(pawn);
        BOOST_TEST(board1->getSquares(1,1)->getPiece()==pawn);
        BOOST_TEST(pawn->getSquare()==board1->getSquares(1,1));
    }
BOOST_AUTO_TEST_SUITE_END()