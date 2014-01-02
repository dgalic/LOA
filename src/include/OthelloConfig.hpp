#ifndef OTHELLOCONFIG_HPP
#define OTHELLOCONFIG_HPP


#include "ANSI.hpp"
#include "State.hpp"
#include "StateHandler.hpp"

#include <list>

/**
   Config d'othello : 
   - couleur du joueur 1
   - couleur du joueur 2
   - type du joueur 2 : humain ou IA
 */

class OthelloConfig : public State{

private:
  unsigned short entry;
  unsigned short type2; // 0 pour humain, entre 1 et ?? pour IA
  std::list<ANSI::Color>::iterator color1;
  std::list<ANSI::Color>::iterator color2;
  std::list<ANSI::Color> possible_colors; // couleurs séléctionnables

public:
  OthelloConfig();
  virtual ~OthelloConfig();
  virtual void handle(const char& = ' ');
  virtual void update();
  virtual void render();
  virtual bool init();
  virtual bool exit();

};

#endif
