//
// Created by student on 31.05.23.
//
#include "boost/test/unit_test.hpp"
#include "model/Pawn.h"
#include "model/Square.h"
#include "typedefs.h"
#include "model/Board.h"
#include "model/HumanPlayer.h"
#include "model/Knight.h"
#include "model/Game.h"
struct TestSuiteKnightFixture{
    std::shared_ptr<Board> board1=std::make_shared<Board>();
    PlayerPtr player1=std::make_shared<HumanPlayer>("Bob",true);
    PlayerPtr player2=std::make_shared<HumanPlayer>("Josh",false);
    PiecePtr knight1=std::make_shared<Knight>(player1);
    PiecePtr pawn1=std::make_shared<Pawn>(player2);
    PiecePtr pawn3=std::make_shared<Pawn>(player2);
    GamePtr game=std::make_shared<Game>(board1,player1,player2);
    std::vector<MovePtr> moveHistory;
    TestSuiteKnightFixture(){
        knight1->setOnBoard(board1->getSquares(5, 5));
        pawn3->setOnBoard(board1->getSquares(2,2));
        MovePtr test=std::make_shared<Move>(pawn3,board1->getSquares(2,2));
        game->getMovesHistory().push_back(test);
    }
    ~TestSuiteKnightFixture(){}
};
BOOST_FIXTURE_TEST_SUITE(TestSuiteKnight,TestSuiteKnightFixture)

BOOST_AUTO_TEST_CASE(Knight_ConstructorTest){
    BOOST_TEST_REQUIRE(knight1->getSquare() == board1->getSquares(5, 5));
    BOOST_TEST_REQUIRE(knight1->getPlayer()==player1);
}
    BOOST_AUTO_TEST_CASE(Knight_movesTest){
        // 7,6; 7,4; 3,6; 3,4; 6,7; 4,7; 6,3; 4,3; 4,4;
        BOOST_TEST(knight1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==8);
//        std::cout<<player1->getAvailableMoves(board1,game->getMovesHistory()).size()<<"\n";
//        for (int i = 0; i < player1->getAvailableMoves(board1,game->getMovesHistory()).size(); i++) {
//            std::cout<<i+1<<"."<<"\n";
//            std::cout<<" x: "<<player1->getAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getX()<<"\n";
//            std::cout<<" y: "<<player1->getAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getY()<<"\n";
//        }
        MovePtr move=std::make_shared<Move>(knight1,board1->getSquares(7,6));
        BOOST_TEST_REQUIRE(player1->move(move,board1,game->getMovesHistory()));
        BOOST_TEST_REQUIRE(board1->getSquares(7,6)->getPiece()==knight1);
        BOOST_TEST(knight1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==3);

    }
    BOOST_AUTO_TEST_CASE(Knight_capturePawnTest){
        pawn1->setOnBoard(board1->getSquares(6,3));
        BOOST_TEST(player2->getPieces().size()==2);
        MovePtr move=std::make_shared<Move>(knight1,board1->getSquares(6,3));
        BOOST_TEST_REQUIRE(player1->move(move,board1,game->getMovesHistory()));
        BOOST_TEST_REQUIRE(board1->getSquares(6,3)->getPiece()==knight1);
        BOOST_TEST(player2->getPieces().size()==1);
}

BOOST_AUTO_TEST_SUITE_END()