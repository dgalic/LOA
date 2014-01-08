
#ifndef GAMESTATEHANDLER_HPP
#define GAMESTATEHANDLER_HPP

#include <stack>

#include "State.hpp"


class StateHandler
{

public: 
  virtual ~StateHandler();
  virtual void push (State *);
  virtual void pop();
  virtual bool isEmpty();
  virtual void change(State *);
  virtual void clear();
  virtual void update();
  virtual void render();
  
private:
  std::stack<State *> mStates;

};

#endif
