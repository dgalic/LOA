#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <map>
#include <string>

#include "Singleton.hpp"

#include "Font.hpp"

template <class T>
class ResourceManager:public Singleton<ResourceManager<T> >{

  friend class Singleton<ResourceManager<T> >;

public:
  void load(const std::string&);
  T * get(const std::string&);
  const T * get(const std::string&) const;

private:
  std::map<std::string, T *> map;
};



class FontManager: public ResourceManager<Font>{
  friend class ResourceManager<Font>;

public:
  static Font * getLabelFont();
};





#endif
