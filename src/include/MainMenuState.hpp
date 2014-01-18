#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "State.hpp"

#include <string>

class MainMenuState: virtual public State{

private:
  std::vector<std::string> mGameDescs; //descriptions des jeux disponibles
  unsigned short mEntry;
  unsigned short mNbGames;

public :
  MainMenuState();
  virtual ~MainMenuState();
  virtual void handle(const char& = ' ');
  virtual void update();
  virtual void render();

  

};

#endif
