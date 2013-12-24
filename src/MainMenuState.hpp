#ifndef MAINMENU_HPP
#define MAINMENU_HPP

#include "GameState.hpp"

#include "Event.hpp"
#include "GUI_Button.hpp"
#include "GUI_Container.hpp"
#include "GUI_Label.hpp"

class MainMenuState: public GameState{

public :
  virtual void update(const Event&);
  virtual void render();
  virtual bool init();
  virtual bool exit();

private:
  GUI::Container * container_main;
  GUI::Container * container_buttons;
  GUI::Button * button_play;
  GUI::Button * button_quit;
  GUI::Label * label_title;
  

};

#endif
