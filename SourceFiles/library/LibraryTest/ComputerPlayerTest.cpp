#include "boost/test/unit_test.hpp"
#include "model/Pawn.h"
#include "model/Square.h"
#include "typedefs.h"
#include "model/Board.h"
#include "model/HumanPlayer.h"
#include "model/Game.h"
#include "vector"
#include "model/Rook.h"
#include "model/King.h"
#include "model/ComputerPlayer.h"

struct TestSuiteComputerPlayerFixture{
    std::shared_ptr<Board> board1=std::make_shared<Board>();
    PlayerPtr player1=std::make_shared<HumanPlayer>("Bob",true);
    PlayerPtr computerPlayer=std::make_shared<ComputerPlayer>(false);
    PiecePtr rook1=std::make_shared<Rook>(player1);
    PiecePtr rook2=std::make_shared<Rook>(computerPlayer);
    PiecePtr king1=std::make_shared<King>(player1);
    PiecePtr king2=std::make_shared<King>(computerPlayer);
    GamePtr game=std::make_shared<Game>(board1,player1,computerPlayer);
    PiecePtr pawn2=std::make_shared<Pawn>(computerPlayer);
    PiecePtr queen=std::make_shared<Pawn>(computerPlayer);
    TestSuiteComputerPlayerFixture(){
        //king1->setOnBoard(board1->getSquares(6,7));
        rook1->setOnBoard(board1->getSquares(2, 7));
        king2->setOnBoard(board1->getSquares(0,0));
        rook2->setOnBoard(board1->getSquares(7,1));
        pawn2->setOnBoard(board1->getSquares(2,2));
        //game->getMovesHistory().push_back(test);
    }
    ~TestSuiteComputerPlayerFixture(){}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteComputerPlayer,TestSuiteComputerPlayerFixture)
    BOOST_AUTO_TEST_CASE(ComputerPlayer_movesTest){
    MovePtr randomMove=computerPlayer->getMove(board1,game->getMovesHistory());
    BOOST_TEST_REQUIRE(computerPlayer->move(randomMove,board1,game->getMovesHistory()));
    randomMove=computerPlayer->getMove(board1,game->getMovesHistory());
    BOOST_TEST_REQUIRE(computerPlayer->move(randomMove,board1,game->getMovesHistory()));
    randomMove=computerPlayer->getMove(board1,game->getMovesHistory());
    BOOST_TEST_REQUIRE(computerPlayer->move(randomMove,board1,game->getMovesHistory()));
    randomMove=computerPlayer->getMove(board1,game->getMovesHistory());
    BOOST_TEST_REQUIRE(computerPlayer->move(randomMove,board1,game->getMovesHistory()));
}

BOOST_AUTO_TEST_SUITE_END()
