
#ifndef GAMESTATEHANDLER_HPP
#define GAMESTATEHANDLER_HPP

#include <stack>

#include "State.hpp"
#include "Singleton.hpp"


class StateHandler:public Singleton<StateHandler>
{

  friend class Singleton<StateHandler>;

public:
  void push (State *);
  void pop();
  bool isEmpty();
  void change(State *);
  void clear();
  void update();
  void render();
  
private:
  std::stack<State *> mStates;

};

#endif
