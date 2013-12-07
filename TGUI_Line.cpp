
#include "TGUI_Color.hpp"
#include "TGUI_Colorful.hpp"
#include "TGUI_Render.hpp"
#include "TGUI_Line.hpp"

#include <iostream>

namespace TGUI{

  Line::Line(const int& p1x, const int& p1y, 
	     const int& p2x, const int& p2y, 
	     const Color::Color_t& bc,
	     const Color::Color_t& fc,
	     const char& c) 
    : Colorful(bc, fc), x1(p1x), y1(p1y), x2(p2x), y2(p2y), character(c){
    //    balance();
  }

  Line::~Line(){}

  void Line::balance(){
    int tmp;
    /* rounding */
    if( this->x1 != this->x2){
      //if the X is not the same, Y should be the same
      this->y2 = this->y1;
    }
    //otherwise, X are in the same column, Y has to be the same
    if( this->y1 != this->y2){
      this->x2 = this->x1;
    }
    if(x2 > x1){
      tmp = x2;
      x2 = x1;
      x1 = tmp;
    }
    if(y2 > y1){
      tmp = y2;
      y2 = y1;
      y1 = tmp;
    }
      
  }

  void Line::setPoint1(const int& x, const int& y){
    this->x1 = x;
    this->y1 = y;
  }

  void Line::setPoint2(const int& x, const int& y){
    this->x2 = x;
    this->y2 = y;
  }

  void Line::setX1(const int& x){
    this->x1 = x;
  }

  void Line::setY1(const int& y){
    this->y1 = y;
  }

  void Line::setX2(const int& x){
    this->x2 = x;
  }

  void Line::setY2(const int& y){
    this->y2 = y;
  }

  void Line::setChar(const char& c){
    this->character = c;
  }

  int Line::getX1() const{
    return this->x1;
  }

  int Line::getY1() const{
    return this->y1;
  }

  int Line::getX2() const{
    return this->x2;
  }

  int Line::getY2() const{
    return this->y2;
  }

  char Line::getChar() const{
    return this->character;
  }

  void Line::draw() const{
    /* saving previous state */
    int previousX = Render::getInstance()->getCursorX();
    int previousY = Render::getInstance()->getCursorY();
    Color::Color_t previousBG = Render::getInstance()->getBackground();
    Color::Color_t previousFG = Render::getInstance()->getForeground();
 
   std::cerr<<"drawing line"<<std::endl;
    int x = this->x1, y = this->y1;
    int dirX = 0, dirY = 0;
    if(x2 > x1)
      dirX = 1;
    if(y2 > y1)
      dirY = 1; 
    Render::getInstance()->setBackground(this->background);
    Render::getInstance()->setForeground(this->foreground);
 
    while( not(x == x2 && y == y2) ){     
      std::cerr<<"drwing line's point "<<x<<","<<y<<" / "<<x2<<","<<y2<<std::endl;
      Render::getInstance()->setCursorPosition(x, y);
      Render::getInstance()->printChar(this->character);
      x += dirX;
      y += dirY;
    } 
    
    // a last print (for the case where the two points at the same position */
    Render::getInstance()->setCursorPosition(x, y);
    Render::getInstance()->printChar(this->character);
   
    
    /* restoring previous state */
    Render::getInstance()->setCursorPosition(previousX, previousY);
    Render::getInstance()->setBackground(previousBG);
    Render::getInstance()->setForeground(previousFG);
  }
  
};
