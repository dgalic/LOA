#include "Game.hpp"

#include "GameStateHandler.hpp"
#include "GUI_Window.hpp"
#include "MainMenuState.hpp"
#include "ResourceManager.hpp"
#include "Singleton.hpp"

void Game::init(){
  GUI::Window::getInstance()->init();
  GameStateHandler::getInstance()->push(new MainMenuState() );
  running = true;
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
}

void Game::loop(){
  while(running && GUI::Window::getInstance()->getWindow()->isOpen() ){
    GameStateHandler::getInstance()->update();
    GameStateHandler::getInstance()->render();
  }
}

int main(){
  Game::getInstance()->init();
  Game::getInstance()->loop();
  Game::getInstance()->exit();
}
