#include "GUI_Button.hpp"
#include "GUI_Component.hpp"

#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Color.hpp"
#include "Event.hpp"

#include "ResourceManager.hpp"

#include "Helpers.hpp"

namespace GUI{
  
  Button::Button(const std::string& s,
		 const Color& c,
		 const std::function<void()>& f)
    : Component(), normal_color(c), action(f){
    text.setString(s);
    text.setCharacterSize(48);
    text.setFont( * FontManager::getInstance()->get("fonts/ArialPixel.ttf") );
    centerText();
    normal_color = Color(c.r, c.g, c.b, c.a);
    if(c.r+c.g+c.b >= 3*160){
      //couleur claire : hover par défaut plus sombre
      hover_color = Color(max(c.r-50, 0), max(c.g-50, 0), max(c.b-50,0), c.a );
    }else{
      //couleur sombre : hover par défaut plus clair
      hover_color = Color(min(c.r+50, 255), min(c.g+50, 255), min(c.b+50, 255), c.a );
    }

  }

  Button::~Button(){

  }

  sf::Text Button::getText() const{
    return text;
  }

  void Button::centerText(){
    sf::FloatRect t = text.getGlobalBounds();
    //    text.setOrigin(t.width/2, t.height/2);
    //    text.setPosition(sf::Vector2f(t.left+t.width/2, t.top+t.height/2) ) ;
  }

  void Button::setPosition(const float& x, const float& y){
    Transformable::setPosition(x, y);
    text.setPosition( x+5, y+5 );
    //        centerText();
  }

  bool Button::isSelectable() const{
    return true;
  }

  void Button::onSelection(){
    Component::onSelection();
    normal_color = hover_color;
    selected = true;
  }

  void Button::onDeselection(){
    Component::onDeselection();
    selected = false;
  }

  void Button::onActivation(){
    Component::onActivation();
    action();
  }

  void Button::onDesactivation(){
    Component::onDesactivation();
  }

  bool Button::checkMouse(const unsigned int& x, const unsigned int& y) const{
    sf::FloatRect r = text.getGlobalBounds();
    sf::Vector2f p = getAbsolutePosition();
    bool res = (
	   x >= p.x+r.left-5 &&
	   y >= p.y+r.top-5 &&
	   x <= p.x+r.left+r.width+5 &&
	   y <= p.y+r.top+r.height+5
	   );
    return res;
  }

  void Button::setAction(const std::function<void()>& f){
    action = f;
  }  

  void Button::setColor(const Color& c){
    normal_color = Color(c.r, c.g, c.b, c.a);
  }

  void Button::setHoverColor(const Color& c){
    hover_color = Color(c.r, c.g, c.b, c.a);
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

  void Button::handle(const Event& e){   
    switch(e.type){
    case sf::Event::MouseButtonPressed:
      if(selected && e.mouseButton.button == sf::Mouse::Left)
	  onActivation();
      break;

    case sf::Event::MouseMoved:
      if(checkMouse(e.mouseMove.x, e.mouseMove.y) ){
	if(not selected)
	  onSelection();
      }
      else{
	if(selected)
	  onDeselection();
      }
      break;
	
    default:
      break;
    }
  }
  
  void Button::draw(sf::RenderTarget& t, sf::RenderStates s) const{
    s.transform *= getTransform();
    sf::RectangleShape r;
    sf::FloatRect fr = text.getGlobalBounds();
    r.setSize(sf::Vector2f(fr.width+10, fr.height+10) );
    r.setPosition(getPosition().x, getPosition().y);
    r.setFillColor(normal_color);
    r.setOutlineColor(Color(10, 10, 10) );
    r.setOutlineThickness(2);
    t.draw(r, s);
    t.draw(text, s);

  }
  
}
