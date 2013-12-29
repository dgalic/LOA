
#ifndef GAMESTATEHANDLER_HPP
#define GAMESTATEHANDLER_HPP

#include <stack>

#include "State.hpp"
#include "Singleton.hpp"


class StateHandler:public Singleton<StateHandler>
{

  friend class Singleton<StateHandler>;

public:
  void push (State * gs );
  State * pop();
  bool isEmpty();
  State * change(State * gs );
  void clear();
  void update();
  void render();
  
private:
  std::stack<State *> states;

};

#endif
