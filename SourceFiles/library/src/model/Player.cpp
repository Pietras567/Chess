
#include "model/Player.h"
#include "model/Move.h"
#include "model/Square.h"
#include "model/Board.h"
#include "model/Pawn.h"
#include "string"
#include "../../exceptions/PlayerException.h"
#include "model/King.h"
#include "model/Knight.h"
#include "model/Bishop.h"
#include "model/Rook.h"
#include "model/Queen.h"
#include "algorithm"
#include "vector"


Player::Player(const std::string &name, bool white) : name(name), white(white) {}
Player::Player(bool white) : white(white), name("ComputerPlayer") {
    if (white) name = name + " White";
    else name = name + " Black";
}

Player::~Player() {

}

const std::string &Player::getName() const {
    return name;
}

std::vector<PiecePtr> &Player::getPieces() {
    return pieces;
}

//const BoardPtr &Player::getBoard() const {
//    return board;
//}

bool Player::isWhite() const {
    return white;
}

bool Player::move(const MovePtr& move, const BoardPtr& board1, std::vector<MovePtr> &movesHistory) {
    std::vector<MovePtr> availableMoves= getAvailableMoves(board1,movesHistory);
    //std::cout<<"availableMoves.size: "<<availableMoves.size()<<"\n";
    for (int i = 0; i < availableMoves.size(); i++) {
        //sprawdzenie czy ruch znajduje sie na liscie
        if(move->getPiece()==availableMoves.at(i)->getPiece() && move->getDestination()==availableMoves.at(i)->getDestination() && move->getOldSquare()==availableMoves.at(i)->getOldSquare() ){
            //sprawdzenie i wykonanie ruchow specjalnych
            if(!checkSpecialMoves(move,board1,movesHistory)){
                move->getPiece()->makeMove(move->getDestination());
                movesHistory.push_back(move);
            }
            //move->getPiece()->makeMove(move->getDestination());
            //dodanie ruchu do historii
            //wykonanie ruchu

            return true;
        }
    }
    return false;
}

bool Player::checkSpecialMoves(const MovePtr& move, const BoardPtr& board1, std::vector<MovePtr> &movesHistory){
    if(std::dynamic_pointer_cast<Pawn>(move->getPiece())) { //dla pionka
        //jesli ruszamy pionkiem na skos na puste pole to zbij pionka przeciwnika za tym polem (enPassant)
        if (move->getDestination()->getX() != move->getOldSquare()->getX() &&
            move->getDestination()->getPiece() == nullptr) {
            int direction = move->getPiece()->getDirection();
            SquarePtr enPassant = board1->getSquares(move->getDestination()->getX(),
                                                     move->getDestination()->getY() - direction);
            //std::cout<<enPassant->getSquareInfo()<<"\n";
            move->getPiece()->capture(enPassant);
            move->getPiece()->makeMove(move->getDestination());
            movesHistory.push_back(move);
            return true;
        }
        else if( (isWhite() && move->getDestination()->getY()==0) || (!isWhite() && move->getDestination()->getY()==7) ){
            move->getPiece()->makeMove(move->getDestination());
            movesHistory.push_back(move);
            int a=askForPromotion();
            promotion(move->getPiece(),a);
            MovePtr move2=std::make_shared<Move>(move->getDestination()->getPiece(),move->getDestination());
            movesHistory.push_back(move2);
            return true;
        }
    }
    //sprawdz czy roszada (ruch krolem o 2 pola)
    // dodanie ruchu wiezy do historii na koncu aby metoda calculateAvailableMoves poprawnie okreslila czy krol jest szachowany
    else if(std::dynamic_pointer_cast<King>(move->getPiece()) && abs(move->getDestination()->getX()-move->getOldSquare()->getX())==2 ){
        PiecePtr rook;
        MovePtr towerMove;
        if(move->getDestination()->getX()==1){
            rook=board1->getSquares(0,move->getDestination()->getY())->getPiece();
            move->getPiece()->makeMove(move->getDestination()); //ruch krolem
            movesHistory.push_back(move); //dodanie ruchu krolem do historii
            //utworzenie ruchu dla wiezy
            towerMove=std::make_shared<Move>(rook,board1->getSquares(2,move->getDestination()->getY()));
            rook->makeMove(board1->getSquares(2,move->getDestination()->getY())); //ustawienie wiezy po roszadzie
            //dodanie ruchu wieza do historii
            movesHistory.push_back(towerMove);
            return true;
        } else{
            rook=board1->getSquares(7,move->getDestination()->getY())->getPiece();
            move->getPiece()->makeMove(move->getDestination()); //ruch krolem
            movesHistory.push_back(move); //dodanie ruchu krolem do historii
            //utworzenie ruchu dla wiezy
            towerMove=std::make_shared<Move>(rook,board1->getSquares(4,move->getDestination()->getY()));
            rook->makeMove(board1->getSquares(4,move->getDestination()->getY())); //ustawienie wiezy po roszadzie
            //dodanie ruchu wieza do historii
            movesHistory.push_back(towerMove);
            return true;
        }
    }
    return false;
}

