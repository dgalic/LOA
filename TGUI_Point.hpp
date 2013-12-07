#ifndef TGUI_POINT_HPP
#define TGUI_POINT_HPP

#include "TGUI_Color.hpp"
#include "TGUI_Colorful.hpp"


namespace TGUI{

  class Point: public Colorful{

  protected:
    char character;
    int positionX;
    int positionY;

  public:
    Point(const int& = 0, const int& = 0, 
	       const Color::Color_t& = Color::BLACK, 
	       const Color::Color_t& = Color::BLACK,
	  const char& = ' ');
    Point(const Point&);
    ~Point();
    char getChar() const;
    void setChar(const char &);
    void setX(const int&);
    void setY(const int&);
    void setPosition(const int&, const int&);
    int getX() const;
    int getY() const;
    virtual void draw() const;
  };

};

#endif
