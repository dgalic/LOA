#ifndef TGUI_CIRCLE_HPP
#define TGUI_CIRCLE_HPP

#include "TGUI_Color.hpp"
#include "TGUI_Colorful.hpp"
#include "TGUI_Point.hpp"

namespace TGUI{

  class Circle: public Colorful{

  private:    
    Point center; /* defines also the color and character */
    int radius;
    
  public:
    Circle(const Point&,
	   const int& = 0);
    Circle(const int& = 0,
 	   const int& = 0,
	   const int& = 0,
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
    int getRadius() const;
    void setRadius(const int&);
    Color::Color_t getBackground() const;
    Color::Color_t getForeground() const;
    void setBackground(const Color::Color_t &);
    void setForeground(const Color::Color_t &);

    virtual void draw() const;

  };

};

#endif
