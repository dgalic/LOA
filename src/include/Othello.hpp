#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include "ANSI.hpp"
#include "BoardGame.hpp"
#include "StateHandler.hpp"

class Othello : public BoardGame{

private:
  ANSI::Color player1;
  ANSI::Color player2;
  unsigned short score[2];

public:
  Othello(ANSI::Color = ANSI::Color::BLUE, 
	  ANSI::Color = ANSI::Color::RED );
  virtual ~Othello();
  virtual void handle(const char& = ' ');
  virtual void update();
  virtual void render();
  virtual bool init();
  virtual bool exit();

};

#endif
