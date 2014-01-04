#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

/**
 * Classe de matrice 2x2 génériques.
 * c'est juste un tableau.
 */
template <class T>
class Matrix{

protected:
  std::vector< T > mData; 
  unsigned int mWidth;
  unsigned int mHeight;

public:
  Matrix(const unsigned int&, const unsigned int&);
  virtual ~Matrix();
  virtual T& at(const unsigned int&, const unsigned int&);
  virtual T get(const unsigned int&, const unsigned int&) const;
  virtual unsigned int getHeight() const;
  virtual unsigned int getWidth() const;
  virtual void set(const unsigned int&, const unsigned int&, const T&);
  virtual void fillWith(const T&);
  virtual std::vector<T> getData() const;
  virtual std::ostream& operator<<(std::ostream&);
  template <class X> friend std::ostream &operator<<(std::ostream&, const Matrix<X> &);

};


template <class T>
Matrix<T>::Matrix(const unsigned int& w,
                  const unsigned int& h ){
  mWidth = w;
  mHeight = h;
  mData.reserve(w*h);
}

template <class T>
Matrix<T>::~Matrix(){
  mData.clear();
}

template <class T>
T& Matrix<T>::at(const unsigned int& x, 
                 const unsigned int& y)
{
  /**
   * Retourne un référence à l'élément à la position (@a x, @a y), qui est donc
   * utilisable comme L-value.
   * @param x abscisse de l'élément à récupérer
   * @param y abscisse de l'élément à récupérer
   * @return renvoie l'élément (x,y) ou lance une exception (vraiment ?)
   * @TODO vérifier les dépassements : est-ce que @e at renvoie une exception ?
   */
  return mData.at(y*mWidth+x);
}

template <class T>
T Matrix<T>::get(const unsigned int& x, 
                 const unsigned int& y) const
{
  /**
   * Retourne une copie de  l'élément à la position (@a x, @a y).
   * @param x abscisse de l'élément à récupérer
   * @param y abscisse de l'élément à récupérer
   * @return renvoie l'élément (x,y) ou lance une exception (vraiment ?)
   * @TODO vérifier les dépassements : est-ce que @e at renvoie une exception ?
   */
  return mData.at(y*mWidth+x);
}

template <class T>
unsigned int Matrix<T>::getWidth() const
{
  return mWidth;
}

template <class T>
unsigned int Matrix<T>::getHeight() const
{
  return mHeight;
}

template <class T>
void Matrix<T>::set(const unsigned int& x, 
                    const unsigned int& y, 
                    const T& t)
{
  /**
   * Remplace un élément de la matrice par un élément donné. 
   * Equivalent à une affectation après @e at.
   * @param x abscisse de l'élément à remplacer
   * @param y abscisse de l'élément à remplacer
   * @param t élément à copier dans la matrice.
   */
  mData.at(y*mWidth+x) = t;
}

template <class T>
std::vector<T> Matrix<T>::getData() const
{
  /**
   * Renvoie l'ensemble des données dans 1 tableau.
   * @return retourne dans un tableau tous les éléments de la matrice.
   * @TODO vérifier que c'est bien utile.
   */
  return mData;
}

template <class T>
void Matrix<T>::fillWith(const T& t)
{
  /**
   * Remplie la matrice avec une valeur donnée. 
   * @param t élément qu'on retrouvera partout ailleurs.
   */
  mData.clear();
  const unsigned int Threshold = getWidth()*getHeight();
  for(unsigned int i = 0; i < Threshold; i++)
    mData.push_back(t);
}

template <class T>
std::ostream& Matrix<T>::operator<<(std::ostream & s)
{
  /**
   * Ecrit la matrice sur le flux donné. Une matrice 3x2 d'entiers sera écrite
   * selon le motif suivant : 
   * ~~~~~~~
   * |1|2|3|
   * |4|5|6|
   * ~~~~~~~
   * @param s flux sur lequel ajouter la matrice
   * @return renvoie le flux paramètre, où la matrice a été écrite
   */
  for(unsigned int col = 0; col < mWidth; col++)
    {
      s << "-";
    }
  for(unsigned int row = 0; row < mHeight; row++)
    {
      for(unsigned int col = 0; col < mWidth; col++)
        {
          s << "|" << at(row, col);
        }
      s << "|" << std::endl;
    }
  
  for(unsigned int col = 0; col < mWidth; col++){
    s << "-";
  }
  return s;
}

template <class T>
std::ostream& operator<<(std::ostream & s, 
                         const Matrix<T>& m)
{
  /**
   * Ecrit la matrice donnée sur le flux donné. Une matrice 3x2 d'entiers sera 
   * écrite selon le motif suivant : 
   * ~~~~~~~
   * |1|2|3|
   * |4|5|6|
   * ~~~~~~~
   * @param s flux sur lequel ajouter la matrice
   * @param m matrice à écrire
   * @return renvoie le flux paramètre, où la matrice a été écrite
   */
  for(unsigned int col = 0; col < m.getWidth(); col++)
    s << "-";
  s << std::endl;
  for(unsigned int row = 0; row < m.getHeight(); row++)
    {
      for(unsigned int col = 0; col < m.getWidth(); col++)
        {
          s << "|" << m.at(row, col);
        }
      s << "|"<<std::endl;
    }

  for(unsigned int col = 0; col < m.getWidth(); col++)
    {
      s << "-";
    }
  return s;
}


#endif
