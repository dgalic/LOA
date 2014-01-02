#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include "ANSI.hpp"
#include "BoardGame.hpp"
#include "StateHandler.hpp"

#include <vector>
#include <set>
#include <utility> // pour std::pair

/* le type de retour de la fonction de succession : 
   des paires (x,y) de positions possibles depuis la configuration courante */
typedef std::set< std::pair< unsigned short, unsigned short> > succ;

class Othello : public BoardGame{

private:
  ANSI::Color player1;
  ANSI::Color player2;
  ANSI::Color currentPlayer;
  unsigned short score[2];
  succ successors; //les coups possibles depuis le plateau courant

public:
  Othello(ANSI::Color = ANSI::Color::BLUE, 
	  ANSI::Color = ANSI::Color::RED );
  virtual ~Othello();
  virtual void handle(const char& = ' ');
  /** calcule les coups possibles de la configuration (plateau) donné
   pour le joueur donné */
  virtual succ next(Board, const ANSI::Color&) const;
  /** dit si le coup est possible */
  virtual bool isNext(const unsigned short&, const unsigned short&, const succ&) const;
  virtual void shuffle(const unsigned short&, const unsigned short&);
  virtual void update();
  virtual void render();
  virtual bool init();
  virtual bool exit();

};

#endif