std::vector<MovePtr> Player::getAvailableMoves(const BoardPtr& board1,const std::vector<MovePtr>& movesHistory) {
    std::vector<MovePtr> availableMoves;
    std::vector<MovePtr> pieceMoves;
    std::vector<MovePtr> realMoves;
    KingPtr king;
    if(!board1){
        throw PlayerException("Player::getAvailableMoves: board is nullptr");
    }
    //sprawdz dostepne ruchy
    for (int i = 0; i < getPieces().size(); i++) { // suma wektorow ruchow pionkow
        pieceMoves=getPieces().at(i)->calculateAvailableMoves(board1,movesHistory);
        availableMoves.insert(availableMoves.end(),std::make_move_iterator(pieceMoves.begin()),std::make_move_iterator(pieceMoves.end()));
    }
    //sprawdz czy historia nie jest pusta
    if(!movesHistory.empty()) {
        if (movesHistory.back()->getDestination()->getPiece() == nullptr) {
            throw PlayerException(
                    "Player::getAvailableMoves: no piece was found on destination of last successful move");
        }
        for (int i = 0; i < getPieces().size(); i++) {
            //znajdz krola
            king = std::dynamic_pointer_cast<King>(getPieces().at(i));
            if (king) { //sprawdz dostepne ruchy na wirtualnej planszy
                SquarePtr kingLocation=king->getSquare();
                realMoves = checkMovesOnVirtualBoard(board1, movesHistory, availableMoves, kingLocation);
                if( !realMoves.empty()){
                    return realMoves;
                } else{
                    if(king->isChecked()){
                        throw PlayerException("MAT");
                    } else{
                        throw PlayerException("PAT");
                    }
                }

            }
        }
    }
    return availableMoves;
}
/// \brief sprawdza czy po wykonaniu dostepnego ruchu krol bedzie szachowany, jesli tak to usuwa ten ruch z dostepnych
///
std::vector<MovePtr>
Player::checkMovesOnVirtualBoard(const BoardPtr &board1, const std::vector<MovePtr> &movesHistory, const std::vector<MovePtr> &availableMoves,const SquarePtr& kingLocation) {
    BoardPtr virtualBoard = board1->duplicate();
    //uzyskanie krola
    KingPtr virtualKing=std::dynamic_pointer_cast<King>(virtualBoard->getSquares(kingLocation->getX(),kingLocation->getY())->getPiece());
    //konwersja dostepnych ruchow na virtualna plansze
    std::vector<MovePtr> virtualAvailableMoves= convertMovesToDifferentBoard(availableMoves,virtualBoard);
    MovePtr virtualMove; //wykonany ruch
    PiecePtr virtualPiece; //figura wykonujaca ruch
    PiecePtr previousPiece; //figura zbita w wyniku ruchu
    //std::cout<<"virtualAvailableMoves.size: "<<virtualAvailableMoves.size()<<"\n";
    for (int i = 0; i < virtualAvailableMoves.size();) {
        virtualMove=virtualAvailableMoves.at(i); //zapisanie ruchu
        virtualPiece=virtualMove->getPiece(); //zapisanie figury wykonujacej ruch
        previousPiece=virtualMove->getDestination()->getPiece(); //zapisanie figury zbitej w wyniku ruchu
//        std::cout<<"Przed ruchem:";
//        std::cout<<virtualPiece->getPieceInfo()<<"\n";
        virtualPiece->setSquare(virtualMove->getDestination()); //wykonaj ruch
        virtualMove->getOldSquare()->setPiece(nullptr);
//        std::cout<<"Po ruchu:";
//        std::cout<<virtualPiece->getPieceInfo()<<"\n";
        virtualKing->calculateAvailableMoves(virtualBoard,movesHistory);
        if(virtualKing->isChecked()){ //sprawdz czy krol jest dalej szachowany
//            std::cout<<"usuwanie\n";
            virtualAvailableMoves.erase(std::remove(virtualAvailableMoves.begin(),virtualAvailableMoves.end(),virtualMove), virtualAvailableMoves.end());
        } else{
            i++;
        }
        //przywrocenie stanu planszy przed ruchem
        virtualPiece->setSquare(virtualMove->getOldSquare()); //powrot na poprzednie pole
        virtualMove->getDestination()->setPiece(nullptr);
        //virtualPiece->makeMove(virtualMove->getOldSquare());
        if(previousPiece){ //przywroc zbita figure
            previousPiece->setSquare(virtualMove->getDestination());
        }
    }
    std::vector<MovePtr> realMoves;
    int pieceX=0,pieceY=0,destX=0,destY=0;
    MovePtr move;
    // konwersja ruchow z planszy wirtualnej do glownej planszy gry
    realMoves=convertMovesToDifferentBoard(virtualAvailableMoves,board1);
    //std::cout<<"realMoves.size: "<<realMoves.size()<<"\n";
    return realMoves;
}

