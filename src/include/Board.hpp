#ifndef BOARD_HPP
#define BOARD_HPP

#include "Matrix.hpp"

#include <iostream>

class Board :public Matrix<int>{

public:
  Board(const unsigned int&, const unsigned int&);
  //  Board(const Board&);
  virtual ~Board();
  virtual void draw(const unsigned int&, const unsigned int&);

};


#endif
