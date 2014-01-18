#ifndef FIVEORMORE_HPP
#define FIVEORMORE_HPP

#include "BoardGame.hpp"

#include "Color.hpp"

#include <array>

class FiveOrMore : virtual public BoardGame{

protected:
  static const std::array<Color, 10> sColorList;
  const unsigned short mSize;
  unsigned short mFreePlaces; //nombre de cases libres restants -> pour la fin
  unsigned short mNbColors; // nombre de couleurs du jeu
  const unsigned short mAdds; //nombre de pions ajoutés par tour

public:
  FiveOrMore(const unsigned short&,
             const unsigned short& = 3);
  virtual ~FiveOrMore();
  virtual void handle(const char& c = ' ');
  virtual void update();
  virtual void render();
  virtual unsigned short drop(const unsigned short&,
                              const unsigned short&);
  virtual bool addRandom();
  virtual bool end();
};

#endif
