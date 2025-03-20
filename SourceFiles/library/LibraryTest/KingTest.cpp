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

struct TestSuiteKingFixture{
    std::shared_ptr<Board> board1=std::make_shared<Board>();
    PlayerPtr player1=std::make_shared<HumanPlayer>("Bob",true);
    PlayerPtr player2=std::make_shared<HumanPlayer>("Josh",false);
    PiecePtr king1=std::make_shared<King>( player1);
    PiecePtr pawn1=std::make_shared<Pawn>(player1);
    PiecePtr king2=std::make_shared<King>( player2);
    PiecePtr pawn3=std::make_shared<Pawn>(player2);
    GamePtr game=std::make_shared<Game>(board1,player1,player2);
    std::vector<MovePtr> moveHistory;
    TestSuiteKingFixture(){
        pawn1->setOnBoard(board1->getSquares(1,6));
        king1->setOnBoard(board1->getSquares(3, 7));
        king2->setOnBoard(board1->getSquares(3, 0));
        pawn3->setOnBoard(board1->getSquares(2,2));
        MovePtr test=std::make_shared<Move>(pawn3,board1->getSquares(2,3));
        player2->move(test,board1,game->getMovesHistory());
    }
    ~TestSuiteKingFixture(){}
};
BOOST_FIXTURE_TEST_SUITE(TestSuiteKing,TestSuiteKingFixture)
    BOOST_AUTO_TEST_CASE(King_ConstructorTest){
        BOOST_TEST_REQUIRE(king1->getSquare() == board1->getSquares(3, 7));
        BOOST_TEST_REQUIRE(king1->getPlayer()==player1);
    }
    BOOST_AUTO_TEST_CASE(King_movesTest) {
//        for (int i = 0; i < king1->calculateAvailableMoves(board1,game->getMovesHistory()).size(); i++) {
//            std::cout<<i+1<<"."<<"\n";
//            std::cout<<" x: "<<king1->calculateAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getX()<<"\n";
//            std::cout<<" y: "<<king1->calculateAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getY()<<"\n";
//        }
        BOOST_TEST_REQUIRE(king1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==5);
        king1->setSquare(board1->getSquares(7,7));
        pawn1->setOnBoard(board1->getSquares(7,6));
        BOOST_TEST_REQUIRE(king1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==2);
}
    BOOST_AUTO_TEST_CASE(CastlingWhiteTest_toRight) {
        PiecePtr rook1=std::make_shared<Rook>(player1);
        rook1->setOnBoard(board1->getSquares(0,7));
        BOOST_TEST(king1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==6);
        BOOST_TEST_REQUIRE(king1->calculateAvailableMoves(board1,game->getMovesHistory()).at(5)->getDestination()==board1->getSquares(1,7));
    }
    BOOST_AUTO_TEST_CASE(CastlingWhiteTest_toLeft){
        PiecePtr rook2=std::make_shared<Rook>(player1);
        rook2->setOnBoard(board1->getSquares(7,7));
        BOOST_TEST(king1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==6);
        BOOST_TEST_REQUIRE(king1->calculateAvailableMoves(board1,game->getMovesHistory()).at(5)->getDestination()==board1->getSquares(5,7));
}
    BOOST_AUTO_TEST_CASE(CastlingWhiteTest_toBoth){
        PiecePtr rook1=std::make_shared<Rook>(player1);
        PiecePtr rook2=std::make_shared<Rook>(player1);
        rook1->setOnBoard(board1->getSquares(0,7));
        rook2->setOnBoard(board1->getSquares(7,7));
        BOOST_TEST(king1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==7);
        BOOST_TEST_REQUIRE(king1->calculateAvailableMoves(board1,game->getMovesHistory()).at(5)->getDestination()==board1->getSquares(5,7));
        BOOST_TEST_REQUIRE(king1->calculateAvailableMoves(board1,game->getMovesHistory()).at(6)->getDestination()==board1->getSquares(1,7));
    }
    BOOST_AUTO_TEST_CASE(CastlingBlackTest_toLeft) {
        MovePtr test=std::make_shared<Move>(pawn1,board1->getSquares(1,5));
        pawn1->makeMove(board1->getSquares(1,5));
        game->getMovesHistory().push_back(test);
        PiecePtr rook2=std::make_shared<Rook>(player2);
        rook2->setOnBoard(board1->getSquares(0,0));
        BOOST_TEST(king2->calculateAvailableMoves(board1,game->getMovesHistory()).size()==6);
//        for (int i = 0; i < king2->calculateAvailableMoves(board1,game->getMovesHistory()).size(); i++) {
//            std::cout<<i+1<<"."<<"\n";
//            std::cout<<" x: "<<king2->calculateAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getX()<<"\n";
//            std::cout<<" y: "<<king2->calculateAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getY()<<"\n";
//        }
        BOOST_TEST_REQUIRE(king2->calculateAvailableMoves(board1,game->getMovesHistory()).at(5)->getDestination()==board1->getSquares(1,0));
    }
    BOOST_AUTO_TEST_CASE(CastlingBlackTest_toRight){
        MovePtr test=std::make_shared<Move>(pawn1,board1->getSquares(1,5));
        pawn1->makeMove(board1->getSquares(1,5));
        game->getMovesHistory().push_back(test);
        PiecePtr rook2=std::make_shared<Rook>(player2);
        rook2->setOnBoard(board1->getSquares(7,0));
        BOOST_TEST(king2->calculateAvailableMoves(board1,game->getMovesHistory()).size()==6);
        BOOST_TEST_REQUIRE(king2->calculateAvailableMoves(board1,game->getMovesHistory()).at(5)->getDestination()==board1->getSquares(5,0));
    }
    BOOST_AUTO_TEST_CASE(CastlingBlackTest_toBoth){
        MovePtr test=std::make_shared<Move>(pawn1,board1->getSquares(1,5));
        pawn1->makeMove(board1->getSquares(1,5));
        game->getMovesHistory().push_back(test);
        PiecePtr rook1=std::make_shared<Rook>(player2);
        PiecePtr rook2=std::make_shared<Rook>(player2);
        rook1->setOnBoard(board1->getSquares(0,0));
        rook2->setOnBoard(board1->getSquares(7,0));
        BOOST_TEST(king2->calculateAvailableMoves(board1,game->getMovesHistory()).size()==7);
        BOOST_TEST_REQUIRE(king2->calculateAvailableMoves(board1,game->getMovesHistory()).at(5)->getDestination()==board1->getSquares(5,0));
        BOOST_TEST_REQUIRE(king2->calculateAvailableMoves(board1,game->getMovesHistory()).at(6)->getDestination()==board1->getSquares(1,0));
    }
    BOOST_AUTO_TEST_CASE(CastlingWhiteTest_attackedRightSquares){
        PiecePtr rook1=std::make_shared<Rook>(player1);
        //PiecePtr rook2=std::make_shared<Rook>(player1);
        rook1->setOnBoard(board1->getSquares(0,7));
        //rook2->setOnBoard(board1->getSquares(7,7));
        PiecePtr rook3=std::make_shared<Rook>(player2);
        rook3->setOnBoard(board1->getSquares(3,5));
        BOOST_TEST(king1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==4);
        BOOST_TEST(std::dynamic_pointer_cast<King>(king1)->isChecked());
        rook3->makeMove(board1->getSquares(2,5));
        BOOST_TEST(king1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==3);
        BOOST_TEST(!std::dynamic_pointer_cast<King>(king1)->isChecked());
        rook3->makeMove(board1->getSquares(1,5));
        BOOST_TEST(king1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==6);
    }
BOOST_AUTO_TEST_SUITE_END()