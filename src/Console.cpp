#include "Console.hpp"
#include "ANSI.hpp"
#include "Helpers.hpp"

#include <string>
#include <iostream>

Console::Console(){
  width = 80;
  height = 24;
  cursorX = 0;
  cursorY = 0;
  framerate = 40;
  currentBG = ANSI::Color::BLACK;
  currentFG = ANSI::Color::WHITE;
  showCursor(false);
  setBlocking(false);

}

char Console::getInput() const{
  char c;
  std::cin >> c;
  return c;
}

void Console::exit(){
  clear();
  showCursor(true); 
  setBlocking(true);
}

void Console::setBlocking(const bool& b){
  if(b){
    /* Setting the terminal for validating inputs */
    system("stty -cbreak");   
    system("stty icanon"); 
    system("stty echo");
  }else{
    /* Setting the terminal for non-validating inputs */
    system("stty cbreak");   
    system("stty -icanon"); 
    system("stty -echo");
  }
}

unsigned short Console::getWidth() const{
  return width;
}

unsigned short Console::getHeight() const{
  return height;
}

void Console::setWidth(const unsigned short& w){
  width = w;
}

void Console::setHeight(const unsigned short& h){
  height = h;
}

ANSI::Color Console::getBackground() const{
  return this->currentBG;
}

ANSI::Color Console::getForeground() const{
  return this->currentFG;
}

/* changes the background color */
void Console::setBackground(const ANSI::Color& bc){
  this->currentBG = bc;
  //    std::cout<<CSI<<bc<<"m";
  std::cout<<CSI<<"48;5;"<<bc<<"m";
}

/* changes the foreground color */
void Console::setForeground(const ANSI::Color& fc){
  this->currentFG = fc;
  //    std::cout<<CSI<<fc<<"m";
  std::cout<<CSI<<"38;5;"<<fc<<"m";
}

unsigned short Console::getCursorX() const{
  return this->cursorX;
}

unsigned short Console::getCursorY() const{
  return this->cursorY;
}

/** changes the cursor's position to the given coordinates */    
void Console::setCursor(const unsigned short& x, const unsigned short& y){
  this->cursorX = min(x, width);
  this->cursorY = min(y, height);
  std::cout<<CSI<<this->cursorY<<";"<<this->cursorX<<"H";
}

/** changes the cursor's X */
void Console::setCursorX(const unsigned short& x){
  this->cursorX = min(x, width);
  std::cout<<CSI<<this->cursorY<<";"<<this->cursorX<<"H";
}

/** changes the cursor's Y */
void Console::setCursorY(const unsigned short& y){
  this->cursorY = min(y, height);
  std::cout<<CSI<<this->cursorY<<";"<<this->cursorX<<"H";
}

void Console::setFramerate(const double& f){
  this->framerate = f;
}

double Console::getFramerate() const{
  return this->framerate;
}

void Console::draw(const char& c = ' ') {
  if( this->cursorX > 0 
      and this->cursorY > 0
      and this->cursorX <= this->width
      and this->cursorY <= this->height){
    std::cout<<c;
  }
}

void Console::draw(const std::string& s){
  if( this->cursorX > 0 
      and this->cursorY > 0
      and this->cursorX <= this->width
      and this->cursorY <= this->height){
    std::cout<<s.substr(0, this->width - this->cursorX+1 );
  }
}

void Console::drawRectangle(const unsigned short& originX, const unsigned short& originY, 
			    const unsigned short& w, const unsigned short& h,
			    const char& c = ' '){
  unsigned short previousX = Console::getInstance()->getCursorX();
  unsigned short previousY = Console::getInstance()->getCursorY();
  unsigned short x1 = originX, y1 = originY;
  unsigned short x2 = x1+w, y2 = y1+h;
  for(unsigned short y = y1; y < y2; y++){
    for(unsigned short x = x1; x < x2; x++){
      Console::getInstance()->setCursor(x, y);
      Console::getInstance()->draw(c);
    }
  }
  Console::getInstance()->setCursor(previousX, previousY);
}

void Console::drawRectangle(const unsigned short& w, const unsigned short& h, const char& c = ' '){
  drawRectangle(cursorX, cursorY, w, h, c);
}


void Console::showCursor(const bool& b) const{
  if(b)
    std::cout<<CSI<<"?25l";
  else
    std::cout<<CSI<<"?25h";  
}


void Console::clear(){
  std::cout<<ESC<<"c";
}

/* move the cursor by the given vector */
void Console::moveCursor(const int& vx, const int& vy){
  setCursor(cursorX + vx, cursorY += vy);
}

/* move the cursor on its line of the given amount */
void Console::moveCursorX(const int& vx){
  setCursorX(cursorX + vx);
  std::cout<<CSI<<this->cursorY<<";"<<this->cursorX<<"H";
}

/* move the cursor on its line of the given amount */
void Console::moveCursorY(const int& vy){
  setCursorY(cursorY+ vy);
  std::cout<<CSI<<this->cursorY<<";"<<this->cursorX<<"H";
}

/** plays a little sound */
void Console::beep() const{
  std::cout<<ESC<<"G";
}
