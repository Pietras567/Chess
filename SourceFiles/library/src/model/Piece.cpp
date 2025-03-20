//
// Created by Piotr on 10.05.2023.
//
#include <memory>
#include <iostream>
#include "model/Piece.h"
#include "model/Square.h"
#include "model/Move.h"
#include "model/HumanPlayer.h"
#include "model/Board.h"
#include "../exceptions/PieceException.h"
#include "vector"

Piece::Piece(const PlayerPtr &player) : square(nullptr), player(player) {
}

Piece::~Piece() {}

const SquarePtr &Piece::getSquare() const {
    return square;
}
/// \brief przypisuje pole do pionka i pionka do pola, w przypadku przekazania nullptr czysci takze pole
/// \param squarePtr
void Piece::setSquare(const SquarePtr &squarePtr) {
//    if (getSquare()== nullptr && squarePtr!= nullptr){ //przy umieszczeniu na planszy
//        getPlayer()->getPieces().push_back(shared_from_this());
//    }
    if(squarePtr== nullptr){
        square->setPiece(nullptr);
    }
    Piece::square = squarePtr;
    if(square!= nullptr && square->getPiece() != shared_from_this()  ){
        square->setPiece(shared_from_this());
    }
}
/// \brief umieszcza pionek na planszy, przypisuje go do pola i dodaje do zbioru pionkow gracza
/// \param squarePtr
void Piece::setOnBoard(const SquarePtr &squarePtr){
    getPlayer()->getPieces().push_back(shared_from_this());
    setSquare(squarePtr);
}

std::string Piece::getPieceInfo() {
    std::string napis;
    if(square!= nullptr){
        napis+=" square: x: "+std::to_string(square->getX())+", y: "+std::to_string(square->getY())+"";
    } else{
        napis+=" square: not placed\n";
    }
    return napis;
}

const PlayerPtr & Piece::getPlayer() const {
    return player;
}

/// \brief Przeprowadza zbicie figury, odpina pionka od pola i pole od pionka, usuwa zbitego pionka z dostepnych pionkow gracza
/// \param squarePtr - pole z ktorego zbic pionka
void Piece::capture(const SquarePtr& squarePtr) {
    if(squarePtr->getPiece()== nullptr){
        throw PieceException("Piece::capture: no Piece placed on this Square");
    }
    PiecePtr capturedPiece=squarePtr->getPiece();
    //squarePtr->setPiece(nullptr);
    capturedPiece->setSquare(nullptr);
    for (int i = 0; i < capturedPiece->getPlayer()->getPieces().size(); ++i) { //usuwanie zbitego pionka z pionkow gracza
        if(capturedPiece->getPlayer()->getPieces().at(i)==capturedPiece){
            capturedPiece->getPlayer()->getPieces().erase(capturedPiece->getPlayer()->getPieces().begin()+i);
            return;
        }
    }
}

void Piece::makeMove(const SquarePtr& sq) {
    if (sq->getPiece()!= nullptr){ //zbicie figury
        capture(sq);
    }
    SquarePtr oldSquare=getSquare();
    setSquare(sq);
    oldSquare->setPiece(nullptr);
    //getBoard()->recalculateAvailableMoves();
}

int Piece::getDirection() const {
    if(getPlayer()->isWhite()){
        return -1;
    } else{
        return 1;
    }
}

std::vector<MovePtr> Piece::getLshapedMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory) {
    if(board1== nullptr){
        throw PieceException("Piece::getLshapedMoves: board is nullptr");
    }
    std::vector<MovePtr> availableMoves;
    MovePtr move;
    int x=getSquare()->getX();
    int y=getSquare()->getY();
    SquarePtr sq1;
    SquarePtr sq2;
    for (int i = -1; i < 2; i+=2) { // sprawdzanie kierunkow kolejno:  1. -x,-y; 2. x,-y; 3. -x,y; 4. x,y;
//        SquarePtr sq=board1->getSquares(x-1 , y+2);
//        SquarePtr sq=board1->getSquares(x+1 , y+2);
//        SquarePtr sq=board1->getSquares(x+2 , y-1);
//        SquarePtr sq=board1->getSquares(x+2 , y+1);
        for (int j = -1; j < 2; j+=2) {
            sq1=board1->getSquares(x+(1*j) , y+(2*i) );
            if( sq1 && ( !sq1->getPiece() || sq1->getPiece()->getPlayer()!=getPlayer()) ){ //sprawdz czy pionek przeciwnika
                move=std::make_shared<Move>(shared_from_this(),sq1);
                availableMoves.push_back(move);
            }
            sq2=board1->getSquares(x+(2*i) , y+(1*j) );
            if( sq2 && ( !sq2->getPiece() || sq2->getPiece()->getPlayer()!=getPlayer()) ){ //sprawdz czy pionek przeciwnika
                move=std::make_shared<Move>(shared_from_this(),sq2);
                availableMoves.push_back(move);
            }
        }
    }
    return availableMoves;
}

