#ifndef OTHELLO_HPP
#define OTHELLO_HPP

#include "BoardGame.hpp"
#include "Player.hpp"
#include "Color.hpp"
#include "Point.hpp"
#include "State.hpp"
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
  class Config : public State{
    
  protected:
    unsigned short mEntry;
    unsigned short mType2; // 0 pour humain, entre 1 et ?? pour IA
    std::list<Color>::iterator mColor1;
    std::list<Color>::iterator mColor2;
    std::list<Color> mPossibleColors; // couleurs séléctionnables
    
  public:
    Config();
    virtual ~Config();
    virtual void handle(const char& = ' ');
    virtual void update();
    virtual void render();
    
  };

 
};

#endif
