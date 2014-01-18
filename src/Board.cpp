#include "Board.hpp"

#include "Console.hpp"
#include "Matrix.hpp"

#include <iostream>


Board::Board(const unsigned int& w, const unsigned int& h)
  :Matrix<int>(w, h)
{
  /**
   * Constructeur. Crée une matrice de taille @a w x @a h remplie avec @e -1,
   * qui est la valeur correspondant à "pas de pion dans cette case". 
   * @param w largeur de la matrice
   * @param h hauteur de la matrice
   */
  fillWith(-1); // -1 est la valeur "pas de pion"
}

Board::~Board()
{

}


void Board::draw(const unsigned int& x = 12,
		 const unsigned int& y = 8)
{
  /**
   * Dessine le plateau dans la console à la position (@a x, @a y). Des '|' sont
   * ajoutés entre chaque colonne, et elle est entre deux lignes de '~'.
   * La couleur de dessin du @e cadre est blanc. Les pions sont dessinés avec
   * le caractère @b ʘ, de couleur correspondant au contenu de la matrice 
   * converti en @e Color.
   * @param x abscisse du point supérieur gauche
   * @param y abscisse du point supérieur droit
   */
  Console::getInstance()->setForeground( Color::WHITE);
  Console::getInstance()->setCursor(x,y);
  Console::getInstance()->drawRectangle(x, y, 2*getWidth()+1, 1, '~');
  Console::getInstance()->drawRectangle(x, y+getHeight()+1, \
                                        2*getWidth()+1, 1, '~');
  for(unsigned int row = 0; row < getHeight(); row++)
    {
    unsigned int col = 0;
    for(col = 0; col < 2*getWidth(); col += 2)
      {
      Console::getInstance()->setForeground( Color::WHITE);
      Console::getInstance()->draw(x+col, y+row+1, '|');
      int content = at(col/2, row);
      // std::cerr<<"Board ("<<row<<","<<col/2<<") -> "<< content <<std::endl;
      if(content != -1)
        {
	Console::getInstance()->setForeground( (Color)content);
	Console::getInstance()->draw(x+col+1, y+row+1, "ʘ");
        }else
        {
          Console::getInstance()->draw(x+col+1, y+row+1, ' ');
        }
    }
    Console::getInstance()->setForeground( Color::WHITE);
    Console::getInstance()->draw(x+col, y+row+1, '|');
  }
}
