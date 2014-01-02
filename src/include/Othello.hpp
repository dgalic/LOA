#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include "ANSI.hpp"
#include "BoardGame.hpp"
#include "StateHandler.hpp"

class Othello : public BoardGame{

private:
  ANSI::Color player1;
  ANSI::Color player2;
  ANSI::Color currentPlayer;
  unsigned short score[2];

public:
  Othello(ANSI::Color = ANSI::Color::BLUE, 
	  ANSI::Color = ANSI::Color::RED );
  virtual ~Othello();
  virtual void handle(const char& = ' ');
  /** prend les positions d'un placement de coup et calcule si c'est un coup possible pour le joueur donné.
   Dans ce cas précis, on renvoie le nombre de pions gagnés (et <0 si le coup n'est pas possible, car dans othello comme on place un pion qui encercle, le score est censé augmenter d'au moins 2) */
  virtual short next(const unsigned short&, const unsigned short&, const ANSI::Color&) const;  
  virtual void shuffle(const unsigned short&, const unsigned short&);
  virtual void update();
  virtual void render();
  virtual bool init();
  virtual bool exit();

};

#endif
