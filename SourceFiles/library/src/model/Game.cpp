//
// Created by Piotr on 10.05.2023.
//

#include "model/Game.h"
#include "model/Piece.h"
#include "model/Board.h"
#include "string"
#include <cstdlib>
#include <iostream>
#include "model/Square.h"
#include "model/Player.h"
#include "model/HumanPlayer.h"
#include <string.h>
#include <stdio.h>

#include <iomanip>
#include <dirent.h>
#include "fstream"
#include "../exceptions/PlayerException.h"

bool Game::saveGame() {
    /*
     * Gracz1
     * nazwa
     * czyBialy
     *
     * Gracz2
     * nazwa
     * czyBialy
     *
     * historia ruchow
     * x posiadane
     * y posiadane
     * x docelowe
     * y docelowe
     * */
    std::cout<<"Podaj nazwe dla pliku z zapisem gry: ";
    std::string saveName;
    std::cin>>saveName;
    std::ofstream saveFile(saveName+".txt");
    saveFile << getPlayer1()->getName();
    saveFile << "\n";
    if(getPlayer1()->isWhite()){
        saveFile << "white\n";
    } else{
        saveFile << "black\n";
    }
    saveFile << getPlayer2()->getName();
    saveFile << "\n";
    if(getPlayer2()->isWhite()){
        saveFile << "white\n";
    } else{
        saveFile << "black\n";
    }

    for(int i = 0; i < getMovesHistory().size(); i++) {
        if(getMovesHistory().at(i)->getOldSquare()== getMovesHistory().at(i)->getDestination()){ //jesli pionek sie pojawil na planszy
            if(getMovesHistory().at(i)->getPiece()->getClassName()=="Knight"){
                saveFile <<"1\n";
            } else if(getMovesHistory().at(i)->getPiece()->getClassName()=="Bishop"){
                saveFile <<"2\n";
            } else if(getMovesHistory().at(i)->getPiece()->getClassName()=="Rook"){
                saveFile <<"3\n";
            } else{
                saveFile <<"4\n";
            }
        }
        else{
            saveFile << std::to_string(getMovesHistory().at(i)->getOldSquare()->getX())<<"\n";
            saveFile << std::to_string(getMovesHistory().at(i)->getOldSquare()->getY())<<"\n";

            saveFile << std::to_string(getMovesHistory().at(i)->getDestination()->getX())<<"\n";
            saveFile << std::to_string(getMovesHistory().at(i)->getDestination()->getY())<<"\n";
        }

    }

    saveFile.close();
    return true;
}

bool Game::loadGame() {

    std::cout<<"Podaj nazwe pliku z zapisem gry: \n";
    std::string saveName;
    std::cin>>saveName;

    std::ifstream saveFile(saveName+".txt");
    movesHistory.clear();
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            getGameBoard()->getSquares(i,j)->setPiece(nullptr);
        }
    }
    player1->getPieces().clear();
    player2->getPieces().clear();
    getGameBoard()->fill(player1,player2);

    std::string linia;
    MovePtr move;
    int i=0;
    int x1=0,x2=0,y1=0,y2=0;
    if(saveFile.good()){
        while (getline(saveFile,linia)){
            switch (i) {
                case 0:
                    player1->setName(linia);
                    i++;
                    break;
                case 1:
                    if(linia=="white"){
                        player1->setWhite(true);
                    } else {
                        player1->setWhite(false);
                    }
                    i++;
                    break;

                case 2:
                    player2->setName(linia);
                    i++;
                    break;
                case 3:
                    if(linia=="white"){
                        player2->setWhite(true);
                    } else {
                        player2->setWhite(false);
                    }
                    i++;
                    break;
                case 4:
                    x1 = stoi(linia.substr(0,1));
                    i++;
                    break;
                case 5:
                    y1 = stoi(linia.substr(0,1));
                    i++;
                    break;
                case 6:
                    x2 = stoi(linia.substr(0,1));
                    i++;
                    break;
                case 7:
                    y2 = stoi(linia.substr(0,1));
                case 8: //jesli oldSquare nullptr to ustaw figure na destination
                    move=std::make_shared<Move>(getGameBoard()->getSquares(x1, y1)->getPiece(),getGameBoard()->getSquares(x2, y2));
                    getGameBoard()->getSquares(x1, y1)->getPiece()->makeMove(getGameBoard()->getSquares(x2, y2));
                    getMovesHistory().push_back(move);
                    if(move->getPiece()->getClassName()=="Pawn" && (y2==0 || y2==7)){
                        getline(saveFile,linia);
                        move->getPiece()->getPlayer()->promotion(move->getPiece(), std::stoi(linia));
                        MovePtr move2=std::make_shared<Move>(move->getDestination()->getPiece(),move->getDestination());
                        movesHistory.push_back(move2);
                    }
                    i=4;
            }
        }
    } else{
        std::cout<<"Blad otwarcia pliku\n";
        std::cin.clear();
        std::cin.ignore( 1000, '\n' );
        std::cin.clear();
        std::cin.ignore( 1000, '\n' );
    }
    saveFile.close();
    updateScreen();
    return true;
}


