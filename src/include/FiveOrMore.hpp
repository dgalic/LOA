#ifndef FIVEORMORE_HPP
#define FIVEORMORE_HPP

#include "BoardGame.hpp"

#include "Color.hpp"

#include <list>

class FiveOrMore : virtual public BoardGame{

private:
  static const std::list<Color> sColorList;

public:
  FiveOrMore();
  virtual ~FiveOrMore();

};

#endif
