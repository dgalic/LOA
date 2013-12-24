#ifndef COLOR_HPP
#define COLOR_HPP

#include <SFML/Graphics/Color.hpp>

class Color:public sf::Color{

public:
  Color():sf::Color(0,0,0){};
  Color(const unsigned int& r,
	const unsigned int& g,
	const unsigned int& b) : sf::Color(r,g,b){};
  Color(const unsigned int& r,
	const unsigned int& g,
	const unsigned int& b,
	const unsigned int& a) : sf::Color(r,g,b,a){};
  //  Color(const Color& c):sf::Color(c){};
  //  Color brighter() const;
  //Color darker() const;
};

#endif
