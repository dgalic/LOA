
#include <iostream>

//for stretchWindow
#include <termios.h>
#include <sys/ioctl.h>
// for signals
#include <csignal>
//for changing states of terminal
#include <cstdlib>
#include <fcntl.h>

#include "TGUI_Render.hpp"
#include "TGUI_Component.hpp"

#define ESC "\033"
#define CSI "\033["
  
void sighandler(int signo){
  std::cerr<<"received signal "<<signo<<std::endl;
  switch(signo){
  case SIGWINCH:
    TGUI::Render::getInstance()->stretchWindow();
    break;
  case SIGKILL:
    TGUI::Render::getInstance()->kill();
    break;
  case SIGQUIT:
    TGUI::Render::getInstance()->kill();
    break;
  case SIGABRT:
    TGUI::Render::getInstance()->kill();
    break;
  case SIGINT:
    TGUI::Render::getInstance()->kill();
    break;

  }

}

namespace TGUI{

  Render::Render(){
    width = 80;
    height = 24;
    minwidth = 0;
    minheight = 0;
    maxwidth = 0;
    maxheight = 0;
    cursorX = 0;
    cursorY = 0;
    framerate = 40;
    currentBG = Color::BLACK;
    currentFG = Color::BLACK;

    /* Setting the terminal for non-blocking inputs */
    system("stty cbreak");   
    system("stty -icanon"); 
    system("stty -echo");

           
    /* placing a handling for the signal that changes the window's size */
    signal(SIGWINCH, (void (*)(int))sighandler);
    signal(SIGKILL, (void (*)(int))sighandler);
    signal(SIGABRT, (void (*)(int))sighandler);
    signal(SIGQUIT, (void (*)(int))sighandler);
    signal(SIGINT, (void (*)(int))sighandler);

  }

  Render::~Render(){
    kill();
  }


  Render * Render::getInstance(){
    if(instance == NULL){
      instance = new Render();
    }
    return instance;
  }

  char Render::getInput(){
    char c;
    std::cin >> c;
    return c;
  }

  bool Render::ingame(){
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(0, &fds); //STDIN_FILENO is 0
    select(1, &fds, NULL, NULL, &tv);
    return (bool)FD_ISSET(0, &fds);
  }

  void Render::kill(){
    clear();
    system("reset");
    setBackground(Color::BLACK);
    setForeground(Color::WHITE);
    system("reset");
    showCursor(true);
    std::cerr<<"reseted terminal"<<std::endl;
    system("stty -cbreak");  
    system("stty icanon");  
    system("stty echo");
    system("stty sane");
  }


  void Render::stretchWindow(){
    struct winsize w, w2;
    ioctl(0, TIOCGWINSZ, &w);
    w2.ws_row = w.ws_row;
    w2.ws_col = w.ws_col;
    if(w.ws_row < minheight)
      w2.ws_row = minheight;
    else if(maxheight > 0 && w.ws_row > maxheight)
      w2.ws_row = maxheight;
    if(w.ws_col < minwidth)
      w2.ws_col = minwidth;
    else if (maxwidth > 0 && w.ws_col > maxwidth)
      w2.ws_col = maxwidth;
    //    std::cout<<"\e[8;"<<w2.ws_row<<";"<<w2.ws_col<<"t";
    this->width = w2.ws_col;
    this->height = w2.ws_row;
    //ioctl(0, TIOCSWINSZ, &w2);
  }

  void Render::showCursor(const bool& b){
    if(b)
      std::cout<<CSI<<"?25l";
    else
      std::cout<<CSI<<"?25h";  
  }

  unsigned int Render::getWidth() const{
    return this->width;
  }

  unsigned int Render::getHeight() const{
    return this->height;
  }

  void Render::setWidth(const unsigned int& w){
    this->width = w;
    stretchWindow();
  }

  void Render::setHeight(const unsigned int& h){
    this->height = h;
    stretchWindow();
  }

  void Render::setDimensions(const unsigned int& w, const unsigned int& h){
    this->setWidth(w);
    this->setHeight(h);
  }

  void Render::setMinWidth(const unsigned int& w){
    this->minwidth = w;
    stretchWindow();
  }

