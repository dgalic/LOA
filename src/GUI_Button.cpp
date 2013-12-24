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

namespace GUI{
  
  Button::Button(const std::string& s,
		 const Color& c,
		 const std::function<void()>& f)
    : Component(), color(c), action(f){
    text.setString(s);
    text.setCharacterSize(48);
    text.setFont( * FontManager::getInstance()->get("fonts/ArialPixel.ttf") );
    centerText();
  
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
    selected = true;
    color = Color(color.r+50, color.g+50, color.b+50);
  }

  void Button::onDeselection(){
    Component::onDeselection();
    color = Color(color.r-50, color.g-50, color.b-50);
    selected = false;
  }

  void Button::onActivation(){
    Component::onActivation();
    std::cerr<<"actionning..." <<std::endl;
    action();
    std::cerr<<"actionned" <<std::endl;
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
    std::cerr<< "mouse is in button ("<< p.x+r.left-5<<","<<p.y+r.top-5<<"),("<<p.x+r.left+r.width+5<<","<<p.y+r.top+r.height+5<<") ?"<<res <<std::endl;
    return res;
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
    r.setFillColor(color);
    r.setOutlineColor(Color(10, 10, 10) );
    r.setOutlineThickness(2);
    t.draw(r, s);
    t.draw(text, s);
    std::cerr<<"drawing button "<<text.getString().toAnsiString()<<" at "<<getAbsolutePosition().x<<","<<getAbsolutePosition().y<<" | "<<fr.width<<"x"<<fr.height<<std::endl;
    /*
    std::cerr<< "position bouton play : "<<	\
    this->getPosition().x << ","<<	\
    this->getPosition().y << \
    "global bounds bouton play : "<< \
    this->getText().getGlobalBounds().left <<"," <<	\
      this->getText().getGlobalBounds().top << std::endl;
    */
  }
  
}
