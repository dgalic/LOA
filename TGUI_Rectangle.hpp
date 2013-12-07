#ifndef TGUI_RECTANGLE_HPP
#define TGUI_RECTANGLE_HPP


#include "TGUI_Color.hpp"
#include "TGUI_Component.hpp"
#include "TGUI_Point.hpp"

namespace TGUI{

  class Rectangle: public Component{
  protected:
    // the top-left corner, gives the colors and graphics
    Point origin;
    unsigned int width;
    unsigned int height;

  public:
    Rectangle(
	      const Point&,
	      const unsigned int& = 0,
	      const unsigned int& = 0);    
    Rectangle(
	      const int& = 0,
	      const int& = 0,
	      const unsigned int& = 0,
	      const unsigned int& = 0,
	      const Color::Color_t& = Color::BLACK,
	      const Color::Color_t& = Color::BLACK,
	      const char& = ' ');
    void setX(const int&);
    void setY(const int&);
    void setPosition(const int&, const int&);
    int getX() const;
    int getY() const;
    char getChar() const;
    void setChar(const char &);
    void setDimensions(const unsigned int&, const unsigned int&);
    void setWidth(const unsigned int&);
    void setHeight(const unsigned int&);
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    Color::Color_t getBackground() const;
    Color::Color_t getForeground() const;
    void setBackground(const Color::Color_t &);
    void setForeground(const Color::Color_t &);

    virtual void draw() const;
  };

};

#endif
