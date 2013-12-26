#ifndef GUI_WINDOW_HPP
#define GUI_WINDOW_HPP

#include "Singleton.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <string>

namespace GUI{

  class Window : public Singleton<Window>{

    friend class Singleton<Window>;
  
  private:
    Window();
    ~Window();
    sf::RenderTexture * texture;
    sf::RenderWindow * window;
    unsigned int windowWidth;
    unsigned int windowHeight;
    const static std::string programName;
  
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
