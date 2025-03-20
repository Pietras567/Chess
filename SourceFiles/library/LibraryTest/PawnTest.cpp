//
// Created by student on 25.05.23.
//
#include "boost/test/unit_test.hpp"
#include "model/Pawn.h"
#include "model/Square.h"
#include "typedefs.h"
#include "model/Board.h"
#include "model/HumanPlayer.h"
#include "model/Game.h"
#include "vector"
struct TestSuitePawnFixture{
    std::shared_ptr<Board> board1=std::make_shared<Board>();
    PlayerPtr player1=std::make_shared<HumanPlayer>("Bob",true);
    PlayerPtr player2=std::make_shared<HumanPlayer>("Josh",false);
    PiecePtr pawn1=std::make_shared<Pawn>(player1);
    PiecePtr pawn2=std::make_shared<Pawn>(player2);
    PiecePtr pawn3=std::make_shared<Pawn>(player2);
    SquarePtr sq1=board1->getSquares(5,5);
    SquarePtr sq2=board1->getSquares(5,4);
    GamePtr game=std::make_shared<Game>(board1,player1,player2);
    std::vector<MovePtr> moveHistory;
    TestSuitePawnFixture(){
        pawn1->setOnBoard(board1->getSquares(5, 6));
        pawn2->setOnBoard(board1->getSquares(1,1));
        pawn3->setOnBoard(board1->getSquares(2,2));
        MovePtr test=std::make_shared<Move>(pawn3,board1->getSquares(2,2));
        game->getMovesHistory().push_back(test);
    }
    ~TestSuitePawnFixture(){}
};
BOOST_FIXTURE_TEST_SUITE(TestSuitePawn,TestSuitePawnFixture)

    BOOST_AUTO_TEST_CASE(Pawn_ConstructorTest){
        BOOST_TEST_REQUIRE(pawn1->getSquare() == board1->getSquares(5, 6));
        BOOST_TEST_REQUIRE(pawn1->getPlayer()==player1);
    }
    BOOST_AUTO_TEST_CASE(Pawn_setOnBoardTest){
        BOOST_TEST_REQUIRE(pawn1->getSquare() == board1->getSquares(5, 6));
        BOOST_TEST_REQUIRE(pawn1 == board1->getSquares(5, 6)->getPiece());
    }
    BOOST_AUTO_TEST_CASE(Pawn_checkMove_ByOneSquare){
        std::vector<MovePtr> pawnMoves=pawn1->calculateAvailableMoves(board1,moveHistory);
//        for (int i = 0; i < pawnMoves.size(); ++i) {
//            std::cout<<i+1<<"."<<"\n";
//            std::cout<<" x: "<<pawnMoves.at(i)->getDestination()->getX()<<"\n";
//            std::cout<<" y: "<<pawnMoves.at(i)->getDestination()->getY()<<"\n";
//        }
//
//        std::cout<<">>>>>>>>>>>>PLAYER1"<<"\n";
//        std::cout<<player1->getPieces().size()<<"\n";
//        for (int i = 0; i < player1->getAvailableMoves(board1,moveHistory).size(); ++i) {
//            std::cout<<i+1<<"."<<"\n";
//            std::cout<<" x: "<<player1->getAvailableMoves(board1,moveHistory).at(i)->getDestination()->getX()<<"\n";
//            std::cout<<" y: "<<player1->getAvailableMoves(board1,moveHistory).at(i)->getDestination()->getY()<<"\n";
//        }
        MovePtr move1=std::make_shared<Move>(pawn1,board1->getSquares(5,5));
        BOOST_TEST_REQUIRE(player1->move(move1,board1,game->getMovesHistory()));
        game->getMovesHistory().push_back(move1);
        BOOST_TEST(move1->getOldSquare()->getPiece()== nullptr);
        BOOST_TEST(pawn1->getSquare()==sq1);
        BOOST_TEST(board1->getSquares(5,5)->getPiece()==pawn1);
        BOOST_TEST_REQUIRE(!player2->move(move1,board1,game->getMovesHistory()));
        MovePtr move2=std::make_shared<Move>(pawn2,board1->getSquares(1,2));
        BOOST_TEST_REQUIRE(player2->move(move2,board1,game->getMovesHistory()));
        BOOST_TEST(pawn2->getSquare()==board1->getSquares(1,2));
        BOOST_TEST(board1->getSquares(1,2)->getPiece()==pawn2);
        BOOST_TEST(move2->getOldSquare()->getPiece()== nullptr);
    }
    BOOST_AUTO_TEST_CASE(Pawn_checkMove_By2Squares){
        MovePtr move1=std::make_shared<Move>(pawn1,board1->getSquares(5,4));
        BOOST_TEST_REQUIRE(player1->move(move1,board1,game->getMovesHistory()));
        //game->getMovesHistory().push_back(move1);
        BOOST_TEST(move1->getOldSquare()->getPiece()== nullptr);
        BOOST_TEST(pawn1->getSquare()==sq2);
        BOOST_TEST(board1->getSquares(5,4)->getPiece()==pawn1);
        BOOST_TEST_REQUIRE(!player2->move(move1,board1,game->getMovesHistory()));
        MovePtr move2=std::make_shared<Move>(pawn2,board1->getSquares(1,3));
        BOOST_TEST_REQUIRE(player2->move(move2,board1,game->getMovesHistory()));
        BOOST_TEST(pawn2->getSquare()==board1->getSquares(1,3));
        BOOST_TEST(board1->getSquares(1,3)->getPiece()==pawn2);
        BOOST_TEST(move2->getOldSquare()->getPiece()== nullptr);
    }
    BOOST_AUTO_TEST_CASE(Pawn_checkMove_By3Squares){
        MovePtr move1=std::make_shared<Move>(pawn1,board1->getSquares(5,2));
        BOOST_TEST_REQUIRE(!player1->move(move1,board1,game->getMovesHistory()));
        MovePtr move2=std::make_shared<Move>(pawn2,board1->getSquares(1,4));
        BOOST_TEST_REQUIRE(!player2->move(move2,board1,game->getMovesHistory()));
    }
    BOOST_AUTO_TEST_CASE(Pawn_checkMove_Horizontal){
        MovePtr move1=std::make_shared<Move>(pawn1,board1->getSquares(4,5));
        BOOST_TEST_REQUIRE(!player1->move(move1,board1,game->getMovesHistory()));
        move1=std::make_shared<Move>(pawn2,board1->getSquares(6,5));
        BOOST_TEST_REQUIRE(!player1->move(move1,board1,game->getMovesHistory()));
        MovePtr move2=std::make_shared<Move>(pawn2,board1->getSquares(0,1));
        BOOST_TEST_REQUIRE(!player2->move(move2,board1,game->getMovesHistory()));
        move2=std::make_shared<Move>(pawn2,board1->getSquares(2,1));
        BOOST_TEST_REQUIRE(!player2->move(move2,board1,game->getMovesHistory()));
    }
    BOOST_AUTO_TEST_CASE(Pawn1_pieceBlockingMoveByOneSquareTest){
        pawn2->setOnBoard(board1->getSquares(5,4));
//        std::cout<<">>>>>>>>>>>>PLAYER1"<<"\n";
//        std::cout<<player1->getPieces().size()<<"\n";
//        std::cout<<player1->getAvailableMoves(board1,game->getMovesHistory()).size()<<"\n";
//        for (int i = 0; i < player1->getAvailableMoves(board1,game->getMovesHistory()).size(); i++) {
//            std::cout<<i+1<<"."<<"\n";
//            std::cout<<" x: "<<player1->getAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getX()<<"\n";
//            std::cout<<" y: "<<player1->getAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getY()<<"\n";
//        }
        MovePtr move1=std::make_shared<Move>(pawn1,board1->getSquares(5,4));
        BOOST_TEST_REQUIRE(!player1->move(move1,board1,game->getMovesHistory()));
        move1=std::make_shared<Move>(pawn1,board1->getSquares(5,3));
        BOOST_TEST_REQUIRE(!player1->move(move1,board1,game->getMovesHistory()));
    }
    BOOST_AUTO_TEST_CASE(Pawn1_pieceBlockingMoveBy2SquaresTest){
        pawn2->setOnBoard(board1->getSquares(5,3));
        MovePtr move1=std::make_shared<Move>(pawn1,board1->getSquares(5,3));
        BOOST_TEST_REQUIRE(!player1->move(move1,board1,game->getMovesHistory()));
        move1=std::make_shared<Move>(pawn1,board1->getSquares(5,4));
        BOOST_TEST_REQUIRE(player1->move(move1,board1,game->getMovesHistory()));

    }
    BOOST_AUTO_TEST_CASE(Pawn1_captureSquareToLeftTest){
        pawn2->setSquare(board1->getSquares(4,5));
        BOOST_TEST(player2->getPieces().size()==2);
        MovePtr move1=std::make_shared<Move>(pawn1,board1->getSquares(4,5));
        BOOST_TEST_REQUIRE(player1->move(move1,board1,game->getMovesHistory()));
        game->getMovesHistory().push_back(move1);
        BOOST_TEST_REQUIRE(pawn2->getSquare()== nullptr);
        BOOST_TEST(player2->getPieces().size()==1);
//        for (int i = 0; i < game->getMovesHistory().size(); ++i) {
//            std::cout<<" x: "<<game->getMovesHistory().at(i)->getOldSquare()->getX()<<"\n";
//            std::cout<<" y: "<<game->getMovesHistory().at(i)->getOldSquare()->getY()<<"\n";
//            std::cout<<" x: "<<game->getMovesHistory().at(i)->getDestination()->getX()<<"\n";
//            std::cout<<" y: "<<game->getMovesHistory().at(i)->getDestination()->getY()<<"\n";
//        }
    }
    BOOST_AUTO_TEST_CASE(Pawn1_captureSquareToRightTest){
        pawn2->setSquare(board1->getSquares(6,5));
        BOOST_TEST(player2->getPieces().size()==2);
        MovePtr move1=std::make_shared<Move>(pawn1,board1->getSquares(6,5));
        BOOST_TEST_REQUIRE(player1->move(move1,board1,game->getMovesHistory()));
        game->getMovesHistory().push_back(move1);
        BOOST_TEST_REQUIRE(pawn2->getSquare()== nullptr);
        BOOST_TEST(player2->getPieces().size()==1);
    }
    BOOST_AUTO_TEST_CASE(Pawn2_pieceBlockingMoveByOneSquareTest){
        pawn2->setSquare(board1->getSquares(5,5));
        MovePtr move2=std::make_shared<Move>(pawn2,board1->getSquares(5,6));
        BOOST_TEST_REQUIRE(!player2->move(move2,board1,game->getMovesHistory()));
//        move2=std::make_shared<Move>(pawn2,board1->getSquares(5,6));
//        BOOST_TEST_REQUIRE(!player2->move(move2,board1,game->getMovesHistory()));
    }
    BOOST_AUTO_TEST_CASE(Pawn2_pieceBlockingMove2SquaresTest){
        pawn2->setSquare(board1->getSquares(5,2));
        pawn1->setSquare(board1->getSquares(5,4));
        MovePtr move2=std::make_shared<Move>(pawn2,board1->getSquares(5,4));
        BOOST_TEST_REQUIRE(!player2->move(move2,board1,game->getMovesHistory()));
        move2=std::make_shared<Move>(pawn2,board1->getSquares(5,3));
        BOOST_TEST_REQUIRE(player2->move(move2,board1,game->getMovesHistory()));
    }
    BOOST_AUTO_TEST_CASE(Pawn2_captureSquareToRightTest){
        pawn2->setSquare(board1->getSquares(5,5));
        pawn1->setSquare(board1->getSquares(6,6));
        BOOST_TEST(player1->getPieces().size()==1);
//                std::cout<<player2->getAvailableMoves(board1,game->getMovesHistory()).size()<<"\n";
//        for (int i = 0; i < player2->getAvailableMoves(board1,game->getMovesHistory()).size(); i++) {
//            std::cout<<i+1<<"."<<"\n";
//            std::cout<<" x: "<<player2->getAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getX()<<"\n";
//            std::cout<<" y: "<<player2->getAvailableMoves(board1,game->getMovesHistory()).at(i)->getDestination()->getY()<<"\n";
//        }
        MovePtr move2=std::make_shared<Move>(pawn2,board1->getSquares(6,6));
        BOOST_TEST_REQUIRE(player2->move(move2,board1,game->getMovesHistory()));
        BOOST_TEST(player1->getPieces().size()==0);
        BOOST_TEST(pawn1->getSquare()== nullptr);
        BOOST_TEST(board1->getSquares(6,6)->getPiece()== pawn2);
    }
    BOOST_AUTO_TEST_CASE(Pawn2_dontCaptureYourPiece){
        pawn2->setSquare(board1->getSquares(2,2));
        MovePtr move2=std::make_shared<Move>(pawn2,board1->getSquares(2,2));
        BOOST_TEST_REQUIRE(!player2->move(move2,board1,game->getMovesHistory()));
}
    BOOST_AUTO_TEST_CASE(Pawn1_enPassantTest){
        pawn2->setSquare(board1->getSquares(6,1));
        pawn1->setSquare(board1->getSquares(5,3));
        MovePtr move2=std::make_shared<Move>(pawn2,board1->getSquares(6,3));
        BOOST_TEST_REQUIRE(player2->move(move2,board1,game->getMovesHistory()));
        BOOST_TEST(player2->getPieces().size()==2);
        BOOST_TEST(pawn2==board1->getSquares(6,3)->getPiece());
        MovePtr move1=std::make_shared<Move>(pawn1,board1->getSquares(6,2));
        BOOST_TEST_REQUIRE(player1->move(move1,board1,game->getMovesHistory()));
        BOOST_TEST(board1->getSquares(6,2)->getPiece()==pawn1);
        BOOST_TEST(board1->getSquares(6,3)->getPiece()== nullptr);
        BOOST_TEST(player2->getPieces().size()==1);
    }
    BOOST_AUTO_TEST_CASE(Pawn1_enPassantFalseTest){
        pawn2->setSquare(board1->getSquares(6,1));
        pawn1->setSquare(board1->getSquares(5,3));
        MovePtr move2=std::make_shared<Move>(pawn2,board1->getSquares(6,3));
        BOOST_TEST_REQUIRE(player2->move(move2,board1,game->getMovesHistory()));
        game->getMovesHistory().push_back(move2);
        BOOST_TEST(player2->getPieces().size()==2);
        BOOST_TEST(pawn2==board1->getSquares(6,3)->getPiece());
        MovePtr move3=std::make_shared<Move>(pawn3,board1->getSquares(2,3));
        BOOST_TEST_REQUIRE(player2->move(move3,board1,game->getMovesHistory()));
        MovePtr move1=std::make_shared<Move>(pawn1,board1->getSquares(6,2));
        BOOST_TEST_REQUIRE(!player1->move(move1,board1,game->getMovesHistory()));
        BOOST_TEST(player2->getPieces().size()==2);
    }
    BOOST_AUTO_TEST_CASE(Pawn2_moveOutOfBoard){
        pawn2->setSquare(board1->getSquares(7,7));
        BOOST_TEST(pawn2->calculateAvailableMoves(board1,game->getMovesHistory()).size()==0);
        MovePtr move2=std::make_shared<Move>(pawn2,board1->getSquares(7,8));
        BOOST_TEST_REQUIRE(!player2->move(move2,board1,game->getMovesHistory()));
    }

BOOST_AUTO_TEST_SUITE_END()