void Player::setName(const std::string &name) {
    Player::name = name;
}

void Player::setWhite(bool white) {
    Player::white = white;
}

std::vector<MovePtr> Player::convertMovesToDifferentBoard(const std::vector<MovePtr> &movesToConvert,const BoardPtr& newBoard){
    std::vector<MovePtr> convertedMoves;
    int pieceX=0,pieceY=0,destX=0,destY=0;
    MovePtr move;
    for (int i = 0; i < movesToConvert.size(); ++i) {//skonwertuj do innej planszy
        pieceX=movesToConvert.at(i)->getPiece()->getSquare()->getX();
        pieceY=movesToConvert.at(i)->getPiece()->getSquare()->getY();
        destX=movesToConvert.at(i)->getDestination()->getX();
        destY=movesToConvert.at(i)->getDestination()->getY();
        move=std::make_shared<Move>(newBoard->getSquares(pieceX,pieceY)->getPiece(),newBoard->getSquares(destX,destY));
        convertedMoves.push_back(move);
    }
    return convertedMoves;
}

void Player::promotion(const PiecePtr &piece, int a) { //znikajacy pionek?
    int position=0;
    SquarePtr location=piece->getSquare();
    for (int i = 0; i < getPieces().size(); ++i) {
        if(getPieces().at(i)==piece){
            getPieces().erase(getPieces().begin()+i);
        }
    }

    PiecePtr newPiece;

//    piece->setSquare(nullptr);
//    location->setPiece(nullptr);
    //location->setPiece(nullptr);
    switch (a) {
        case 1:
            newPiece=std::make_shared<Knight>(shared_from_this());
            newPiece->setOnBoard(location);
            break;
        case 2:
            newPiece=std::make_shared<Bishop>(shared_from_this());
            newPiece->setOnBoard(location);
            break;
        case 3:
            newPiece=std::make_shared<Rook>(shared_from_this());
            newPiece->setOnBoard(location);
            break;
        default:
            newPiece=std::make_shared<Queen>(shared_from_this());
            newPiece->setOnBoard(location);
            break;
    }

    //getPieces().at(position)=newPiece;
}

