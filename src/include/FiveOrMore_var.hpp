#ifndef FIVEORMORE_VAR_HPP
#define FIVEORMORE_VAR_HPP

#include "FiveOrMore.hpp"

#include "Config.hpp"

class FiveOrMore_var : virtual public FiveOrMore{

protected:
  unsigned short mPreviousColor; // indice avant qu'on ai décidé de changer.
  unsigned short mColorIndex; // indice de la nouvelle couleur courante

public:
  FiveOrMore_var(const unsigned short&,
                 const unsigned short& = 5,
                 const unsigned short& = 3);
  virtual ~FiveOrMore_var();

protected:
  virtual void handleSelection(const char&);
  virtual void handleAction(const char&);
  virtual int findIndex(const int& c);

public:
  class Config: public FiveOrMore::Config{

  public:
    Config();
    virtual ~Config();
    virtual void launchGame();
  };

};

#endif
