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

struct TestSuiteBishopFixture{
    std::shared_ptr<Board> board1=std::make_shared<Board>();
    PlayerPtr player1=std::make_shared<HumanPlayer>("Bob",true);
    PlayerPtr player2=std::make_shared<HumanPlayer>("Josh",false);
    PiecePtr bishop1=std::make_shared<Bishop>( player1);
    PiecePtr pawn3=std::make_shared<Pawn>(player2);
    GamePtr game=std::make_shared<Game>(board1,player1,player2);
    std::vector<MovePtr> moveHistory;
    TestSuiteBishopFixture(){
        bishop1->setOnBoard(board1->getSquares(5, 5));
        pawn3->setOnBoard(board1->getSquares(2,2));
        MovePtr test=std::make_shared<Move>(pawn3,board1->getSquares(2,2));
        game->getMovesHistory().push_back(test);
    }
    ~TestSuiteBishopFixture(){}
};
BOOST_FIXTURE_TEST_SUITE(TestSuiteBishop,TestSuiteBishopFixture)

    BOOST_AUTO_TEST_CASE(Bishop_ConstructorTest){
        BOOST_TEST_REQUIRE(bishop1->getSquare() == board1->getSquares(5, 5));
        BOOST_TEST_REQUIRE(bishop1->getPlayer()==player1);
    }

    BOOST_AUTO_TEST_CASE(Bishop_movesTest) {
//        std::cout<<player1->getAvailableMoves(board1,game->getMovesHistory()).size()<<"\n";
//        for (int i = 0; i < player1->getAvailableMoves(board1,game->getMovesHistory()).size(); i++) {
//            std::cout<<i+1<<"."<<"\n";
//            std::cout<<" x: "<<player1->getAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getX()<<"\n";
//            std::cout<<" y: "<<player1->getAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getY()<<"\n";
//        }
        BOOST_TEST(bishop1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==9);
        MovePtr move=std::make_shared<Move>(bishop1,board1->getSquares(7,7));
        BOOST_TEST_REQUIRE(player1->move(move,board1,game->getMovesHistory()));
        BOOST_TEST_REQUIRE(board1->getSquares(7,7)->getPiece()==bishop1);
        BOOST_TEST(bishop1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==5);
        move=std::make_shared<Move>(bishop1,board1->getSquares(1,1));
        BOOST_TEST_REQUIRE(!player1->move(move,board1,game->getMovesHistory()));
        PiecePtr pawn1=std::make_shared<Pawn>(player1);
        pawn1->setOnBoard(board1->getSquares(6,6));
        BOOST_TEST(bishop1->calculateAvailableMoves(board1,game->getMovesHistory()).size()==0);
    }
    BOOST_AUTO_TEST_CASE(Bishop_captureKnightTest){
        PiecePtr knight1=std::make_shared<Knight>(player2);
        knight1->setOnBoard(board1->getSquares(2,2));
        BOOST_TEST(player2->getPieces().size()==2);
        bishop1->setSquare(board1->getSquares(7,7));
        board1->getSquares(5,5)->setPiece(nullptr);
        MovePtr move=std::make_shared<Move>(bishop1,board1->getSquares(2,2));
        BOOST_TEST_REQUIRE(player1->move(move,board1,game->getMovesHistory()));
        BOOST_TEST_REQUIRE(board1->getSquares(2,2)->getPiece()==bishop1);
        BOOST_TEST(player2->getPieces().size()==1);
    }

BOOST_AUTO_TEST_SUITE_END()