std::vector<MovePtr> &Game::getMovesHistory() {
    return movesHistory;
}

const PlayerPtr &Game::getPlayer1() const {
    return player1;
}

const PlayerPtr &Game::getPlayer2() const {
    return player2;
}

void Game::askPlayer1ToMove() { ////prosi gracza o ruch i zapisuje ruch w historii
   // if(std::dynamic_pointer_cast<HumanPlayer>(player1)){
        MovePtr move1;
        bool yes= false;
        do {
            move1=player1->getMove(getGameBoard(),getMovesHistory());
            yes=player1->move(move1,getGameBoard(),getMovesHistory());
       }while(!(yes));

   // }
}

Game::Game(const BoardPtr &gameBoard, const PlayerPtr &player1, const PlayerPtr &player2) : GameBoard(gameBoard),
                                                                                            player1(player1),
                                                                                            player2(player2) {}

const BoardPtr &Game::getGameBoard() const {
    return GameBoard;
}

void Game::updateScreen() {
    system("clear");
    //Dostepne opcje - menu
    std::cout << "1. Wykonaj ruch\n";
    std::cout << "2. Zapisz gre\n";
    std::cout << "3. Wczytaj gre\n";
    std::cout << "4. Zakoncz gre\n";
    std::cout << "5. Poddaj sie\n";
    std::cout << "6. Zaproponuj remis\n";
    std::cout << "7. Wyswietl dostepne ruchy dla danej figury\n";
    std::cout << "8. Wyswietl historie ruchow\n\n";

    //Pionki i plansza
    int size,row,column;
    size = 8;
    std::cout<<"y:  0   1   2   3   4   5   6   7\nx:\n";
    for(row=0;row<size;row++) {
        std::cout<<std::setw(1)<<" \u2003\u2003";
        /* Gorna linia */
        for(column=0;column<size;column++)
            std::cout<<"\u23AF\u23AF\u23AF\u23AF";//linia pozioma
        std::cout<<'\n';
        std::cout<<row<<" ";
        /* Kwadraty z figurami lub bez */
        for(column=0;column<size;column++) {
            std::cout<<std::setw(1)<<"\u007C"; //linia pionowa
            if (getGameBoard()->getSquares(row, column)->getPiece() != nullptr) {
                if (getGameBoard()->getSquares(row, column)->getPiece()->getPlayer()->isWhite() == true) {
                    setlocale(LC_CTYPE, "");
                    std::cout<<std::left<< "\u2003";
                    getGameBoard()->getSquares(row, column)->getPiece()->showPieceImageWhite();
                    std::cout<<std::left<< "\u2003";
                } else {
                    setlocale(LC_CTYPE, "");
                    std::cout<<std::left<< "\u2003";
                    getGameBoard()->getSquares(row, column)->getPiece()->showPieceImageBlack();
                    std::cout<<std::left<< "\u2003";
                }
            } else {
                setlocale(LC_CTYPE, "");
                std::cout<<std::left<< "\u2003";
                std::cout<<std::left<< "\u2003";
                std::cout<<std::left<< "\u2003";
            }
        }
        std::cout<<"\u007C\n";
    }
    /* Dolna linia */
    std::cout<<std::setw(1)<<" \u2003\u2003";
    for(column=0;column<size;column++)
        std::cout<<"\u23AF\u23AF\u23AF\u23AF";
    std::cout<<'\n';
    std::cout << "\n";
    if (getMovesHistory().empty() || getMovesHistory().back()->getPiece()->getPlayer()->isWhite()==false ) {
        std::cout<<"Ruch gracza "<<player1->getName()<<"\n";
    } else{
        std::cout<<"Ruch gracza "<<player2->getName()<<"\n";
    }
    std::cout << "Wprowadz polecenie: \n";
    int wybor;
    if(!(std::cin>>wybor)){
        std::cin.clear();
        std::cin.ignore( 1000, '\n' );
        updateScreen();
    }
    switch(wybor) {
        case 1: {
            if (getMovesHistory().empty() || getMovesHistory().back()->getPiece()->getPlayer()->isWhite()==false ) {
                askPlayer1ToMove();
            } else {
                askPlayer2ToMove();
            }
            updateScreen();
            break;
        }
        case 2: {
            saveGame();
            updateScreen();
            break;
        }
        case 3: {
            loadGame();
            updateScreen();
            break;
        }
        case 4:{
            break;
        }
        case 5: {
            endGame();
            break;
        }
        case 6: {
            std::cout<<"Oponent proponuje ci remis, czy chcesz na to przystac, wprowadz t/T dla tak, w przeciwnym razie wrocimy do potyczki: ";
            char ifDraw;
            std::cin>>ifDraw;
            //ifDraw = getchar();
            if(ifDraw=='T' || ifDraw=='t') draw();
            break;
        }
        case 7: {
            int x=0,y=0;
            do{
                std::cout<<"\nPodaj wspolrzedne figury : \n";
                std::cout<<"x: ";
                std::cin>>x;
                std::cout<<"y: ";
                std::cin>>y;
        } while (getGameBoard()->getSquares(x,y) == nullptr || !getGameBoard()->getSquares(x,y)->getPiece());
            std::cout<<getGameBoard()->getSquares(x,y)->getPiece()->getPieceInfo()<<"\n";
            std::vector<MovePtr> availableMoves=getGameBoard()->getSquares(x,y)->getPiece()->calculateAvailableMoves(getGameBoard(),getMovesHistory());
            std::cout<<"Dostepne ruchy: "<<availableMoves.size()<<"\n";
            for (int i = 0; i < availableMoves.size(); i++) {
                std::cout<<i+1<<"."<<"\n";
                std::cout<<" x: "<<availableMoves.at(i)->getDestination()->getX()<<"\n";
                std::cout<<" y: "<<availableMoves.at(i)->getDestination()->getY()<<"\n";
            }
            std::cin.clear();
            std::cin.ignore( 1000, '\n' );
            std::cin.clear();
            std::cin.ignore( 1000, '\n' );
            updateScreen();
            break;
        }
        case 8: {
            getMovesHistoryInfo();
            updateScreen();
            break;
        }
        default: {
            updateScreen();
        }
    }
}

