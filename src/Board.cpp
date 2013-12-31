#include "Board.hpp"
#include "Matrix.hpp"
#include <iostream>

Board::Board(const unsigned int& w, const unsigned int& h)
  :Matrix<int>(w, h){
  fillWith(-1);
}

Board::~Board(){

}

