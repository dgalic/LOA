#include "GUI_Button.hpp"
#include "GUI_Component.hpp"

#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Color.hpp"

#include "ResourceManager.hpp"

namespace GUI{
  
  Button::Button(const std::string& s,
		 const Color& c,
		 const std::function<void()>& f)
    : Component(), color(c), action(f){
    text.setString(s);
    text.setCharacterSize(30);
    text.setFont( * FontManager::getInstance()->get("fonts/ArialPixel.ttf") );
    centerText();
  
  }

  Button::~Button(){

  }

  void Button::centerText(){
    sf::FloatRect t = text.getGlobalBounds();
    text.setPosition(sf::Vector2f(t.left+t.width/2, t.top+t.height/2) ) ;
  }

  bool Button::isSelectable() const{
    return true;
  }

  void Button::onSelection(){
    Component::onSelection();
  }

  void Button::onDeselection(){
    Component::onDeselection();
  }

  void Button::onActivation(){
    Component::onActivation();
    if(action)
      action();
  }

  void Button::onDesactivation(){
    Component::onDesactivation();
  }

  bool Button::checkMouse(const unsigned int& x, const unsigned int& y) const{
    sf::FloatRect r = text.getGlobalBounds();
    return(
	   x > r.left &&
	   y > r.top &&
	   x < r.left+r.width &&
	   y < r.top+r.height
	   );
  }

  void Button::setAction(const std::function<void()>& f){
    action = f;
  }  

  void Button::setColor(const Color& c){
    color = c;
  }

  void Button::setFont(const sf::Font& f){
    text.setFont(f);
  }

  void Button::setCharacterSize(const unsigned int& s){
    text.setCharacterSize(s);
    centerText();
  }

  void Button::setString(const std::string& s){
    text.setString(s);
    centerText();
  }

  void Button::handle(const sf::Event& e){   
    if(e.type == sf::Event::MouseButtonPressed){
      if(e.mouseButton.button == sf::Mouse::Left){
	onActivation();
      }
    }
  }

  void Button::draw(sf::RenderTarget& t, sf::RenderStates s) const{
    s.transform *= getTransform();
    sf::RectangleShape r;
    sf::FloatRect fr = text.getGlobalBounds();
    r.setSize(sf::Vector2f(fr.width, fr.height) );
    r.setPosition(fr.left, fr.top);
    r.setFillColor(color);
    r.setOutlineColor(Color(10, 10, 10) );
    r.setOutlineThickness(2);
    t.draw(r);
    t.draw(text);
  }
  
}
