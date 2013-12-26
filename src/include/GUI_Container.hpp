#ifndef GUI_CONTAINER_HPP
#define GUI_CONTAINER_HPP

#include "GUI_Component.hpp"

#include <vector>

#include <SFML/Window.hpp>

namespace GUI{

  class Container: public Component{
    
  protected:
    std::vector<Component *> subcomponents;
    Component * selectedChild;
    
  public:
    Container();
    ~Container();
    virtual void handle(const Event&);
    virtual void add(Component *);
    virtual void select(const unsigned int&);
    virtual bool hasSelection() const;
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
  };

}
#endif
