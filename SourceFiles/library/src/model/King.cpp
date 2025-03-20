//
// Created by Piotr on 10.05.2023.
//
#include <string>
#include "model/King.h"
#include <iostream>
#include "model/Move.h"
#include "model/Player.h"
#include "model/Square.h"
#include "model/Rook.h"
#include "model/Board.h"
#include "functional"
#include "model/Pawn.h"

King::King(const PlayerPtr &player) : Piece(player), checked(false) {}

const std::string &King::getUnicodeWhite() const {
    return unicodeWhite;
}

const std::string &King::getUnicodeBlack() const {
    return unicodeBlack;
}

void King::showPieceImageWhite() {
    setlocale(LC_CTYPE,"");
    std::string a= getUnicodeWhite();
    std::cout << a;
}

void King::showPieceImageBlack() {
    setlocale(LC_CTYPE,"");
    std::string a= getUnicodeBlack();
    std::cout << a;
}

King::~King() {}

std::string King::getPieceInfo() {
    return "\nPiece: King\n "+Piece::getPieceInfo()+"\n  checked: "+(checked ?  "true" :"false");
}

/// \brief zwraca dostepne ruchy krola i sprawdza czy krol jest szachowany
/// \param board1
/// \param moveHistory
/// \return
std::vector<MovePtr> King::calculateAvailableMoves(const BoardPtr &board1, const std::vector<MovePtr> &moveHistory) {
    std::vector<MovePtr> kingMoves=Piece::getKingMoves(board1,moveHistory);
    if(!moveHistory.empty()){
        //PlayerPtr enemy=moveHistory.back()->getPiece()->getPlayer(); //nie szukaj na podstawie wektora tylko na podstawie samych pionkow
        std::vector<MovePtr> allEnemyMoves;
        std::vector<MovePtr> enemyMoves;
        PiecePtr piece;
        //zsumuj ruchy przeciwnika
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                piece=board1->getSquares(i,j)->getPiece();
                if(piece && piece->getPlayer()!=getPlayer()){ //sprawdz czy to pionek przeciwnika
                    if(piece && !std::dynamic_pointer_cast<King>(piece)){ //jesli figura nie jest krolem to oblicz ruchy
                        enemyMoves=piece->calculateAvailableMoves(board1,moveHistory);
                        //jesli figura jest pionkiem to nie bierz pod uwage ruchu do przodu pionka jako zagrozenia
                        if( !enemyMoves.empty() && std::dynamic_pointer_cast<Pawn>(piece)){
                            enemyMoves.erase(enemyMoves.begin());
                        } else{
                            enemyMoves = piece->calculateAvailableMoves(board1,moveHistory);
                        }
                        allEnemyMoves.insert(allEnemyMoves.end(),std::make_move_iterator(enemyMoves.begin()),std::make_move_iterator(enemyMoves.end()));
                    } else{
                        //otrzymanie ruchow przeciwnego krola metoda getKingMoves() aby nie spowodowac nieskocznonej rekurencji
                        enemyMoves=piece->getKingMoves(board1,moveHistory);
                        allEnemyMoves.insert(allEnemyMoves.end(),std::make_move_iterator(enemyMoves.begin()),std::make_move_iterator(enemyMoves.end()));
                    }
                }
            }
        }
        std::function<bool(const SquarePtr&)> findInAllEnemyMoves=[allEnemyMoves](const SquarePtr& square){
            for (int i = 0; i < allEnemyMoves.size(); ++i) {
                if(allEnemyMoves.at(i)->getDestination()==square){
                    return true;
                }
            }
            return false;
        };
