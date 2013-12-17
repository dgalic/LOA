#include "GUI_Button.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace GUI{

  Button::Button(const std::string& s,
		 const std::function<void()> f)
    :Component(), action(f){
    text.setString(s);
    text.setCharacterSize(30);
    text.setFont(FontManager::getInstance()->getLabelFont() );
    sf::Texture t = TextureManager::getInstance()->getButtonNormal();
    sprite.setTexture(t);
    text.setPosition(sf::Vector2f(t.getSize() / 2u) ) );

}

Button::~Button(){

}

bool Button::isSelectable() const{
  return true;
}

void Button::onSelection(){
  Component::onSelection();
  sprite.setTexture(TextureManager::getInstance()->getButtonHover() );
}

void Button::onDeselection(){
  Component::onDeselection();
  sprite.setTexture(TextureManager::getInstance()->getButtonNormal() );
}

void Button::onActivation(){
  Component::onActivation();
   if(action)
    action();
 }

bool checkMouse(const unsigned int& x, const unsigned int& y) const{
  sf::FloatRect r = sprite.getGlobalBounds();
  return(
	 x > r.left &&
	 y > r.top &&
	 x < r.left+r.width &&
	 y < r.top+r.height
	 );
}

}
