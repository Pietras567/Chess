#include <iostream>
#include "model/Board.h"
#include "model/Square.h"
#include "model/Pawn.h"
#include "typedefs.h"
#include "model/Game.h"
#include "model/HumanPlayer.h"
#include "model/ComputerPlayer.h"
#include "string"
#include "../exceptions/PlayerException.h"
using namespace std;

int main() {
    //Tutaj nastapi wlaczenie gry i wyswietlenie menu, a nastepnie wybor opcji i rozpoczecie
    // nowej lub wczytanie zapisanej rozgrywki

    int tryb=0;
    cout<<"Podaj tryb gry [1 - PVP , 2 - PVE, 3 - BOT VS BOT]";
    if(!(cin>>tryb)){
        cout<<"Wprowadzono zla wartosc, kod bledu 1";
        return 1;
    }

    switch (tryb) {
        case 1: {
            cout<<"Podaj nazwe dla gracza nr 1, grajacego bialymi pionkami \n";

            string name1;
            cin>>name1;
            //getline(cin, name1);

            PlayerPtr player1=std::make_shared<HumanPlayer>(name1,true);

            std::cin.clear();
            std::cin.ignore( 1000, '\n' );

            cout<<"Podaj nazwe dla gracza nr 2, grajacego czarnymi pionkami \n";

            string name2;
            //getline(cin, name2);
            cin>>name2;

            PlayerPtr player2=std::make_shared<HumanPlayer>(name2, false);

            BoardPtr board1=std::make_shared<Board>();
            board1->fill(player1,player2);
            //wywolanie fabryki i ustawienie bazowego zestawu pionkow
          //  shared_ptr<Bishop> Element=std::make_shared<Bishop>(player1);
           // Element->setOnBoard(board1->getSquares(2, 3));

           // shared_ptr<Bishop> Element2=std::make_shared<Bishop>(player2);
           // Element2->setOnBoard(board1->getSquares(2, 6));

            GamePtr game=std::make_shared<Game>(board1,player1,player2);
            try {
                game->updateScreen();
            }
            catch (PlayerException &e){
                std::string errorMsg=e.what();
                if(errorMsg == "MAT"){
                    game->endGame();
                } else if (errorMsg == "PAT"){
                    game->draw();
                } else{
                    std::cout<<"Wystapil wyjatek: "<<errorMsg<<"\n";
                    std::cout<<"\nNastapi zamkniecie programu \n";
                }
            }
            break;
        }
        case 2: {
            int kolor=0;
            cout<<"Podaj kolor figur, jakimi chcesz grac [1 - bialy , 2 - czarny]";
            if(!(cin>>kolor)){
                cout<<"Wprowadzono zla wartosc, kod bledu 1";
                return 1;
            }

            if(kolor==1){
                cout<<"Podaj nazwe dla gracza nr 1, grajacego bialymi pionkami \n";

                string name1;
                cin>>name1;


                PlayerPtr player1=std::make_shared<HumanPlayer>(name1,true);
                std::cin.clear();
                std::cin.ignore( 1000, '\n' );
                PlayerPtr player2=std::make_shared<ComputerPlayer>(false);


                BoardPtr board1=std::make_shared<Board>();
                board1->fill(player1,player2);
                //wywolanie fabryki i ustawienie bazowego zestawu pionkow
                GamePtr game=std::make_shared<Game>(board1,player1,player2);
                try {
                    game->updateScreen();
                }
                catch (PlayerException &e){
                    std::string errorMsg=e.what();
                    if(errorMsg == "MAT"){
                        game->endGame();
                    } else if (errorMsg == "PAT"){
                        game->draw();
                    } else{
                        std::cout<<"Wystapil wyjatek: "<<errorMsg<<"\n";
                        std::cout<<"\nNastapi zamkniecie programu \n";
                    }
                }

                break;
            } else if(kolor==2) {
                cout<<"Podaj nazwe dla gracza nr 2, grajacego czarnymi pionkami \n";

                string name2;
                cin>>name2;

                PlayerPtr player1=std::make_shared<ComputerPlayer>(true);
                std::cin.clear();
                std::cin.ignore( 1000, '\n' );
                PlayerPtr player2=std::make_shared<HumanPlayer>(name2, false);

                BoardPtr board1=std::make_shared<Board>();
                board1->fill(player1,player2);
                //wywolanie fabryki i ustawienie bazowego zestawu pionkow
                GamePtr game=std::make_shared<Game>(board1,player1,player2);
                //game->updateScreen();
                try {
                    game->updateScreen();
                }
                catch (PlayerException &e){
                    std::string errorMsg=e.what();
                    if(errorMsg == "MAT"){
                        game->endGame();
                    } else if (errorMsg == "PAT"){
                        game->draw();
                    } else{
                        std::cout<<"Wystapil wyjatek: "<<errorMsg<<"\n";
                        std::cout<<"\nNastapi zamkniecie programu \n";
                    }
                }
            }
            break;
        }
        case 3: {
            PlayerPtr player1=std::make_shared<ComputerPlayer>(true);
            PlayerPtr player2=std::make_shared<ComputerPlayer>(false);
            BoardPtr board1=std::make_shared<Board>();
            //wywolanie fabryki i ustawienie bazowego zestawu pionkow
            GamePtr game=std::make_shared<Game>(board1,player1,player2);
            board1->fill(player1,player2);
            try {
                game->updateScreen();
            }
            catch (PlayerException &e){
                std::string errorMsg=e.what();
                if(errorMsg == "MAT"){
                    game->endGame();
                } else if (errorMsg == "PAT"){
                    game->draw();
                } else{
                    std::cout<<"Wystapil wyjatek: "<<errorMsg<<"\n";
                    std::cout<<"\nNastapi zamkniecie programu \n";
                }
            }
            //game->updateScreen();
            break;
        }
    }

    return 0;
}
