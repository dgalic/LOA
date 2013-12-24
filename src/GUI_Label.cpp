#include "GUI_Label.hpp"
#include "GUI_Component.hpp"

#include "ResourceManager.hpp"
#include "Singleton.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>

namespace GUI{

  Label::Label(const std::string& s)
    : Component(){
    text.setString(s);
    text.setCharacterSize(30);
    text.setFont( * FontManager::getInstance()->get("./fonts/ArialPixel.ttf") );
  }

  Label::~Label(){
    
  }

  void Label::setFont(const sf::Font& f){
    text.setFont(f);
  }

  void Label::setCharacterSize(const unsigned int& s){
    text.setCharacterSize(s);
  }

  void Label::setString(const std::string& s){
    text.setString(s);
  }

  bool Label::checkMouse(const unsigned int& x, 
			 const unsigned int& y) const{
    sf::FloatRect fr = text.getGlobalBounds();
    return(
	   x >= fr.left &&
	   y >= fr.top &&
	   x <= fr.left + fr.width &&
	   y <= fr.top + fr.height
	   );
  }

  void Label::draw(sf::RenderTarget& t, sf::RenderStates s)const{
    s.transform *= getTransform();
    t.draw(text, s);
  }


}
