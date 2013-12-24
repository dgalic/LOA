
#include "GUI_Window.hpp"
#include "Color.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Game.hpp"
#include "Event.hpp"

namespace GUI{

  const std::string Window::programName = "App";

  Window::Window(){
    windowWidth = 800;
    windowHeight = 600;
    texture = new sf::RenderTexture();
    window = new sf::RenderWindow();

  }

  Window::~Window(){
    exit();
  }

  bool Window::init(){
    window->create(sf::VideoMode(windowWidth, windowHeight),
		   Window::programName,
		   sf::Style::Close|sf::Style::Titlebar
		   );
    //texture->create(window->getSize().x, window->getSize().y);
    texture->create(windowWidth, windowHeight);
    texture->setSmooth(false);
    return true;
  }


  bool Window::exit(){
    window->close();
    delete texture;
    delete window;
    return true;
  }

  sf::RenderWindow * Window::getWindow() const{
    return window;
  }

  sf::RenderTexture * Window::getTexture() const{
    return texture;
  }

  void Window::update(){
    
  }
  
  void Window::render(){
    window->clear(Color(128,128,128) );
    texture->display();
    window->draw(sf::Sprite(texture->getTexture()) );
    window->display();
  }

}
