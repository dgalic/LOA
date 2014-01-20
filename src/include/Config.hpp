#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "State.hpp"

#include "ANSI.hpp"
#include "Color.hpp"

#include <list>

/**
 * La config par défaut permet de régler les couleurs de 2 joueurs, 
 * ainsi que les dimensions du plateau de jeu.
 */
 
class Config : public State{
  
protected:
  unsigned short mEntry; // indice de l'entrée séléctionnée
  const unsigned short mNbEntries; // nombre d'entrées
  unsigned short mWidth; // dimensions de la grille
  unsigned short mHeight;
  std::list<Color>::iterator mColor1; // couleurs des joueurs
  std::list<Color>::iterator mColor2;
  std::list<Color> mPossibleColors; // couleurs séléctionnables


public:
  Config(const unsigned short& = 0);
  virtual ~Config();
  virtual void handle(const char& = ' ');
  virtual void update();
  virtual void render();

};

#endif
