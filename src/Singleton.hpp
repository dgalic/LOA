#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template <class T>
class Singleton{

private:
  T& operator=(const T&){};

public:
  static T * getInstance(){
    if( instance == nullptr ){
      instance = new T();
    }
    return instance;
  }

  static void destroy(){
    delete instance;
    instance = nullptr;
  }
  
protected:
  static T * instance;

};


/////////////////////////////////////////////
/////////////////////////////////////////////

template <class T> 
T * Singleton<T>::instance= nullptr;


#endif
