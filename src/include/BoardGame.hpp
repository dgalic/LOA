#ifndef BOARDGAME_HPP
#define BOARDGAME_HPP

#include "Board.hpp"
#include "State.hpp"

#include "Player.hpp"

#include <set>
#include <utility> // pour std::pair
#include <functional>
#include <string>

typedef std::set< std::pair< unsigned short, unsigned short> > Positions;

class BoardGame : public State{

protected:
  Board mBoard;
  const Player mPlayer1;
  const Player mPlayer2;
  const Player * mCurrentPlayer;
  unsigned short mPointerX, mPointerY; // case séléctionnée
  bool mIngame; //dit si le jeu est terminé ou pas
  Positions successors; //les coups possibles depuis le plateau courant
  std::function<bool(Board, 
		     const unsigned short&,
		     const unsigned short&,
		     const Player&) > succ_function;

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
                        const Player& p, //joueur dont on cherche les coups
                        const std::function< bool(Board, const unsigned short&, const unsigned short&, const Player&)> & succ ); //fonction de succession
  bool isNext(const unsigned short& x, 
              const unsigned short& y,
              const Positions& p) const;
  void displayHeader(const std::string&);
  void displayScore();
  void displayCurrentPlayer();
  void displayResult(const unsigned short&, const unsigned short&);
  
};

#endif
