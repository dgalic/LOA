#ifndef GAME_HPP
#define GAME_HPP

#include "Singleton.hpp"
#include "StateHandler.hpp"

class Game: public Singleton<Game>{

  friend class Singleton<Game>;

public:
  void init();
  void exit();
  void loop();
  bool isRunning() const;
  void stop();
  void resume();
  StateHandler& getHandler();

private:
  bool mRunning;
  StateHandler mHandler;
};

#endif
