#ifndef BOARD_HPP
#define BOARD_HPP

#include "Matrix.hpp"

#include <iostream>

typedef enum{
  PIECE_NONE,
  PIECE_PLAYER1,
  PIECE_PLAYER2
} Piece;

class Board :public Matrix<int>{
private:
  
public:
  Board(const unsigned int&, const unsigned int&);
  //  Board(const Board&);
  virtual ~Board();
  virtual void draw(const unsigned int&, const unsigned int&);

};


#endif
