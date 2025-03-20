//
// Created by Piotr on 10.05.2023.
//
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
#include "model/King.h"
#include "model/Queen.h"
#include "../exceptions/BoardException.h"
#include "../exceptions/PlayerException.h"

struct TestSuitePlayerFixture{
    std::shared_ptr<Board> board1=std::make_shared<Board>();
    PlayerPtr player1=std::make_shared<HumanPlayer>("Bob",true);
    PlayerPtr player2=std::make_shared<HumanPlayer>("Josh",false);
    PiecePtr rook1=std::make_shared<Rook>(player1);
    PiecePtr rook2=std::make_shared<Rook>(player2);
    PiecePtr king1=std::make_shared<King>(player1);
    PiecePtr king2=std::make_shared<King>(player2);
    GamePtr game=std::make_shared<Game>(board1,player1,player2);
    PiecePtr pawn2=std::make_shared<Pawn>(player2);
    TestSuitePlayerFixture(){
//        king1->setOnBoard(board1->getSquares(6,7));
//        king2->setOnBoard(board1->getSquares(0,0));
//        rook2->setOnBoard(board1->getSquares(7,1));
//        rook1->setOnBoard(board1->getSquares(2, 7));
//        pawn2->setOnBoard(board1->getSquares(2,2));
    }
    ~TestSuitePlayerFixture(){}
};

