#ifndef GUI_WINDOW_HPP
#define GUI_WINDOW_HPP

#include "Singleton.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


namespace GUI{

  class Window : public Singleton<Window>{

    friend class Singleton<Window>;
  
  private:
    Window();
    ~Window();
    sf::RenderTexture * m_render;
    sf::RenderWindow * m_window;
    unsigned int m_windowWidth;
    unsigned int m_windowHeight;
    static const std::string m_programName = "";
  
  public:
    sf::RenderWindow * getWindow() const;
    sf::RenderTexture * getTexture() const;
    bool init();
    bool exit();
    void update();
    void render();
  };

}



#endif
