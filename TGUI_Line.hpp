#ifndef TGUI_LINE_HPP
#define TGUI_LINE_HPP

#include "TGUI_Colorful.hpp"
#include "TGUI_Component.hpp"

namespace TGUI{
  class Line: public Colorful{

  private:
    int x1;
    int y1;
    int x2;
    int y2;
    char character;
    /** balances the points, to make point 1 is always at the left. 
     Thus, we just check the Y to know in which direction we should draw */
    void balance();

  public:
    Line(const int& = 0, const int& = 0, 
	     const int& = 0, const int& = 0, 
	     const Color::Color_t& = Color::BLACK, 
	     const Color::Color_t& = Color::BLACK, 
	 const char& = ' ');
    ~Line();
    void setPoint1(const int&, const int&);
    void setPoint2(const int&, const int&);
    void setX1(const int&);
    void setY1(const int&);
    void setX2(const int&);
    void setY2(const int&);
    void setChar(const char&);
    int getX1() const;
    int getY1() const;
    int getX2() const;
    int getY2() const;
    char getChar() const;
    virtual void draw() const;
  };

};
#endif
