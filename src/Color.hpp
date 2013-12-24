#ifndef COLOR_HPP
#define COLOR_HPP

#include <SFML/Graphics/Color.hpp>

class Color:public sf::Color{

public:
  Color(const unsigned int& r,
	const unsigned int& g,
	const unsigned int& b):sf::Color(r,g,b){};

};

#endif
