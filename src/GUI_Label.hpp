#ifndef GUI_LABEL_HPP
#define GUI_LABEL_HPP

#include "Event.hpp"
#include "GUI_Component.hpp"

#include <string>

namespace GUI{

  class Label : public Component{

  public:
    Label(const std::string&);
    ~Label();
    virtual void setFont(const sf::Font&);
    virtual void setCharacterSize(const unsigned int&);
    virtual void setString(const std::string& );
    virtual bool checkMouse(const unsigned int& x, const unsigned int& y) const;
    virtual void draw(sf::RenderTarget& t, sf::RenderStates s) const;

  protected:
    sf::Text text;

  };

}

#endif
