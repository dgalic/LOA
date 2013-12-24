

#include "ResourceManager.hpp"

#include "Font.hpp"

#include <map>
#include <string>

template <class T>
void ResourceManager<T>::load(const std::string& name){
  T * t;
  if(t->loadFromFile(name) )
    map.insert( std::pair<std::string, T*>(name, t) );
}

template <class T>
T * ResourceManager<T>::get(const std::string& name){
  auto tcouple = map.find(name);
  return tcouple->second;
}

template <class T>
const T * ResourceManager<T>::get(const std::string& name) const{
  auto tcouple = map.find(name);
  return tcouple->second;
}

Font * FontManager::getLabelFont(){
  return getInstance()->get("fonts/ArialPixel.ttf");
}
