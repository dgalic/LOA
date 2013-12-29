#include "Board.hpp"
#include "Matrix.hpp"
#include <iostream>

Board::Board(const unsigned int& w, const unsigned int& h)
  :Matrix<int>(w, h){
  for(unsigned int i = 0; i < width; i++)
    for(unsigned int j = 0; j < height; j++)
      data[i][j] = -1;
}

Board::~Board(){

}

