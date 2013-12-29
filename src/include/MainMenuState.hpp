#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "GameState.hpp"



class MainMenuState: public GameState{

public :
  virtual void update();
  virtual void render();
  virtual bool init();
  virtual bool exit();

private:
  

};

#endif
