#ifndef DIRECTION_HPP
#define DIRECTION_HPP

/** 
    Un ensemble de directions est juste un octet et s'obtient comme un flag : 
    -par le OU bit à bit : 
        dirs = S|SE|SO|E|O
    -ou par une simple addition, ici : 
        dirs = S+SE+SO+E+O
    Pour tester si une direction est dans l'ensemble, on utilise le ET bit à bit
        if( dir & N)
    Ne pas tester plusieurs directions :
        if( dir & (N | E) ) --> interdit !
        if( dir & (N & E) ) --> interdit !
*/

typedef enum{
  N = 1 << 7,
  NE = 1 << 6,
  E = 1 << 5,
  SE = 1 << 4,
  S = 1 << 3,
  SO = 1 << 2,
  O = 1 <<1,
  NO = 1
} direction;

typedef char DirectionSet;


#endif
