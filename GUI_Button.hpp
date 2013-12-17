#ifndef GUI_BUTTON_HPP
#define GUI_BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace GUI{

  class Button:public Component{
    
  public:
    Button(const std::string&, const std::function<void()>&);
    ~Button();
    virtual void setAction(const std::function<void()>&);   
    virtual void setFont(const sf::Font&);
    virtual void setCharacterSize(const unsigned int&);
    virtual void setString(const std::string& );

  protected:
    sf::Text text;
    sf::Sprite sprite;
    std::function<void()> action;
  };

}

#endif
