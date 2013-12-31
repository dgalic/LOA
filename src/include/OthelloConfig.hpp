#ifndef OTHELLOCONFIG_HPP
#define OTHELLOCONFIG_HPP


#include "ANSI.hpp"
#include "State.hpp"
#include "StateHandler.hpp"

class OthelloConfig : public State{

private:
  unsigned short entry;
  ANSI::Color color1;
  ANSI::Color color2;

public:
  virtual ~OthelloConfig();
  virtual void handle(const char& = ' ');
  virtual void update();
  virtual void render();
  virtual bool init();
  virtual bool exit();

};

#endif
