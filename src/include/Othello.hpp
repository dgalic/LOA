#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include "BoardGame.hpp"
#include "Player.hpp"
#include "StateHandler.hpp"
#include "Color.hpp"
#include "Point.hpp"

class Othello : public BoardGame{

public:
  Othello(const Color&, 
	  const Color&);
  virtual ~Othello();
  virtual void update();
  virtual void render();

protected:
  void handle(const char&);
  void shuffle(const Point&);
  bool isSucc(Board,
	      const Point&,
	      const Player&) const;  
};

#endif
