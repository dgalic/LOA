#include "Color.hpp"

/*

Color::Color(const unsigned int& r = 0,
	     const unsigned int& g = 0,
	     const unsigned int& b = 0,
	     const unsigned int& a = 255)
  : sf::Color(r,g,b,a) {}
*/

Color::Color(const Color& c){
  r = c.r;
  g = c.g;
  b = c.b;
  a = c.a;
}

/*
Color Color::brighter() const{
  return Color(r+20, g+20, b+20, a);
}

Color Color::darker() const{
  return Color(r-20, g-20, b-20, a);
}
*/
