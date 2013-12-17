
#include "GUI_Window.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace GUI{
  Window::Window(){
    m_windowWidth = 800;
    m_windowHeight = 600;
    m_render = new sf::RenderTexture();
    m_window = new sf::RenderWindow();

  }

  Window::~Window(){
    exit();
  }

  bool Window::init(){
    m_window->create(sf::VideoMode(m_windowWidth, m_windowHeight),
		     m_programName,
		     sf::Style::Close|sf::Style::Titlebar
		     );
    m_texture->create(m_window->getSize().x, m_window->getSize().y);
  }


  bool Window::exit(){
    m_window->close();
    delete m_texture;
    delete m_window;
  }

}
