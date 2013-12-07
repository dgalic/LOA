#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

//////////////////////////////////////////////////
//////////////////////////////////////////////////
///// This class is a wrapper to easily work /////
///// with matrix. In fact, it is just an    /////
///// array of arrays.                       /////
//////////////////////////////////////////////////
//////////////////////////////////////////////////

template <typename T>
class Matrix<T>{

 protected:
  T[][] data;
  unsigned int width;
  unsigned int height;

 public:
  Matrix(const unsigned int&, const unsigned int&, const T&);
  Matrix recreate(const unsigned int&, const unsigned int&);
  T get(const unsigned int&, const unsigned int&) const;
  unsigned int getHeight() const;
  unsigned int getWidth() const;
  void insert(const T[]&, const unsigned int&);
  void insert(const T&, const unsigned int&, const unsigned int&);


};



template <typename T>
Matrix<T>::Matrix(const unsigned int& w, 
	       const unsigned int& h, 
	       const T& defvalue){
  /*
    for(int i = 0; i < h; i++){
    std::vector<T> tmp;
    for(int j = 0, j < w; j++){
    tmp.push_back(defvalue);
    }
    data.push_back(tmp);
    }*/
  this->width = w;
  this->height = h;
  data = new T[w][h];
}

template <typename T>
Matrix<T> Matrix<T>::recreate(const unsigned int& w, 
		 const unsigned int& h
		 ){
  delete[] data;
  this->width = w;
  this->height = h;
  data = new T[w][h];
  
}

template <typename T>
T Matrix<T>::get(const unsigned int& x,
      const unsigned int& y){
  if(x < this->width && y < this->height)
    return data[x][y];
  else
    return T(); // raise exception instead
}

template <typename T>
unsigned int Matrix<T>::getHeight() const{
  return this->height;
}

template <typename T>
unsigned int Matrix<T>::getWidth() const{
  return this->width;
}

template <typename T>
void Matrix<T>::insert(const T[]& tab, 
	    const unsigned int& x){
  data[x] = tab;
}

template <typename T>
void Matrix<T>::insert(const T& elmt, 
	    const unsigned int& x, 
	    const unsigned int& y){
  data[x][y] = elmt;
}


#endif
