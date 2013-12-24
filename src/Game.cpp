#include "Game.hpp"

#include <iostream>

#include "GameStateHandler.hpp"
#include "GUI_Window.hpp"
#include "MainMenuState.hpp"
#include "ResourceManager.hpp"
#include "Singleton.hpp"

void Game::init(){
  GUI::Window::getInstance()->init();
  GameStateHandler::getInstance()->push(new MainMenuState() );
  running = true;
  std::cerr<<"Game initialized"<<std::endl;
}

void Game::stop(){
  running = false;
}

void Game::resume(){
  running = true;
}

void Game::exit(){
  FontManager::getInstance()->destroy();
  GameStateHandler::getInstance()->clear();
  GameStateHandler::getInstance()->destroy();
  std::cerr<<"Game destroyed properly"<<std::endl;
}

void Game::loop(){
  std::cerr<<"Starting Game Loop"<<std::endl;
  while(running && GUI::Window::getInstance()->getWindow()->isOpen() ){
    std::cerr<<"One more loop"<<std::endl;
    GameStateHandler::getInstance()->update();
    GUI::Window::getInstance()->update();
    std::cerr<<"Updated"<<std::endl;
    GameStateHandler::getInstance()->render();
    GUI::Window::getInstance()->render();
    std::cerr<<"Rendered"<<std::endl;
  }
}

int main(){
  Game::getInstance()->init();
  Game::getInstance()->loop();
  Game::getInstance()->exit();
}
