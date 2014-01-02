#include "Board.hpp"
#include "Matrix.hpp"

#include "Console.hpp"

#include <iostream>

Board::Board(const unsigned int& w, const unsigned int& h)
  :Matrix<int>(w, h){
  fillWith(-1); // -1 est la valeur "pas de pion"
}

Board::~Board(){

}

/*
  par défaut, car nos jeux de plateau sont dessinés comme ça, 
  le plateau est dessiné est position (6, 6).
  Un board est une matrice d'entiers : 
  -1 correspond à "aucun pion posé".
  sinon, c'est la couleur de la case.
  Ainsi, les joueurs devraient être identifiés par leur numéro
  de couleur, et le Board rempli avec ces identifiants (et non
  pas 1 pour J1 et 2 pour J2 comme on pourrait s'y attendre).
*/
void Board::draw(const unsigned int& x = 12,
		 const unsigned int& y = 8){
  Console::getInstance()->setForeground( ANSI::Color::WHITE);
  Console::getInstance()->setCursor(x,y);
  Console::getInstance()->drawRectangle(x, y, 2*width+1, 1, '~');
  Console::getInstance()->drawRectangle(x, y+height+1, 2*width+1, 1, '~');
  
  for(unsigned int row = 0; row < height; row++){
    unsigned int col = 0;
    for(col = 0; col < 2*width; col += 2){
      Console::getInstance()->setForeground( ANSI::Color::WHITE);
      Console::getInstance()->draw(x+col, y+row+1, '|');
      int content = at(col/2, row);
      //      std::cerr<<"Board ("<<row<<","<<col/2<<") -> "<< content <<std::endl;
      if(content != -1){
	Console::getInstance()->setForeground( (ANSI::Color)content);
	Console::getInstance()->draw(x+col+1, y+row+1, "ʘ");
      }else{
	Console::getInstance()->draw(x+col+1, y+row+1, ' ');
      }
    }  
    Console::getInstance()->setForeground( ANSI::Color::WHITE);
    Console::getInstance()->draw(x+col, y+row+1, '|');
  }
}
