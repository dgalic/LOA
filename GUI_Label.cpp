#include "GUI_Label.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>

namespace GUI{

  Label::Label(const std::string& s)
    :Component(){
    text.setString(s);
    text.setCharacterSize(30);
    text.setFont(FontManager::getInstance()->getLabelFont() );
  }

  void Label::setFont(const sf::Font& f){
    text.setFont(f);
  }

  void Label::setCharacterSize(const unsigned int& s){
    text.setCharacterSize(s);
  }

  void Label::setString(const std::string&){
    text.setString(s);
  }

  void Label::draw(sf::RenderTarget& t, sf::RenderStates s)const{
    s.transform *= getTransform();
    t.draw(text, s);
  }


}
