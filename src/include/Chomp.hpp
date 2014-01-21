#ifndef CHOMP_HPP
#define CHOMP_HPP

#include "BoardGame.hpp"
#include "Player.hpp"
#include "Color.hpp"
#include "Config.hpp"

class Chomp: virtual public BoardGame {

protected:
  virtual void update();
  
  virtual void fillcolor(const unsigned short&, const unsigned short&);
  
public:
  // Ctor et  Dtor
  Chomp(const Color&, const Color&,
        const unsigned short& = 10, const unsigned short& = 4);
  virtual ~Chomp();
  
  // gére les touches des joueurs
        void handle(const char&);
  
  
  //gére l'affichage
  virtual void render();
  
  class Config: public ::Config{

  public:
    Config();
    virtual ~Config();
    virtual void launchGame();
    virtual void render();

  };

};

#endif
