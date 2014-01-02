#ifndef BOARDGAME_HPP
#define BOARDGAME_HPP

#include "Board.hpp"
#include "State.hpp"


#include <set>
#include <utility> // pour std::pair

/* le type de retour de la fonction de succession : 
   des paires (x,y) de positions possibles depuis la configuration courante */
typedef std::set< std::pair< unsigned short, unsigned short> > succ;

class BoardGame : public State{

protected:
  Board board;
  unsigned short pointerX, pointerY; // case séléctionnée
  bool ingame; //dit si le jeu est terminé ou pas
  succ successors; //les coups possibles depuis le plateau courant

public:
  BoardGame(const unsigned int&, const unsigned int&);
  virtual ~BoardGame();
  virtual void handle(const char& c = ' ');
  virtual void update() = 0;
  virtual void render() = 0;
  virtual bool init() = 0;
  virtual bool exit() = 0;

};

#endif
