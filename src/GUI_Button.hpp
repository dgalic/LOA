#ifndef GUI_BUTTON_HPP
#define GUI_BUTTON_HPP

#include <string>
#include <functional>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Color.hpp"
#include "GUI_Component.hpp"


namespace GUI{

  class Button:public Component{
    
  public:
    Button(const std::string&, const Color&, const std::function<void()>&);
    ~Button();
    void centerText();
    void setAction(const std::function<void()>&);  
    void setColor(const Color&);
    void setFont(const sf::Font&);
    void setCharacterSize(const unsigned int&);
    void setString(const std::string& );
    virtual bool isSelectable() const;
    virtual void onSelection();
    virtual void onDeselection();
    virtual void onActivation();
    virtual void onDesactivation();
    virtual bool checkMouse(const unsigned int&, const unsigned int&) const;
    virtual void handle(const sf::Event& e);
    virtual void draw(sf::RenderTarget&, sf::RenderStates ) const;

  protected:
    sf::Text text;
    Color color;
    std::function<void()> action;
  };

}

#endif
