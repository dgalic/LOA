#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include "ANSI.hpp"
#include "BoardGame.hpp"
#include "StateHandler.hpp"

#include <vector>


class Othello : public BoardGame{

private:
  ANSI::Color player1;
  ANSI::Color player2;
  ANSI::Color currentPlayer;
  unsigned short typeIA;
  unsigned short score[2];

public:
  Othello(ANSI::Color = ANSI::Color::BLUE, 
	  ANSI::Color = ANSI::Color::GREEN,
	  const unsigned short& = 0);
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
