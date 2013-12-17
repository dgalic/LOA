#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template <class T>
class Singleton{

private:
  T& operator=(const T&){};

public:
  static T * getInstance();
  
protected:
  static T instance;

};


/////////////////////////////////////////////
/////////////////////////////////////////////

template <class T> T Singleton<T>::instance=T();

template <class T> T& Singleton<T>::getInstance(){
  return instance;
}

#endif
