#include "boost/test/unit_test.hpp"
#include "model/Pawn.h"
#include "model/Square.h"
#include "typedefs.h"
#include "model/Board.h"
#include "model/HumanPlayer.h"
#include "model/Game.h"
#include "vector"
#include "model/Bishop.h"
#include "model/Knight.h"
#include "model/Rook.h"
#include "model/Queen.h"

struct TestSuiteQueenFixture{
    std::shared_ptr<Board> board1=std::make_shared<Board>();
    PlayerPtr player1=std::make_shared<HumanPlayer>("Bob",true);
    PlayerPtr player2=std::make_shared<HumanPlayer>("Josh",false);
    PiecePtr queen1=std::make_shared<Queen>( player1);
    PiecePtr pawn3=std::make_shared<Pawn>(player2);
    GamePtr game=std::make_shared<Game>(board1,player1,player2);
    std::vector<MovePtr> moveHistory;
    TestSuiteQueenFixture(){
        queen1->setOnBoard(board1->getSquares(5, 5));
        pawn3->setOnBoard(board1->getSquares(2,2));
        MovePtr test=std::make_shared<Move>(pawn3,board1->getSquares(2,2));
        game->getMovesHistory().push_back(test);
    }
    ~TestSuiteQueenFixture(){}
};
BOOST_FIXTURE_TEST_SUITE(TestSuiteQueen,TestSuiteQueenFixture)
    BOOST_AUTO_TEST_CASE(Queen_ConstructorTest){
        BOOST_TEST_REQUIRE(queen1->getSquare() == board1->getSquares(5, 5));
        BOOST_TEST_REQUIRE(queen1->getPlayer()==player1);
    }
    BOOST_AUTO_TEST_CASE(Queen_movesTest) {
//        for (int i = 0; i < queen1->calculateAvailableMoves(board1,game->getMovesHistory()).size(); i++) {
//            std::cout<<i+1<<"."<<"\n";
//            std::cout<<" x: "<<queen1->calculateAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getX()<<"\n";
//            std::cout<<" y: "<<queen1->calculateAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getY()<<"\n";
//        }
        BOOST_TEST_REQUIRE(queen1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==23);
        MovePtr move1=std::make_shared<Move>(queen1,board1->getSquares(7,7));
        BOOST_TEST_REQUIRE(player1->move(move1,board1,moveHistory));
        PiecePtr pawn1=std::make_shared<Pawn>(player1);
        pawn1->setSquare(board1->getSquares(7,6));
        pawn3->setSquare(board1->getSquares(6,6));
        BOOST_TEST(queen1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==8);
}
    BOOST_AUTO_TEST_CASE(Queen_captureRookTest){
        PiecePtr rook1=std::make_shared<Rook>( player2);
        rook1->setSquare(board1->getSquares(7,0));
        MovePtr move1=std::make_shared<Move>(queen1,board1->getSquares(3,7));
        BOOST_TEST_REQUIRE(player1->move(move1,board1,moveHistory));
        move1=std::make_shared<Move>(queen1,board1->getSquares(0,7));
        BOOST_TEST_REQUIRE(player1->move(move1,board1,moveHistory));
        move1=std::make_shared<Move>(queen1,board1->getSquares(7,0));
        BOOST_TEST_REQUIRE(player1->move(move1,board1,moveHistory));
        BOOST_TEST(queen1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==21);
    }
    
BOOST_AUTO_TEST_SUITE_END()
