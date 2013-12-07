#ifndef TGUI_RENDER_HPP
#define TGUI_RENDER_HPP

#include <queue>

#include "TGUI_Color.hpp"
#include "TGUI_Component.hpp"

void sighandler(int);

namespace TGUI{

  class Render{

  private: 
    static Render * instance;
    unsigned int width; //in columns
    unsigned int height; //in lines
    unsigned int minwidth;
    unsigned int minheight;
    unsigned int maxwidth;
    unsigned int maxheight;
    std::queue<Component * > components; //components will be drawn in order
    int cursorX; //current X of the cursor
    int cursorY; //current Y of the cursor
    Color::Color_t currentBG; //current BackGround color
    Color::Color_t currentFG; //current ForeGround color
    double framerate; // number of frame displayed per second
    Render();
    ~Render();
    
  public:
    static  Render * getInstance();
    
    bool ingame();
    /* deletes stuffs and restores states */
    void kill();

    /* at each modification of the window's size, we need to check/correct */
    void stretchWindow();

    /* getters/setter */
    
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    void setWidth(const unsigned int&);
    void setHeight(const unsigned int&);
    void setDimensions(const unsigned int&, const unsigned int&);
    void setMinWidth(const unsigned int&);
    void setMinHeight(const unsigned int&);
    void setMinDimensions(const unsigned int&, const unsigned int&);
    void setMaxWidth(const unsigned int&);
    void setMaxHeight(const unsigned int&);
    void setMaxDimensions(const unsigned int&, const unsigned int&);
    Color::Color_t getBackground() const;
    Color::Color_t getForeground() const;
    void setBackground(const Color::Color_t&);
    void setForeground(const Color::Color_t&);
    /* get current cursor's X of the terminal */
     int getCursorX() const;
    /* get current cursor's Y of the terminal */
     int getCursorY() const;
    /** changes cursor position */
    void setCursorPosition(const int&, const int&);
    /** changes the cursor's X */
    void setCursorX(const int&);
    /** changes the cursor's Y */
    void setCursorY(const int&);    
    void setFramerate(const double&);
    double getFramerate() const;
    /* displaying events */

    /** Allows showing/hiding the cursor */
    void showCursor(const bool& b);
    /** adds a component to draw during the render, 
       returns the success of the operation */
    void add(Component * const);
    /** Prints the given char if it is in the window */
    void printChar(const char& c);
    /** draw each component in order */
    void display();
    /** clear the display -the console */
    void clear();
    /** removes every component */
    void reinit();
    
    /* terminal control event*/

    /* move the cursor by the given vector */
    void moveCursorX(const int&, const int&);

    /* move the cursor on its line of the given amount */
    void moveCursorX(const int&);

    /* move the cursor on its line of the given amount */
    void moveCursorY(const int&);

    /** plays a little sound */
    void beep();

  };

};

#endif
