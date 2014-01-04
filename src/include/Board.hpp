#ifndef BOARD_HPP
#define BOARD_HPP

#include "Matrix.hpp"

#include <iostream>

/**
 * Par défaut, car nos jeux de plateau sont dessinés comme ça,
 * le plateau est dessiné est position (6, 6).
 * Un board est une matrice d'entiers :
 * -1 correspond à "aucun pion posé".
 * sinon, c'est la couleur de la case.
 * Ainsi, les joueurs devraient être identifiés par leur numéro
 * de couleur, et le Board rempli avec ces identifiants (et non
 * pas 1 pour J1 et 2 pour J2 comme on pourrait s'y attendre).
*/
class Board :public Matrix<int>
{

public:
  Board(const unsigned int&, const unsigned int&);
  //  Board(const Board&);
  virtual ~Board();
  virtual void draw(const unsigned int&, 
                    const unsigned int&);

};


#endif
