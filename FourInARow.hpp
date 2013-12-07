#ifndef FOURINAROW_HPP
#define FOURINAROW_HPP

#include "GameState.hpp"
#include "GUI.hpp"



class FourInARow : public GameState{

private:
  static const StateID::ID id = StateID::FOURINAROW;
  Matrix<Pion> board;

public:
  virtual void compute();
  virtual void render();
  virtual bool init();
  virtual bool exit();
  virtual StateID::ID getID() const { return this->id; }
  

};

#endif
