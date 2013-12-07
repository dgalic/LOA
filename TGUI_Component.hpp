#ifndef TGUI_COMPONENT_HPP
#define TGUI_COMPONENT_HPP

namespace TGUI{

  class Component{
    
  public:
    Component();
    ~Component();
    /** drawing the component : 
     should return true if everything could have been drawn,
    false otherwise */
    virtual void draw() const = 0;
  };

};

#endif
