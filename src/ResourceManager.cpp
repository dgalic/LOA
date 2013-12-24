

#include "ResourceManager.hpp"

#include "Font.hpp"

#include <map>
#include <string>

template <class T>
T * ResourceManager<T>::load(const std::string& name){
  T * t = new T();
  if( t->loadFromFile(name) ){
    map.insert( std::pair<std::string, T*>(name, t) );

  }else{
    // balancer une exception : "ressource non trouvée"

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

Font * FontManager::getLabelFont(){
  return getInstance()->get("fonts/ArialPixel.ttf");
}