//        std::cout<<allEnemyMoves.size()<<"\n";
//        for (int i = 0; i < allEnemyMoves.size(); i++) {
//            std::cout<<i+1<<"."<<"\n";
//            std::cout<<allEnemyMoves.at(i)->getPiece()->getPieceInfo()<<"\n";
//            std::cout<<" x: "<<allEnemyMoves.at(i)->getDestination()->getX()<<"\n";
//            std::cout<<" y: "<<allEnemyMoves.at(i)->getDestination()->getY()<<"\n";
//        }

        //funkcja do sprawdzenia czy dane pole jest atakowane
        for (int i = 0; i < kingMoves.size(); ) {
            if(findInAllEnemyMoves(kingMoves.at(i)->getDestination())){
                kingMoves.erase(kingMoves.begin()+i);
            } else{
                i++;
            }
        }
        if(findInAllEnemyMoves(getSquare())){
            setChecked(true);
        } else{
            setChecked(false);
        }
        //jesli krol nie jest szachowany to znajdz 2 wieze
        if(!isChecked()){
            PiecePtr rook1= nullptr; //lewa wieza (dolna)
            PiecePtr rook2= nullptr; //prawa wieza (gorna)
            if(getPlayer()->isWhite()){
                rook1=std::dynamic_pointer_cast<Rook>(board1->getSquares(7,7)->getPiece());
                rook2=std::dynamic_pointer_cast<Rook>(board1->getSquares(0,7)->getPiece());
            } else{
                rook1=std::dynamic_pointer_cast<Rook>(board1->getSquares(7,0)->getPiece());
                rook2=std::dynamic_pointer_cast<Rook>(board1->getSquares(0,0)->getPiece());

            }

            for (int i = 0; i < moveHistory.size(); i++) { //sprawdz czy krol sie ruszyl
                if(moveHistory.at(i)->getPiece()==shared_from_this()){
                    return kingMoves;
                }
            }
            //poszukaj wiez w historii ruchow
            for (int i = 0; i < moveHistory.size(); ++i) {
                if(moveHistory.at(i)->getPiece()==rook1){
                    rook1= nullptr;
                } else if (moveHistory.at(i)->getPiece()==rook2){
                    rook2= nullptr;
                }
            }
            bool clear = true;
            int x=0,y=0;

            if(rook1) { //dluga roszada - do lewej wiezy (dolna)
                x=rook1->getSquare()->getX();
                y=rook1->getSquare()->getY();
                for (int i = 1; i < 4; ++i) { //sprawdzenie czy pola przez ktore przejdzie krol sa wolne lub czy sa atakowane
                    if (board1->getSquares(x - i, y)->getPiece() ||
                        (i > 1 && findInAllEnemyMoves(board1->getSquares(x - i, y)))) {
                        //std::cout<<board1->getSquares(x - i, y)->getSquareInfo()<<"\n";
                        clear = false;
                    }
                }
                if (clear) { //jesli pola przez ktore przejdzie krol nie sa atakowane i nie stanie na szachu
                    kingMoves.push_back(std::make_shared<Move>(shared_from_this(), board1->getSquares(getSquare()->getX() + 2, y)));
                }
            }
            clear = true;
            if(rook2){ //krotka roszada - do prawej wiezy
                x=rook2->getSquare()->getX();
                y=rook2->getSquare()->getY();
                for (int i = 1; i < 3; ++i) {
                    //sprawdzenie czy pola miedzy wieza i krolem sa wolne lub czy sa atakowane
                    if(board1->getSquares(x+i,y)->getPiece() || findInAllEnemyMoves(board1->getSquares(x+i,y)) ){
                        clear= false;
                    }
                }
                if(clear){//jesli pola przez ktore przejdzie krol nie sa atakowane i nie stanie na szachu
                    kingMoves.push_back(std::make_shared<Move>(shared_from_this(), board1->getSquares( getSquare()->getX()-2,y)));
                }
            }
        }
    }
    //std::cout<<"No moves history\n";
    return kingMoves;
}

bool King::isChecked() const {
    return checked;
}

void King::setChecked(bool checked) {
    King::checked = checked;
}

std::string King::getClassName() {
    return "King";
}