  void Render::setMinHeight(const unsigned int& h){
    this->minheight = h;
    stretchWindow();
  }

  void Render::setMinDimensions(const unsigned int& w, const unsigned int& h){
    this->minwidth = w;
    this->minheight = h;
    stretchWindow();
  }

  void Render::setMaxWidth(const unsigned int& w){
    this->maxwidth = w;
    stretchWindow();
  }

  void Render::setMaxHeight(const unsigned int& h){
    this->maxheight = h;
    stretchWindow();
  }

  void Render::setMaxDimensions(const unsigned int& w, const unsigned int& h){
    this->maxwidth = w;
    this->maxheight = h;
    stretchWindow();
  }

  Color::Color_t Render::getBackground() const{
    return this->currentBG;
  }

  Color::Color_t Render::getForeground() const{
    return this->currentFG;
  }

  /* changes the background color */
  void Render::setBackground(const Color::Color_t& bc){
    this->currentBG = bc;
    //    std::cout<<CSI<<bc<<"m";
    std::cout<<CSI<<"48;5;"<<bc<<"m";
  }

  /* changes the foreground color */
  void Render::setForeground(const Color::Color_t& fc){
    this->currentFG = fc;
    //    std::cout<<CSI<<fc<<"m";
    std::cout<<CSI<<"38;5;"<<fc<<"m";
  }

  int Render::getCursorX() const{
    return this->cursorX;
  }

  int Render::getCursorY() const{
    return this->cursorY;
  }

  /** changes the cursor's position to the given coordinates */    
  void Render::setCursorPosition(const int& x, const  int& y){
    this->cursorX = x;
    this->cursorY = y;
    std::cout<<CSI<<this->cursorY<<";"<<this->cursorX<<"H";
  }

  /** changes the cursor's X */
  void Render::setCursorX(const int& x){
    this->cursorX = x;
    std::cout<<CSI<<this->cursorY<<";"<<this->cursorX<<"H";
  }

  /** changes the cursor's Y */
  void Render::setCursorY(const int& y){
    this->cursorY = y;
    std::cout<<CSI<<this->cursorY<<";"<<this->cursorX<<"H";
  }

  void Render::setFramerate(const double& f){
    this->framerate = f;
  }

  double Render::getFramerate() const{
    return this->framerate;
  }

  void Render::add(Component * const c){
    this->components.push(c);
  }

  void Render::printChar(const char& c){
    if( this->cursorX > 0 
       && this->cursorY > 0
	&& this->cursorX < this->width
	&& this->cursorY < this->height){
      std::cout<<c;
      //      std::cerr<<"char "<<c<<" could be displayed : "<<this->cursorX<<","<<this->cursorY<<" was in the box"<<std::endl;
    }else{
      //std::cerr<<"char "<<c<<" could not be displayed : "<<this->cursorX<<","<<this->cursorY<<" was not in the box"<<std::endl;
    }
  }

  void Render::display(){
    Component * c;
    std::queue<Component *> nextQueue;
    while( not components.empty() ){
      c = this->components.front();
      c->draw();
      this->components.pop();
      nextQueue.push(c);
    }
    this->components = nextQueue;
  }

  void Render::clear(){
    std::cout<<ESC<<"c";
  }

  void Render::reinit(){
    while( not this->components.empty() ){
      this->components.pop();
    }
  }

  /* move the cursor by the given vector */
  void Render::moveCursorX(const int& vx, const int& vy){
    this->cursorX += vx;
    this->cursorY += vy;
    std::cout<<CSI<<this->cursorY<<";"<<this->cursorX<<"H";

  }

  /* move the cursor on its line of the given amount */
  void Render::moveCursorX(const int& vx){
    this->cursorX += vx;
    std::cout<<CSI<<this->cursorY<<";"<<this->cursorX<<"H";
  }

  /* move the cursor on its line of the given amount */
  void Render::moveCursorY(const int& vy){
    this->cursorX += vy;
    std::cout<<CSI<<this->cursorY<<";"<<this->cursorX<<"H";
  }

  /** plays a little sound */
  void Render::beep(){
    std::cout<<ESC<<"G";
  }


}


/* initialising to NULL the singleton */
TGUI::Render * TGUI::Render::instance = NULL;
