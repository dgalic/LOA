#ifndef ANSI_HPP
#define ANSI_HPP

namespace ANSI{

    typedef enum{
      BLACK = 16,
      RED = 1,
      GREEN = 2,
      BLUE = 12,
      DARKRED = 1,
      DARKGREEN = 2,
      BROWN = 3,
      DARKBLUE = 4,
      PURPLE = 5,
      DARKCYAN = 6,
      LIGHTGRAY = 7,
      GRAY = 8,
      LIGHTRED = 9,
      LIGHTGREEN = 10,
      YELLOW = 11,
      LIGHTBLUE = 12,
      PINK = 13,
      LIGHTCYAN = 14,
      WHITE = 15,
      COUNT = 17
    } Color;

  
  typedef enum {
    NOARROW,
    UP,
    DOWN,
    LEFT,
    RIGHT
  } Arrow;


}

#endif
