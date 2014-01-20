#ifndef FIVEORMORECONFIG_HPP
#define FIVEORMORECONFIG_HPP


#include "Color.hpp"
#include "State.hpp"
#include "StateHandler.hpp"

/**
   Config d'othello : 
   - Taille de la grille (entre 8 et 15)
   - Nombre de piece rajouter à chaque tours
   - Nombre total de couleur possible
 */

class FiveOrMoreConfig : public State{

private:
  unsigned short mEntry;
  unsigned short mSize;
  unsigned short mPiece;
  unsigned short mColor;
  unsigned short mJeux;

public:
  FiveOrMoreConfig();
  virtual ~FiveOrMoreConfig();
  virtual void handle(const char& = ' ');
  virtual void update();
  virtual void render();

};

#endif
