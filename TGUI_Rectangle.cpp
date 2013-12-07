#include "TGUI_Rectangle.hpp"

#include "TGUI_Color.hpp"
#include "TGUI_Point.hpp"
#include "TGUI_Render.hpp"

#include <iostream>

namespace TGUI{

  Rectangle::Rectangle(const Point& o,
		       const unsigned int& w,
		       const unsigned int& h
		       )
    : origin(o), width(w), height(h) {
  }

  Rectangle::Rectangle(
		       const int& x,
		       const int& y,
		       const unsigned int& w,
		       const unsigned int& h,
		       const Color::Color_t& bc,
		       const Color::Color_t& fc,
		       const char& c){
    Point p(x, y, bc, fc, c);
    origin = p;
    this->width = w;
    this->height = h;
  }

  void Rectangle::setX(const int& x){
    this->origin.setX(x);
  }

  void Rectangle::setY(const int& y){
    this->origin.setY(y);
  }

  void Rectangle::setPosition(const int& x, const int& y){
    this->origin.setPosition(x, y);
  }

  int Rectangle::getX() const{
    this->origin.getX();
  }

  int Rectangle::getY() const{
    this->origin.getY();
  }

  char Rectangle::getChar() const{
    this->origin.getChar();
  }

  void Rectangle::setChar(const char & c){
    this->origin.setChar(c);
  }

  void Rectangle::setDimensions(const unsigned int& w , const unsigned int& h){
    this->width = w;
    this->height = h;
  }

  void Rectangle::setWidth(const unsigned int& w){
    this->width = w;
  }

  void Rectangle::setHeight(const unsigned int& h){
    this->height = h;
  }

  unsigned int Rectangle::getWidth() const{
    return this->width;
  }

  unsigned int Rectangle::getHeight() const{
    return this->height;
  }


  Color::Color_t Rectangle::getBackground() const{
    return this->origin.getBackground();
  }

  Color::Color_t Rectangle::getForeground() const{
    return this->origin.getForeground();
  }

  void Rectangle::setBackground(const Color::Color_t & bc){
    this->origin.setBackground(bc);
  }

  void Rectangle::setForeground(const Color::Color_t & fc){
    this->origin.setForeground(fc);
  }

  void Rectangle::draw() const{
    /* A rectangle whose dimension has a 0 is empty */
    if(this->width <= 0 || this->height <= 0)
      return;
    /* saving previous state */
    int previousX = Render::getInstance()->getCursorX();
    int previousY = Render::getInstance()->getCursorY();
    Color::Color_t previousBG = Render::getInstance()->getBackground();
    Color::Color_t previousFG = Render::getInstance()->getForeground();
 

    Render::getInstance()->setBackground(this->origin.getBackground() );
    Render::getInstance()->setForeground(this->origin.getForeground() );
    int x, y, x1, y1, x2, y2;
    x1 = this->origin.getX();
    x2 = x1+width;
    y1 = this->origin.getY();
    y2 = y1+height;
    for(y = y1; y < y2; y++){
      for(x = x1; x < x2; x++){
	std::cerr<<"Rectangle : "<<x<<","<<y<<std::endl;
      	Render::getInstance()->setCursorPosition(x, y);
	Render::getInstance()->printChar(this->origin.getChar() );
      }
    }

    /* restoring previous state */
    Render::getInstance()->setCursorPosition(previousX, previousY);
    Render::getInstance()->setBackground(previousBG);
    Render::getInstance()->setForeground(previousFG);

  }



};
