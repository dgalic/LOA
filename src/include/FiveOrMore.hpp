#ifndef FIVEORMORE_HPP
#define FIVEORMORE_HPP

#include "BoardGame.hpp"

#include "Color.hpp"

#include "Config.hpp"

#include <array>

class FiveOrMore : virtual public BoardGame{

protected:
  static const std::array<Color, 10> sColorList;
  const unsigned short mSize;
  unsigned short mFreePlaces; //nombre de cases libres restants -> pour la fin
  unsigned short mNbColors; // nombre de couleurs du jeu
  const unsigned short mAdds; //nombre de pions ajoutés par tour
  Point mSelected;
  bool mPlaced;

public:
  FiveOrMore(const unsigned short&,
             const unsigned short& = 5,
             const unsigned short& = 3);
  virtual ~FiveOrMore();
  virtual void update();
  virtual void render();

protected:
  void handle(const char &c= ' ');  
  virtual void handleSelection(const char&);
  virtual void handleAction(const char&);
  void searchLines(const unsigned short&,
                   const unsigned short&);
  bool addRandom();
  bool end();
  virtual void displayScore();
  virtual void displayResult(const unsigned short&, const unsigned short&);


public:
  class Config: public ::Config{
  protected:
    unsigned short mPieces;
    unsigned short mColors;
    
  public:
    Config();
    virtual ~Config();
    virtual void handle(const char& = ' ');
    virtual void launchGame();
    virtual void render();

  };

};

#endif
