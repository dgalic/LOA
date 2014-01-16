#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Color.hpp"

class Player{

protected:
  Color mColor;

public:
  Player(const Color&);
  Player(const Player& p);
  virtual ~Player(){ };
  virtual Color getColor() const;
  virtual void setColor(const Color&);
  virtual void operator=(const Player&);
  virtual bool operator==(const Player&) const;
  virtual bool operator!=(const Player&) const;

};

#endif
