#include "TGUI_Colorful.hpp"

namespace TGUI{
  
  Colorful::Colorful(const Color::Color_t& bc, 
		     const Color::Color_t& fc)
    : background(bc), foreground(fc) {
    
    }

  Color::Color_t Colorful::getBackground() const{
    return this->background;
  }

  Color::Color_t Colorful::getForeground() const{
    return this->foreground;
  }


  void Colorful::setBackground(const Color::Color_t & bc){
    this->background = bc;
  }

  void Colorful::setForeground(const Color::Color_t & fc){
    this->foreground = fc;
  }
};
