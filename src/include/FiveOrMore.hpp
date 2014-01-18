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
  unsigned short mScore;
  short mSelectedX;
  short mSelectedY;
  bool mPlaced;

private:
  void handle(const char &c= ' ');

public:
  FiveOrMore(const unsigned short&,
             const unsigned short& = 5,
             const unsigned short& = 3);
  virtual ~FiveOrMore();
  virtual void handleSelection(const char&);
  virtual void handleAction(const char&);
  virtual void update();
  virtual void render();
  virtual void searchLines(const unsigned short&,
                    const unsigned short&);
  virtual bool addRandom();
  virtual bool end();
};

#endif
