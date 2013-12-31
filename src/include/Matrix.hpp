#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
//////////////////////////////////////////////////
//////////////////////////////////////////////////
///// This class is a wrapper to easily work /////
///// with 2D matrix. In fact, it is just an /////
///// array of arrays.                       /////
//////////////////////////////////////////////////
//////////////////////////////////////////////////

/**
   |1|2|3|4|5|
   |6|7|8|9|0|

2,1 = 1*width+2

 */


template <class T>
class Matrix{

 protected:
  std::vector< T > data;
  unsigned int width;
  unsigned int height;

public:
  Matrix(const unsigned int&, const unsigned int&);
  virtual ~Matrix();
  virtual T& at(const unsigned int&, const unsigned int&);
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
  width = w;
  height = h;
  data.reserve(w*h);
}

template <class T>
Matrix<T>::~Matrix(){
  data.clear();
}

template <class T>
T& Matrix<T>::at(const unsigned int& x, const unsigned int& y){
  return data.at(y*width+x);
}

template <class T>
unsigned int Matrix<T>::getWidth() const{
  return width;
}

template <class T>
unsigned int Matrix<T>::getHeight() const{
  return height;
}

template <class T>
void Matrix<T>::set(const unsigned int& x, const unsigned int& y, const T& t){
  data.at(y*width+x) = t;
}

template <class T>
std::vector<T> Matrix<T>::getData() const{
  return data;
}

template <class T>
void Matrix<T>::fillWith(const T& t){
  data.clear();
  for(unsigned int i = 0; i < width*height; i++)
    data.push_back(t);
}

template <class T>
std::ostream& Matrix<T>::operator<<(std::ostream & s){
  for(unsigned int col = 0; col < width; col++)
    s << "-";
  for(unsigned int row = 0; row < height; row++){
    for(unsigned int col = 0; col < width; col++){
      s << "|" << at(row, col);
    }
    s << "|"<<std::endl;
  }
  
  for(unsigned int col = 0; col < width; col++)
    s << "-";
  return s;
}

template <class T>
std::ostream& operator<<(std::ostream & s, const Matrix<T>& m){
  for(unsigned int col = 0; col < m.getWidth(); col++)
    s << "-";
  s << std::endl;
  for(unsigned int row = 0; row < m.getHeight(); row++){
    for(unsigned int col = 0; col < m.getWidth(); col++){
      s << "|" << m.at(row, col);
    }
    s << "|"<<std::endl;
  }

  for(unsigned int col = 0; col < m.getWidth(); col++)
    s << "-";
  return s;
}


#endif
