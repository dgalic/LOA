#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "State.hpp"

#include <string>

class MainMenuState: public State{

public :
  virtual ~MainMenuState();
  virtual void handle(const char& = ' ');
  virtual void update();
  virtual void render();
  virtual bool init();
  virtual bool exit();

private:
  std::vector<std::string> gameDescs; //descriptions des jeux disponibles
  unsigned short entry;
  unsigned short nbgames;
  

};

#endif
