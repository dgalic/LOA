#ifndef BOARDGAME_HPP
#define BOARDGAME_HPP

#include "Board.hpp"
#include "State.hpp"

class BoardGame : public State{

protected:
  Board board;
  unsigned short pointerX, pointerY; // case séléctionnée

public:
  BoardGame(const unsigned int&, const unsigned int&);
  virtual ~BoardGame();
  virtual bool handle(const char& c = ' ');
  virtual void update() = 0;
  virtual void render() = 0;
  virtual bool init() = 0;
  virtual bool exit() = 0;

};

#endif