std::vector<MovePtr> Piece::getDiagonalMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory) {
    if( !board1 ){
        throw PieceException("Piece::getDiagonalMoves: board is nullptr");
    }
    std::vector<MovePtr> availableMoves;
    MovePtr move;
    SquarePtr sq;
    int x=getSquare()->getX();
    int y=getSquare()->getY();
    int k=1;
    for (int i = -1; i < 2; i+=2) { // sprawdzanie kierunkow kolejno:  1. -x,-y; 2. x,-y; 3. -x,y; 4. x,y;
        for (int j = -1; j < 2; j+=2) {
            k=1;
            //idz po przekatnej w kierunku dopoki koniec planszy lub wlasny pionek na polu
            while ( board1->getSquares(x+(k*j),y+(k*i)) ){
                sq=board1->getSquares(x+(k*j),y+(k*i));
                if (sq->getPiece() != nullptr && sq->getPiece()->getPlayer() == getPlayer()){ // wlasna figura na polu, zmiana kierunku
                    break;
                } else if ( !sq->getPiece() ){ //jesli puste pole to dodaj pole i sprawdz kolejne
                    move=std::make_shared<Move>(shared_from_this(),sq);
                    availableMoves.push_back(move);
                }
                else{
                    move=std::make_shared<Move>(shared_from_this(),sq); //jesli pionek przeciwnika to dodaj pole i zmien kierunek
                    availableMoves.push_back(move);
                    break;
                }
                k++;
            }

        }
    }
    return availableMoves;

}

std::vector<MovePtr> Piece::getVerticalMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory) {
    if( !board1){
        throw PieceException("Piece::getVerticalMoves: board is nullptr");
    }
    std::vector<MovePtr> availableMoves;
    MovePtr move;
    SquarePtr sq;
    int x = getSquare()->getX();
    int y = getSquare()->getY();
    int k = 1;
        for (int i = -1; i < 2; i += 2) { // sprawdzanie kierunkow kolejno:  1. -x,y; 2. x,y;
            k = 1;
            while (board1->getSquares(x + (k * i), y) ) { // idz w kierunku dopoki koniec planszy
                sq = board1->getSquares(x + (k * i), y);
                if (sq->getPiece() && sq->getPiece()->getPlayer() == getPlayer()){ // wlasna figura na polu, zmiana kierunku
                    break;
                }
                else if ( !sq->getPiece() ) { //jesli puste pole to dodaj pole i sprawdz kolejne
                    move = std::make_shared<Move>(shared_from_this(), sq);
                    availableMoves.push_back(move);
                } else {
                    move = std::make_shared<Move>(shared_from_this(),sq); //jesli pionek przeciwnika to dodaj pole i zmien kierunek
                    availableMoves.push_back(move);
                    break;
                }
                k++;
            }
    }
    return availableMoves;
}

std::vector<MovePtr> Piece::getHorizontalMoves(const BoardPtr& board1, const std::vector<MovePtr>& moveHistory) {
    if( !board1){
        throw PieceException("Piece::getHorizontalMoves: board is nullptr");
    }
    std::vector<MovePtr> availableMoves;
    MovePtr move;
    SquarePtr sq;
    int x = getSquare()->getX();
    int y = getSquare()->getY();
    int k = 1;
        for (int i = -1; i < 2; i += 2) { // sprawdzanie kierunkow kolejno:  1. -x,y; 2. x,y;
            k = 1;
            while (board1->getSquares(x, y + (k * i)) ) {  // w kierunku dopoki koniec planszy
                sq = board1->getSquares(x, y + (k * i));
                if (sq->getPiece() && sq->getPiece()->getPlayer() == getPlayer()) { // wlasna figura na polu, zmiana kierunku
                    break;
                }
                else if ( !sq->getPiece() ) { //jesli puste pole to dodaj pole i sprawdz kolejne
                    move = std::make_shared<Move>(shared_from_this(), sq);
                    availableMoves.push_back(move);
                }
                else {
                    move = std::make_shared<Move>(shared_from_this(),sq); //jesli pionek przeciwnika to dodaj pole i i zmien kierunek
                    availableMoves.push_back(move);
                    break;
                }
                k++;
            }
    }
    return availableMoves;
}

std::vector<MovePtr> Piece::getKingMoves(const BoardPtr &board1, const std::vector<MovePtr> &moveHistory) {
    if( !board1){
        throw PieceException("Piece::getKingMoves: board is nullptr");
    }
    std::vector<MovePtr> availableMoves;
    MovePtr move;
    SquarePtr sq;
    int x = getSquare()->getX();
    int y = getSquare()->getY();

    for (int i = -1; i < 2; i+=2) { // sprawdzanie kierunkow kolejno:  1. -x,-y; 2. x,-y; 3. -x,y; 4. x,y;
        for (int j = -1; j < 2; j++) {
            sq=board1->getSquares(x + (1 * j), y + (1 * i) );
            if(sq){
                if (sq->getPiece() && sq->getPiece()->getPlayer() != getPlayer()) { //jesli pionek przeciwnika to dodaj pole
                    move = std::make_shared<Move>(shared_from_this(),sq);
                    availableMoves.push_back(move);
                }
                else if ( !sq->getPiece() ) { //jesli puste pole to dodaj pole i sprawdz kolejne
                    move = std::make_shared<Move>(shared_from_this(), sq);
                    availableMoves.push_back(move);
                }
            }
        }
        sq=board1->getSquares(x+i,y);
        if( sq && ( !sq->getPiece() || sq->getPiece()->getPlayer() != getPlayer() ) ){
            move = std::make_shared<Move>(shared_from_this(), sq);
            availableMoves.push_back(move);
        }
    }
    return availableMoves;
}




