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

struct TestSuiteRookFixture{
    std::shared_ptr<Board> board1=std::make_shared<Board>();
    PlayerPtr player1=std::make_shared<HumanPlayer>("Bob",true);
    PlayerPtr player2=std::make_shared<HumanPlayer>("Josh",false);
    PiecePtr rook1=std::make_shared<Rook>(player1);
    PiecePtr pawn3=std::make_shared<Pawn>(player2);
    GamePtr game=std::make_shared<Game>(board1,player1,player2);
    TestSuiteRookFixture(){
        rook1->setOnBoard(board1->getSquares(5, 5));
        pawn3->setOnBoard(board1->getSquares(2,2));
        MovePtr test=std::make_shared<Move>(pawn3,board1->getSquares(2,2));
        game->getMovesHistory().push_back(test);
    }
    ~TestSuiteRookFixture(){}
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteRook,TestSuiteRookFixture)
    BOOST_AUTO_TEST_CASE(Rook_ConstructorTest){
        BOOST_TEST_REQUIRE(rook1->getSquare() == board1->getSquares(5, 5));
        BOOST_TEST_REQUIRE(rook1->getPlayer()==player1);
    }
    BOOST_AUTO_TEST_CASE(Rook_movesTest) {
//        std::cout<<player1->getAvailableMoves(board1,game->getMovesHistory()).size()<<"\n";
//        for (int i = 0; i < rook1->calculateAvailableMoves(board1,game->getMovesHistory()).size(); i++) {
//            std::cout<<i+1<<"."<<"\n";
//            std::cout<<" x: "<<rook1->calculateAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getX()<<"\n";
//            std::cout<<" y: "<<rook1->calculateAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getY()<<"\n";
//        }
        PiecePtr pawn1=std::make_shared<Pawn>(player1);
        pawn1->setOnBoard(board1->getSquares(6,7));
//                for (int i = 0; i < rook1->calculateAvailableMoves(board1,game->getMovesHistory()).size(); i++) {
//            std::cout<<i+1<<"."<<"\n";
//            std::cout<<" x: "<<rook1->calculateAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getX()<<"\n";
//            std::cout<<" y: "<<rook1->calculateAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getY()<<"\n";
//        }
        BOOST_TEST(rook1->calculateAvailableMoves(board1, game->getMovesHistory()).size() == 14);
        MovePtr move1=std::make_shared<Move>(rook1,board1->getSquares(5,7));
        BOOST_TEST_REQUIRE(player1->move(move1,board1,game->getMovesHistory()));
        move1=std::make_shared<Move>(rook1,board1->getSquares(6,7));
        BOOST_TEST_REQUIRE(!player1->move(move1,board1,game->getMovesHistory()));
        BOOST_TEST_REQUIRE(rook1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==12);
        pawn1->setSquare(board1->getSquares(5,6));
        BOOST_TEST_REQUIRE(rook1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==5);
    }
    BOOST_AUTO_TEST_CASE(Rook_captureKnightTest){
        PiecePtr knight1=std::make_shared<Knight>(player2);
        knight1->setOnBoard(board1->getSquares(2,3));
        BOOST_TEST(player2->getPieces().size()==2);
        MovePtr move1=std::make_shared<Move>(rook1,board1->getSquares(2,5));
        BOOST_TEST_REQUIRE(player1->move(move1,board1,game->getMovesHistory()));
        move1=std::make_shared<Move>(rook1,board1->getSquares(2,3));
        BOOST_TEST_REQUIRE(player1->move(move1,board1,game->getMovesHistory()));
        BOOST_TEST(board1->getSquares(2,3)->getPiece()==rook1);
        BOOST_TEST(rook1->calculateAvailableMoves(board1, game->getMovesHistory()).size() == 12);
    }

BOOST_AUTO_TEST_SUITE_END()
