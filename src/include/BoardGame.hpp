#ifndef BOARDGAME_HPP
#define BOARDGAME_HPP

#include "Board.hpp"
#include "State.hpp"

#include "ANSI.hpp"
#include "Player.hpp"
#include "Point.hpp"

#include <set>
#include <functional>
#include <string>
 
typedef std::set< Point > Positions;

class BoardGame : public State{

protected:
  Board mBoard;
  const Player mPlayer1;
  const Player mPlayer2;
  const Player * mCurrentPlayer;
  Point mPointer; // case séléctionnée
  bool mIngame; //dit si le jeu est terminé ou pas
  Positions mSuccessors; //les coups possibles depuis le plateau courant
  std::function<bool(Board, 
		     const Point&,
		     const Player&) > mSucc_function;

unsigned short mScore[2];

public:
BoardGame(const unsigned int&, const unsigned int&,
          const Color&, const Color&);
virtual ~BoardGame();
virtual void update() = 0;
virtual void render() = 0;

protected:
virtual void handle(const char& c = ' ');
virtual bool checkMove(const char&);
Positions computeNext(Board b, // plateau à tester
                      const Player& p); //joueur dont on cherche les coups
bool isNext(const Point&,
            const Positions&) const;  
const Player * opponent() const;
void displayScore();
void displayCurrentPlayer();
void displayResult(const unsigned short&, const unsigned short&);
  
};

#endif
