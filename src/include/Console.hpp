#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include "Singleton.hpp"
#include "ANSI.hpp"

#include <string>

#define ESC '\033'
#define CSI "\033["

class Console : public Singleton<Console>{


  friend class Singleton<Console >;

private:
  Console();
  unsigned short width, height;
  unsigned short cursorX; //current X of the cursor
  unsigned short cursorY; //current Y of the cursor
  ANSI::Color currentBG; //current BackGround color
  ANSI::Color currentFG; //current ForeGround color
  double framerate; // number of frame displayed per second
    
public:

  char getInput() const;
  void init();
  /* deletes stuffs and restores states */
  void exit();
  void setBlocking(const bool&);
  /* getters/setter */
  unsigned short getWidth() const;
  unsigned short getHeight() const;
  void setWidth(const unsigned short&);
  void setHeight(const unsigned short&);
  ANSI::Color getBackground() const;
  ANSI::Color getForeground() const;
  void setBackground(const ANSI::Color&);
  void setForeground(const ANSI::Color&);
  /* get current cursor's X of the terminal */
  unsigned short getCursorX() const;
  /* get current cursor's Y of the terminal */
  unsigned short getCursorY() const;
  /** changes cursor position */
  void setCursor(const unsigned short&, const unsigned short&);
  /** changes the cursor's X */
  void setCursorX(const unsigned short&);
  /** changes the cursor's Y */
  void setCursorY(const unsigned short&);    
  void setFramerate(const double&);
  double getFramerate() const;
  /* displaying events */
  void draw(const unsigned short&, const unsigned short&, const char& c);
  void draw(const unsigned short&, const unsigned short&, const std::string& c);
  void drawString(const unsigned short&, const unsigned short&, const std::string& c);
  void draw(const char& c);
  void draw(const std::string& c);
  void drawString(const std::string& c);
  void drawRectangle(const unsigned short&, const unsigned short&, const unsigned short&, const unsigned short&, const char&);
  void drawRectangle(const unsigned short&, const unsigned short&, const char&);
  /** Allows showing/hiding the cursor */
  void showCursor(const bool& b) const;
  /** adds a component to draw during the render, 
      returns the success of the operation */

  /** clear the display -the console */
  void clear();
    
  /* terminal control events */

  /* move the cursor by the given vector */
  void moveCursor(const int&, const int&);

  /* move the cursor on its line of the given amount */
  void moveCursorX(const int&);

  /* move the cursor on its line of the given amount */
  void moveCursorY(const int&);

  /** plays a little sound */
  void beep() const;

};

ANSI::Arrow checkArrow(const char & c);
  


#endif
