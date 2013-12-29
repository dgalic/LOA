#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <string>

#include "Singleton.hpp"


template <class T>
class ResourceManager:public Singleton<ResourceManager<T> >{

  friend class Singleton<ResourceManager<T> >;

public:
  T * load(const std::string&);
  T * get(const std::string&);
  void remove(const std::string&);

private:
  std::map<std::string, T *> map;
};

class ResourceException{
public:
  const std::string res;
  ResourceException(const std::string& r):res(r){};
};

///////

template <class T>
T * ResourceManager<T>::load(const std::string& name){
  T * t = new T();
  if( t->loadFromFile(name) ){
    map.insert( std::pair<std::string, T*>(name, t) );

  }else{
    // balancer une exception : "ressource non trouvée"
    throw ResourceException("Cannot find ressource \""+name+"\"");
  }
  return t;
}

template <class T>
T * ResourceManager<T>::get(const std::string& name){
  auto tcouple = map.find(name);
  if( tcouple == map.end() ){
    return load(name);
  }
  return tcouple->second;
}


template <class T>
void ResourceManager<T>::remove(const std::string& name){
  auto t = map.find(name);
  if( t != map.end() )
    map.erase(t);
}





#endif
