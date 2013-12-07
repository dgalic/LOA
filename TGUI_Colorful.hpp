#ifndef TGUI_COLORFUL_HPP
#define TGUI_COLORFUL_HPP

#include "TGUI_Color.hpp"
#include "TGUI_Component.hpp"

namespace TGUI{
  
  class Colorful: public Component{

  protected:
    Color::Color_t background;
    Color::Color_t foreground;

  public:
    Colorful(const Color::Color_t& = Color::BLACK,
	     const Color::Color_t& = Color::BLACK);
    Color::Color_t getBackground() const;
    Color::Color_t getForeground() const;
    void setBackground(const Color::Color_t &);
    void setForeground(const Color::Color_t &);
    virtual void draw() const = 0;
  };

};

#endif
