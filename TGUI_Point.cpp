
#include "TGUI_Point.hpp"

#include "TGUI_Color.hpp"
#include "TGUI_Colorful.hpp"
#include "TGUI_Render.hpp"


namespace TGUI{

  Point::Point(const int& x, const int& y, 
	       const Color::Color_t& bc,
	       const Color::Color_t& fc,
	       const char& c)
    : Colorful(bc, fc), positionX(x), positionY(y), character(c)
  {}

  Point::Point(const Point& other){
    this->positionX = other.getX();
    this->positionY = other.getY();
    this->background = other.getBackground();
    this->foreground = other.getForeground();
    this->character = other.getChar();
  }

  Point::~Point(){}


  char Point::getChar() const{
    return this->character;
  }


  void Point::setChar(const char & c){
    this->character = c;
  }


  void Point::setX(const int& x){
    this->positionX = x;
  }

  void Point::setY(const int& y){
    this->positionY = y;
  }

  void Point::setPosition(const int& x, const int& y){
    setX(x);
    setY(y);
  }

  int Point::getX() const{
    return positionX;
  }

  int Point::getY() const{
    return positionY;
  }

  void Point::draw() const{
    /* saving previous state */
    int previousX = Render::getInstance()->getCursorX();
    int previousY = Render::getInstance()->getCursorY();
    Color::Color_t previousBG = Render::getInstance()->getBackground();
    Color::Color_t previousFG = Render::getInstance()->getForeground();
    
    /* setting the cursor at the position of the point and drawing */
    Render::getInstance()->setCursorPosition(this->positionX, this->positionY);
    Render::getInstance()->setBackground(this->background);
    Render::getInstance()->setForeground(this->foreground);
    Render::getInstance()->printChar(this->character);

    /* restoring previous state */
    Render::getInstance()->setCursorPosition(previousX, previousY);
    Render::getInstance()->setBackground(previousBG);
    Render::getInstance()->setForeground(previousFG);
  }


};
