
#ifndef GAMESTATEHANDLER_HPP
#define GAMESTATEHANDLER_HPP

#include <stack>

#include "GameState.hpp"
#include "Singleton.hpp"


class GameStateHandler:public Singleton<GameStateHandler>
{

  friend class Singleton<GameStateHandler>;

public:
  void push (GameState * gs );
  GameState * pop();
  bool isEmpty();
  GameState * change(GameState * gs );
  void clear();
  void update();
  void render();
  
private:
  std::stack<GameState *> states;

};

#endif
