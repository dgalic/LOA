#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
//////////////////////////////////////////////////
//////////////////////////////////////////////////
///// This class is a wrapper to easily work /////
///// with matrix. In fact, it is just an    /////
///// array of arrays.                       /////
//////////////////////////////////////////////////
//////////////////////////////////////////////////

template <class T>
class Matrix{

 protected:
  std::vector< std::vector<T> > data;
  unsigned int width;
  unsigned int height;

public:
  Matrix(const unsigned int&, const unsigned int&);
  virtual ~Matrix();
  virtual T& at(const unsigned int&, const unsigned int&);
  virtual unsigned int getHeight() const;
  virtual unsigned int getWidth() const;
  virtual void set(const unsigned int&, const unsigned int&, const T&);
  virtual std::vector< std::vector<T> > getData() const;
  virtual std::vector<T> getData(const unsigned int&) const;
  virtual std::ostream& operator<<(std::ostream&);
  template <class X> friend std::ostream &operator<<(std::ostream&, const Matrix<X> &);


};


template <class T>
Matrix<T>::Matrix(const unsigned int& w,
	       const unsigned int& h ){
  width = w;
  height = h;
  data.reserve(w);
  for(unsigned int i = 0; i < h; i++)
    data.at(i).reserve(h);
}

template <class T>
Matrix<T>::~Matrix(){
  for(unsigned int i = 0; i < width; i++)
    data.at(i).clear();
  data.clear();
}

template <class T>
T& Matrix<T>::at(const unsigned int& x, const unsigned int& y){
  return data.at(x).at(y);
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
  data.at(x).at(y) = t;
}


template <class T>
std::vector< std::vector<T> > Matrix<T>::getData() const{
  return data;
}

template <class T>
std::vector<T> Matrix<T>::getData(const unsigned int& i) const{
  return data.at(i);
}

template <class T>
std::ostream& Matrix<T>::operator<<(std::ostream & s){
  for(unsigned int j = 0; j < width; j++)
    s << "-";
  for(unsigned int i = 0; i < height; i++){
    for(unsigned int j = 0; j < width; j++){
      s << "|" << data[i][j];
    }
    s << "|"<<std::endl;
  }
  
  for(unsigned int j = 0; j < width; j++)
    s << "-";
  return s;
}

template <class T>
std::ostream& operator<<(std::ostream & s, const Matrix<T>& m){
  for(unsigned int j = 0; j < m.getWidth(); j++)
    s << "-";
  s << std::endl;
  for(unsigned int i = 0; i < m.getHeight(); i++){
    
    for(unsigned int j = 0; j < m.getWidth(); j++){
      s << "|" << m.at[i][j];
    }
    s << "|"<<std::endl;
  }

  for(unsigned int j = 0; j < m.getWidth(); j++)
    s << "-";
  return s;
}


#endif
