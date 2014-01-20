#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include "BoardGame.hpp"
#include "Player.hpp"
#include "Color.hpp"
#include "Point.hpp"
#include "Config.hpp"
#include <list>

class Othello : public BoardGame{

public:
  Othello(const Color&, 
	  const Color&);
  virtual ~Othello();
  virtual void update();
  virtual void render();

protected:
  void handle(const char&);
  void shuffle(const Point&);
  bool isSucc(Board,
	      const Point&,
	      const Player&) const; 
public:
  class Config : public ::Config{
    
  protected:
    
  public:
    Config();
    virtual ~Config();
    virtual void handle(const char& = ' ');
    virtual void render();
    
  };

 
};

#endif
