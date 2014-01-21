#ifndef SINGLETON_HPP
#define SINGLETON_HPP

template <class T>
class Singleton{

private:
  T& operator=(const T&){};

public:
  static T * getInstance(){
    if( sInstance == nullptr ){
      sInstance = new T();
    }
    return sInstance;
  }

  static void destroy(){
    delete sInstance;
    sInstance = nullptr;
  }
  
protected:
  static T * sInstance;

};


/////////////////////////////////////////////
/////////////////////////////////////////////

template <class T> 
T * Singleton<T>::sInstance= nullptr;


#endif
