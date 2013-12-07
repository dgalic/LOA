#include "TGUI_Circle.hpp"

#include "TGUI_Color.hpp"
#include "TGUI_Line.hpp"
#include "TGUI_Render.hpp"

#include <cmath>
#include <iostream>

#define PI 3.14159265

namespace TGUI{

  Circle::Circle(const Point& p, 
		 const int& r)
    : center(p), radius(r)
  { }

  Circle::Circle(const int& x,
		 const int& y,
		 const int& r,
		 const Color::Color_t& bc,
		 const Color::Color_t& fc,
		 const char & c){
    Point p(x, y, bc, fc, c);
    center = p;
    this->radius = r;
  }

  void Circle::setX(const int& x){
    this->center.setX(x);
  }

  void Circle::setY(const int& y){
    this->center.setY(y);
  }

  void Circle::setPosition(const int& x, const int& y){
    this->center.setPosition(x, y);
  }

  int Circle::getX() const{
    return this->center.getX();
  }

  int Circle::getY() const{
    return this->center.getY();
  }

  char Circle::getChar() const{
    return this->center.getChar();
  }

  void Circle::setChar(const char & c){
    this->center.setChar(c);
  }

  int Circle::getRadius() const{
    return this->radius;
  }

  void Circle::setRadius(const int& r){
    this->radius = r;
  }

  Color::Color_t Circle::getBackground() const{
    return this->center.getBackground();
  }

  Color::Color_t Circle::getForeground() const{
    return this->center.getForeground();
  }

  void Circle::setBackground(const Color::Color_t & bc){
    this->center.setBackground(bc);
  }

  void Circle::setForeground(const Color::Color_t & fc){
    this->center.setForeground(fc);
  }

  void Circle::draw() const{
    /* a circle whose radius is 0 cannot be drawn */
    if( this->radius <= 0)
      return;
    /* saving previous state */
    int previousX = Render::getInstance()->getCursorX();
    int previousY = Render::getInstance()->getCursorY();
    Color::Color_t previousBG = Render::getInstance()->getBackground();
    Color::Color_t previousFG = Render::getInstance()->getForeground();
 
    Color::Color_t bc = this->getBackground();
    Color::Color_t fc = this->getForeground();
    char ch = this->getChar();
  
    /* We are drawing the circle using the algorithm of Andres */
    int r = this->radius;
    int x, y, d;
    int x_center = this->getX(), y_center = this->getY();
    Point p = this->center;
    while(r >= 0){
      x = 0, y = r, d = r-1;
      while( y >= x){
	p.setPosition(x_center+x, y_center+y);
	p.draw();
	p.setPosition(x_center+y, y_center+x);
	p.draw();
	p.setPosition(x_center-x, y_center+y);
	p.draw();
	p.setPosition(x_center-y, y_center+x);
	p.draw();
	p.setPosition(x_center+x, y_center-y);
	p.draw();
	p.setPosition(x_center+y, y_center-x);
	p.draw();
	p.setPosition(x_center-x, y_center-y);
	p.draw();
	p.setPosition(x_center-y, y_center-x);
	p.draw();
	if( d >= 2*x){
	  d -= 2*x;
	  x++;
	}else if (d < 2*(r-y) ){
	  d += 2*y-1;
	  y--;
	}else{
	  d += 2*(y-x-1);
	  y--;
	  x++;
	}
      }
      
      r--;
    }
    
    /* restoring previous state */
    Render::getInstance()->setCursorPosition(previousX, previousY);
    Render::getInstance()->setBackground(previousBG);
    Render::getInstance()->setForeground(previousFG);
  }

};
