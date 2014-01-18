#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include "BoardGame.hpp"
#include "Player.hpp"
#include "StateHandler.hpp"
#include "Color.hpp"

class Othello : public BoardGame{

private:
  Player mPlayer1;
  Player mPlayer2;
  const Player * mCurrentPlayer;
  unsigned short mScore[2];


public:
  Othello(const Color&, 
	  const Color&);
  virtual ~Othello();
  void handle(const char&);
  void shuffle(const unsigned short&, const unsigned short&);
  bool isSucc(Board,
	      const unsigned short&,
	      const unsigned short&,
	      const Player&) const;
  const Player * opponent() const;
  virtual void update();
  virtual void render();

};

#endif
