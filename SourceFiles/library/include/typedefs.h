#ifndef CARRENTAL_TYPEDEFS_H
#define CARRENTAL_TYPEDEFS_H

#include <memory>
#include <functional>

class Piece;
class Square;
class MovementType;
class Board;
class Move;
class Player;
class Pawn;
class Game;
class King;
//class Observer;
typedef std::shared_ptr<Piece> PiecePtr;
typedef std::shared_ptr<Square> SquarePtr;
typedef std::shared_ptr<MovementType> MovementTypePtr;
typedef std::shared_ptr<Board> BoardPtr;
typedef std::shared_ptr<Move> MovePtr;
typedef std::shared_ptr<Player> PlayerPtr;
typedef std::shared_ptr<Pawn> PawnPtr;
typedef std::shared_ptr<Game> GamePtr;
typedef std::shared_ptr<King> KingPtr;
//typedef std::shared_ptr<Observer> ObserverPtr;

//typedef std::function<bool(RentPtr)> RentPredicate;


#endif //CARRENTAL_TYPEDEFS_H
