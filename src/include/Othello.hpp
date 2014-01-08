#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include "ANSI.hpp"
#include "BoardGame.hpp"
#include "StateHandler.hpp"

#include <vector>


class Othello : public BoardGame{

private:
  Player mPlayer2;
  unsigned short mTypeIA;
  unsigned short mScore[2];

public:
  Othello(Player = ANSI::Color::BLUE, 
	  Player = ANSI::Color::GREEN,
	  const unsigned short& = 0);
  virtual ~Othello();
  virtual void handle(const char& = ' ');
  virtual void shuffle(const unsigned short&, const unsigned short&);
  bool isSucc(Board,
	      const unsigned short&,
	      const unsigned short&,
	      const Player&) const;
  virtual void update();
  virtual void render();
  virtual bool init();
  virtual bool exit();

};

#endif