void Game::endGame() {
    if( getMovesHistory().empty() || getMovesHistory().back()==nullptr || getMovesHistory().back()->getPiece()->getPlayer()->isWhite()==false ) {
        std::cout << "\nGracz przewodzacy czarnym pionkom zwyciezyl!\n";

    } else if(getMovesHistory().back()->getPiece()->getPlayer()->isWhite()==true) {
        std::cout << "Gracz przewodzacy bialym pionkom zwyciezyl!\n";
    }
        std::cout<<"Czy chcesz wykonac cos jeszcze?\n";
        std::cout << "1. Wyswietl dodatkowe informacje o grze oraz historie ruchow\n";
        std::cout << "2. Zakoncz gre\n";
        int czyKoniec=0;
//        if(!(std::cin>>czyKoniec)){
//            std::cin>>czyKoniec;
//        }
        std::cin>>czyKoniec;
        switch (czyKoniec) {
            case 1: {
                getMovesHistoryInfo();
                break;
            }
            case 2: {
                std::cout<<"W takim razie konczymy gre\n";
                break;
            }
            default: {
                std::cout<<"W takim razie rowniez konczymy gre\n";
                break;
            }
        }
    }


void Game::getMovesHistoryInfo() {
    if(getMovesHistory().empty()){
        std::cout<<"Historia jest pusta\n";
    } else{
        std::cout<<"Historia gry: \n";
        for(int i = 0; i<getMovesHistory().size(); i++) {
            std::cout<<"Ruch z: x: "<<getMovesHistory().at(i)->getOldSquare()->getX()<<", y: "<<getMovesHistory().at(i)->getOldSquare()->getY();
            std::cout<<"\n";

            std::cout<<"Ruch do: x: "<<getMovesHistory().at(i)->getDestination()->getX()<<", y: "<<getMovesHistory().at(i)->getDestination()->getY();
            std::cout<<"\n";

            std::cout<<"Figura: ";
            if(getMovesHistory().at(i)->getPiece()->getPlayer()->isWhite()==true) {
                getMovesHistory().at(i)->getPiece()->showPieceImageWhite();
            } else if(getMovesHistory().at(i)->getPiece()->getPlayer()->isWhite()==false) {
                getMovesHistory().at(i)->getPiece()->showPieceImageBlack();
            }
            std::cout<<"\n\n";
        }
    }
    std::cin.clear();
    std::cin.ignore( 1000, '\n' );
    std::cin.clear();
    std::cin.ignore( 1000, '\n' );
}

void Game::draw() {
    std::cout<<"Remis! Po ciezkich bojach nie wyloniono lepszego.\n";
    std::cout<<"Czy chcesz wykonac cos jeszcze?\n";
    std::cout << "1. Wyswietl dodatkowe informacje o grze oraz historie ruchow\n";
    std::cout << "2. Zakoncz gre\n";
    int czyKoniec;
    std::cin>>czyKoniec;
    switch (czyKoniec) {
        case 1: {
            getMovesHistoryInfo();
            break;
        }
        case 2: {
            std::cout<<"W takim razie konczymy gre\n";
            break;
        }
        default: {
            std::cout<<"W takim razie rowniez konczymy gre\n";
            break;
        }
    }
}

void Game::askPlayer2ToMove() {
        MovePtr move1;
        bool yes= false;
        player2->getAvailableMoves(getGameBoard(),getMovesHistory());
        do {
            move1=player2->getMove(getGameBoard(),getMovesHistory());
            yes=player2->move(move1,getGameBoard(),getMovesHistory());
        }while(!(yes));

}