BOOST_FIXTURE_TEST_SUITE(TestSuitePlayer,TestSuitePlayerFixture)
    BOOST_AUTO_TEST_CASE(Player_getAvailableMovesWhenChecked_KingRookVsRook) {
        king1->setOnBoard(board1->getSquares(6,7));
        king2->setOnBoard(board1->getSquares(0,0));
        rook2->setOnBoard(board1->getSquares(7,1));
        rook1->setOnBoard(board1->getSquares(2, 7));
        pawn2->setOnBoard(board1->getSquares(2,2));
        MovePtr move1 = std::make_shared<Move>(rook1, board1->getSquares(0, 7));
        BOOST_TEST_REQUIRE(player1->move(move1, board1, game->getMovesHistory()));
        //game->getMovesHistory().push_back(move1);
        std::vector<MovePtr> p2moves=player2->getAvailableMoves(board1, game->getMovesHistory());
//        for (int i = 0; i < p2moves.size(); i++) {
//            std::cout<<i+1<<"."<<"\n";
//            std::cout<<" x: "<<p2moves.at(i)->getDestination()->getX()<<"\n";
//            std::cout<<" y: "<<p2moves.at(i)->getDestination()->getY()<<"\n";
//        }
        BOOST_TEST(std::dynamic_pointer_cast<King>(king2)->isChecked());
        BOOST_TEST(player2->getAvailableMoves(board1, game->getMovesHistory()).size() == 3);
        BOOST_TEST(player2->getAvailableMoves(board1, game->getMovesHistory()).at(2)->getPiece()==rook2);
        BOOST_TEST(player2->getAvailableMoves(board1, game->getMovesHistory()).at(2)->getDestination()==board1->getSquares(0,1));
    }
    BOOST_AUTO_TEST_CASE(Player_getAvailableMovesWhenChecked_KingPawnVsRook){
        king1->setOnBoard(board1->getSquares(6,7));
        king2->setOnBoard(board1->getSquares(0,0));
        rook2->setOnBoard(board1->getSquares(7,1));
        rook1->setOnBoard(board1->getSquares(2, 7));
        pawn2->setOnBoard(board1->getSquares(2,2));
        //rook2->setOnBoard(board1->getSquares(7,1));
        PiecePtr pawn2=std::make_shared<Pawn>(player2);
        pawn2->setOnBoard(board1->getSquares(1,5));
        MovePtr move2=std::make_shared<Move>(pawn2,board1->getSquares(1,6));
        BOOST_TEST_REQUIRE(player2->move(move2,board1,game->getMovesHistory()));
        MovePtr move1 = std::make_shared<Move>(rook1, board1->getSquares(0, 7));
        BOOST_TEST_REQUIRE(player1->move(move1, board1, game->getMovesHistory()));
        std::vector<MovePtr> p2moves=player2->getAvailableMoves(board1, game->getMovesHistory());
        BOOST_TEST(player2->getAvailableMoves(board1, game->getMovesHistory()).size() == 4);
        BOOST_TEST(player2->getAvailableMoves(board1, game->getMovesHistory()).at(3)->getPiece()==pawn2);
        //zbijanie szachujacej figury
        BOOST_TEST(player2->getAvailableMoves(board1, game->getMovesHistory()).at(3)->getDestination()==board1->getSquares(0,7));
    }
    BOOST_AUTO_TEST_CASE(Player_getAvailableMovesWhenChecked_KingVsRookPawn){
        king1->setOnBoard(board1->getSquares(6,7));
        king2->setOnBoard(board1->getSquares(0,0));
        rook2->setOnBoard(board1->getSquares(7,1));
        rook1->setOnBoard(board1->getSquares(2, 7));
        pawn2->setOnBoard(board1->getSquares(2,2));
        rook1->capture(board1->getSquares(7,1));
        MovePtr move=std::make_shared<Move>(rook1,board1->getSquares(1,7));
        BOOST_TEST_REQUIRE(player1->move(move,board1,game->getMovesHistory()));
        PiecePtr pawn1=std::make_shared<Pawn>(player1);
        pawn1->setOnBoard(board1->getSquares(1,2));
        MovePtr move2=std::make_shared<Move>(pawn1,board1->getSquares(1,1));
        BOOST_TEST_REQUIRE(player1->move(move2,board1,game->getMovesHistory()));
        std::vector<MovePtr> p2moves=player2->getAvailableMoves(board1, game->getMovesHistory());
//        for (int i = 0; i < p2moves.size(); i++) {
//            std::cout<<i+1<<"."<<"\n";
//            std::cout<<" x: "<<p2moves.at(i)->getDestination()->getX()<<"\n";
//            std::cout<<" y: "<<p2moves.at(i)->getDestination()->getY()<<"\n";
//        }
        BOOST_TEST_REQUIRE(std::dynamic_pointer_cast<King>(king2)->isChecked());
        BOOST_TEST(player2->getAvailableMoves(board1, game->getMovesHistory()).size() == 2);
        BOOST_TEST(player2->getAvailableMoves(board1, game->getMovesHistory()).at(0)->getPiece()==king2);
        BOOST_TEST(player2->getAvailableMoves(board1, game->getMovesHistory()).at(0)->getDestination()==board1->getSquares(0,1));
    }

    BOOST_AUTO_TEST_CASE(Player_castlingLongWhiteTest){
        king1->setOnBoard(board1->getSquares(6,7));
        king2->setOnBoard(board1->getSquares(0,0));
        rook2->setOnBoard(board1->getSquares(7,1));
        rook1->setOnBoard(board1->getSquares(2, 7));
        pawn2->setOnBoard(board1->getSquares(2,2));
        king1->makeMove(board1->getSquares(3,7));
        rook1->makeMove(board1->getSquares(7,7));
        BOOST_TEST(board1->getSquares(3,7)->getPiece()== king1);
        BOOST_TEST(board1->getSquares(7,7)->getPiece()== rook1);
        MovePtr test=std::make_shared<Move>(pawn2,board1->getSquares(2,3));
        BOOST_TEST_REQUIRE(player2->move(test,board1,game->getMovesHistory()));
        MovePtr move1 = std::make_shared<Move>(king1, board1->getSquares(5, 7));
        std::vector<MovePtr> p1moves=king1->calculateAvailableMoves(board1, game->getMovesHistory());
        BOOST_TEST_REQUIRE(player1->move(move1, board1, game->getMovesHistory()));
        BOOST_TEST(board1->getSquares(5,7)->getPiece()==king1);
        BOOST_TEST(board1->getSquares(4,7)->getPiece()==rook1);
        BOOST_TEST(board1->getSquares(3,7)->getPiece()== nullptr);
        BOOST_TEST(board1->getSquares(7,7)->getPiece()== nullptr);
}
    BOOST_AUTO_TEST_CASE(Player_castlingShortWhiteTest){
        king1->setOnBoard(board1->getSquares(6,7));
        king2->setOnBoard(board1->getSquares(0,0));
        rook2->setOnBoard(board1->getSquares(7,1));
        rook1->setOnBoard(board1->getSquares(2, 7));
        pawn2->setOnBoard(board1->getSquares(2,2));
        MovePtr test=std::make_shared<Move>(pawn2,board1->getSquares(2,3));
        BOOST_TEST_REQUIRE(player2->move(test,board1,game->getMovesHistory()));
        king1->makeMove(board1->getSquares(3,7));
        rook1->makeMove(board1->getSquares(0,7));
        BOOST_TEST(board1->getSquares(3,7)->getPiece()== king1);
        BOOST_TEST(board1->getSquares(0,7)->getPiece()== rook1);
        MovePtr move1 = std::make_shared<Move>(king1, board1->getSquares(1, 7));
        std::vector<MovePtr> p1moves=king1->calculateAvailableMoves(board1, game->getMovesHistory());
        BOOST_TEST_REQUIRE(player1->move(move1, board1, game->getMovesHistory()));
        BOOST_TEST(board1->getSquares(1,7)->getPiece()==king1);
        BOOST_TEST(board1->getSquares(2,7)->getPiece()==rook1);
        BOOST_TEST(board1->getSquares(3,7)->getPiece()== nullptr);
        BOOST_TEST(board1->getSquares(0,7)->getPiece()== nullptr);
    }
    BOOST_AUTO_TEST_CASE(Player_castlingShortWhite_fullBoard_blockingPieces_Test){
        game->getGameBoard()->fill(player1,player2);
        king1=game->getGameBoard()->getSquares(3,7)->getPiece();
        rook1=game->getGameBoard()->getSquares(0,7)->getPiece();
        PiecePtr knight1=game->getGameBoard()->getSquares(1,7)->getPiece();
        PiecePtr bishop1=game->getGameBoard()->getSquares(2,7)->getPiece();
        //ruch pionkiem
        MovePtr move1 = std::make_shared<Move>(game->getGameBoard()->getSquares(1,6)->getPiece(), game->getGameBoard()->getSquares(1,5));
        BOOST_TEST_REQUIRE(player1->move(move1, game->getGameBoard(), game->getMovesHistory()));
        MovePtr move2 = std::make_shared<Move>(game->getGameBoard()->getSquares(1,1)->getPiece(), game->getGameBoard()->getSquares(1,2));

        BOOST_TEST_REQUIRE(player2->move(move2, game->getGameBoard(), game->getMovesHistory()));
        move1 = std::make_shared<Move>(bishop1, game->getGameBoard()->getSquares(1, 6));
        BOOST_TEST_REQUIRE(player1->move(move1, game->getGameBoard(), game->getMovesHistory()));
        move1 = std::make_shared<Move>(knight1, game->getGameBoard()->getSquares(0, 5));
        BOOST_TEST_REQUIRE(player1->move(move1, game->getGameBoard(), game->getMovesHistory()));
        BOOST_TEST(game->getGameBoard()->getSquares(1,7)->getPiece()== nullptr);
        BOOST_TEST(game->getGameBoard()->getSquares(2,7)->getPiece()== nullptr);
        move1 = std::make_shared<Move>(king1, board1->getSquares(1, 7));
        BOOST_TEST_REQUIRE(player1->move(move1, board1, game->getMovesHistory()));
    }
    BOOST_AUTO_TEST_CASE(Player_castlingShortBlackTest){
        king1->setOnBoard(board1->getSquares(6,7));
        king2->setOnBoard(board1->getSquares(0,0));
        rook2->setOnBoard(board1->getSquares(7,1));
        rook1->setOnBoard(board1->getSquares(2, 7));
        pawn2->setOnBoard(board1->getSquares(2,2));
        king2->makeMove(board1->getSquares(3,0));
        rook2->makeMove(board1->getSquares(0,0));
        BOOST_TEST(board1->getSquares(3,0)->getPiece()== king2);
        BOOST_TEST(board1->getSquares(0,0)->getPiece()== rook2);
        MovePtr test=std::make_shared<Move>(king1,board1->getSquares(7,7));
        BOOST_TEST_REQUIRE(player1->move(test,board1,game->getMovesHistory()));
        MovePtr move1 = std::make_shared<Move>(king2, board1->getSquares(1, 0));
        std::vector<MovePtr> p1moves=king2->calculateAvailableMoves(board1, game->getMovesHistory());
        BOOST_TEST_REQUIRE(player2->move(move1, board1, game->getMovesHistory()));
        BOOST_TEST(board1->getSquares(1,0)->getPiece()==king2);
        BOOST_TEST(board1->getSquares(2,0)->getPiece()==rook2);
        BOOST_TEST(board1->getSquares(3,0)->getPiece()== nullptr);
        BOOST_TEST(board1->getSquares(0,0)->getPiece()== nullptr);
    }
    BOOST_AUTO_TEST_CASE(Player_castlingLongBlackTest){
        king1->setOnBoard(board1->getSquares(6,7));
        king2->setOnBoard(board1->getSquares(0,0));
        rook2->setOnBoard(board1->getSquares(7,1));
        rook1->setOnBoard(board1->getSquares(2, 7));
        pawn2->setOnBoard(board1->getSquares(2,2));
        king2->makeMove(board1->getSquares(3,0));
        rook2->makeMove(board1->getSquares(7,0));
        MovePtr test=std::make_shared<Move>(king1,board1->getSquares(6,6));
        BOOST_TEST_REQUIRE(player1->move(test,board1,game->getMovesHistory()));
        MovePtr move1 = std::make_shared<Move>(king2, board1->getSquares(5, 0));
        //BOOST_TEST(!std::dynamic_pointer_cast<King>(king2)->isChecked());
        BOOST_TEST_REQUIRE(player2->move(move1, board1, game->getMovesHistory()));
        BOOST_TEST(board1->getSquares(5,0)->getPiece()==king2);
        BOOST_TEST(board1->getSquares(4,0)->getPiece()==rook2);
        BOOST_TEST(board1->getSquares(3,0)->getPiece()== nullptr);
        BOOST_TEST(board1->getSquares(7,0)->getPiece()== nullptr);
    }

    BOOST_AUTO_TEST_CASE(Player_promotionIntoKnightTest){
        king1->setOnBoard(board1->getSquares(6,7));
        king2->setOnBoard(board1->getSquares(0,0));
        rook2->setOnBoard(board1->getSquares(7,1));
        rook1->setOnBoard(board1->getSquares(2, 7));
        pawn2->setOnBoard(board1->getSquares(2,2));
    PiecePtr pawn1=std::make_shared<Pawn>(player1);
    pawn1->setOnBoard(board1->getSquares(4,2));
    MovePtr move1=std::make_shared<Move>(pawn1,board1->getSquares(4,1));
    BOOST_TEST_REQUIRE(player1->move(move1,game->getGameBoard(),game->getMovesHistory()));
    int size=player1->getPieces().size();
    player1->promotion(pawn1,1);
    BOOST_TEST(std::dynamic_pointer_cast<Knight>(game->getGameBoard()->getSquares(4,1)->getPiece()));
    BOOST_TEST_REQUIRE(player1->getPieces().back()==board1->getSquares(4,1)->getPiece());
    BOOST_TEST_REQUIRE(player1->getPieces().size()==size);
}
    BOOST_AUTO_TEST_CASE(Player_promotionIntoBishopTest){
        king1->setOnBoard(board1->getSquares(6,7));
        king2->setOnBoard(board1->getSquares(0,0));
        rook2->setOnBoard(board1->getSquares(7,1));
        rook1->setOnBoard(board1->getSquares(2, 7));
        pawn2->setOnBoard(board1->getSquares(2,2));
        PiecePtr pawn1=std::make_shared<Pawn>(player1);
        pawn1->setOnBoard(board1->getSquares(4,2));
        MovePtr move1=std::make_shared<Move>(pawn1,board1->getSquares(4,1));
        BOOST_TEST_REQUIRE(player1->move(move1,game->getGameBoard(),game->getMovesHistory()));
        int size=player1->getPieces().size();
        player1->promotion(pawn1,2);
        BOOST_TEST(std::dynamic_pointer_cast<Bishop>(game->getGameBoard()->getSquares(4,1)->getPiece()));
        BOOST_TEST_REQUIRE(player1->getPieces().back()==board1->getSquares(4,1)->getPiece());
        BOOST_TEST_REQUIRE(player1->getPieces().size()==size);
        MovePtr move2=std::make_shared<Move>(pawn2,board1->getSquares(2,3));
        BOOST_TEST_REQUIRE(player2->move(move2,game->getGameBoard(),game->getMovesHistory()));
}
    BOOST_AUTO_TEST_CASE(Player_promotionIntoRookTest){
        king1->setOnBoard(board1->getSquares(6,7));
        king2->setOnBoard(board1->getSquares(0,0));
        rook2->setOnBoard(board1->getSquares(7,1));
        rook1->setOnBoard(board1->getSquares(2, 7));
        pawn2->setOnBoard(board1->getSquares(2,2));
        PiecePtr pawn1=std::make_shared<Pawn>(player1);
        pawn1->setOnBoard(board1->getSquares(4,2));
        MovePtr move1=std::make_shared<Move>(pawn1,board1->getSquares(4,1));
        BOOST_TEST_REQUIRE(player1->move(move1,game->getGameBoard(),game->getMovesHistory()));
        int size=player1->getPieces().size();
        player1->promotion(pawn1,3);
        BOOST_TEST(std::dynamic_pointer_cast<Rook>(game->getGameBoard()->getSquares(4,1)->getPiece()));
        BOOST_TEST_REQUIRE(player1->getPieces().back()==board1->getSquares(4,1)->getPiece());
        BOOST_TEST_REQUIRE(player1->getPieces().size()==size);
    }
    BOOST_AUTO_TEST_CASE(Player_promotionIntoQueenTest){
        king1->setOnBoard(board1->getSquares(6,7));
        king2->setOnBoard(board1->getSquares(0,0));
        rook2->setOnBoard(board1->getSquares(7,1));
        rook1->setOnBoard(board1->getSquares(2, 7));
        pawn2->setOnBoard(board1->getSquares(2,2));
        PiecePtr pawn1=std::make_shared<Pawn>(player1);
        pawn1->setOnBoard(board1->getSquares(4,2));
        MovePtr move1=std::make_shared<Move>(pawn1,board1->getSquares(4,1));
        BOOST_TEST_REQUIRE(player1->move(move1,game->getGameBoard(),game->getMovesHistory()));
        int size=player1->getPieces().size();
        player1->promotion(pawn1,4);
        BOOST_TEST(std::dynamic_pointer_cast<Queen>(game->getGameBoard()->getSquares(4,1)->getPiece()));
        BOOST_TEST_REQUIRE(player1->getPieces().back()==board1->getSquares(4,1)->getPiece());
        BOOST_TEST_REQUIRE(player1->getPieces().size()==size);
    }
    BOOST_AUTO_TEST_CASE(Player2_promotionIntoQueenTest){
        king1->setOnBoard(board1->getSquares(6,7));
        king2->setOnBoard(board1->getSquares(0,0));
        rook2->setOnBoard(board1->getSquares(7,1));
        rook1->setOnBoard(board1->getSquares(2, 7));
        pawn2->setOnBoard(board1->getSquares(2,2));
        PiecePtr pawn1=std::make_shared<Pawn>(player2);
        pawn1->setOnBoard(board1->getSquares(4,5));
        MovePtr move1=std::make_shared<Move>(pawn1,board1->getSquares(4,6));
        BOOST_TEST_REQUIRE(player2->move(move1,game->getGameBoard(),game->getMovesHistory()));
        int size=player2->getPieces().size();
        player2->promotion(pawn1,4);
        BOOST_TEST(std::dynamic_pointer_cast<Queen>(game->getGameBoard()->getSquares(4,6)->getPiece()));
        BOOST_TEST_REQUIRE(player2->getPieces().back()==board1->getSquares(4,6)->getPiece());
        BOOST_TEST_REQUIRE(player2->getPieces().size()==size);
    }
    bool comm_mat(const PlayerException& exception){
        std::string msg=exception.what();
        return msg=="MAT";
    }
    BOOST_AUTO_TEST_CASE(Player1_matedTest){
        king1->setOnBoard(board1->getSquares(6,7));
        king2->setOnBoard(board1->getSquares(0,0));
        rook2->setOnBoard(board1->getSquares(7,1));
        PiecePtr rook3=std::make_shared<Rook>(player2);
        rook3->setOnBoard(board1->getSquares(1,0));
        BOOST_TEST(!std::dynamic_pointer_cast<King>(king1)->isChecked());
        MovePtr move=std::make_shared<Move>(rook2,game->getGameBoard()->getSquares(6,1));
        BOOST_TEST_REQUIRE(player2->move(move,game->getGameBoard(),game->getMovesHistory()));
        std::vector<MovePtr> king1Moves=player1->getAvailableMoves(board1,game->getMovesHistory());
        BOOST_TEST(std::dynamic_pointer_cast<King>(king1)->isChecked());
        move=std::make_shared<Move>(king1,game->getGameBoard()->getSquares(7,7));
        BOOST_TEST_REQUIRE(player1->move(move,game->getGameBoard(),game->getMovesHistory()));
        king1Moves=player1->getAvailableMoves(game->getGameBoard(),game->getMovesHistory());
        BOOST_TEST(!std::dynamic_pointer_cast<King>(king1)->isChecked());
        move=std::make_shared<Move>(rook3,game->getGameBoard()->getSquares(7,0));
        BOOST_TEST_REQUIRE(player2->move(move,game->getGameBoard(),game->getMovesHistory()));
        BOOST_REQUIRE_EXCEPTION(player1->getAvailableMoves(game->getGameBoard(),game->getMovesHistory()),PlayerException,
                                comm_mat);
    }

BOOST_AUTO_TEST_SUITE_END()