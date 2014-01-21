#ifndef STARTSTATE_HPP
#define STARTSTATE_HPP

#include "State.hpp"

class StartState : public State{


public:
  StartState();
  virtual ~StartState();
  virtual void handle(const char& c = ' ');
  virtual void update();
  virtual void render();

};


#endif
