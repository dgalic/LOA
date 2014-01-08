#ifndef GAME_HPP
#define GAME_HPP

#include "Singleton.hpp"

class Game: public Singleton<Game>{

  friend class Singleton<Game>;

public:
  void init();
  void exit();
  void loop();
  bool isRunning() const;
  void stop();
  void resume();

private:
  bool mRunning;
};

#endif
