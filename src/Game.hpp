#ifndef GAME_HPP
#define GAME_HPP

#include "Singleton.hpp"
#include "GUI_Window.hpp"

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
  bool running;
};

#endif
