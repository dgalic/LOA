#include "Game.hpp"

#include <iostream>

#include "StateHandler.hpp"
#include "Console.hpp"
#include "MainMenuState.hpp"
#include "ResourceManager.hpp"
#include "Singleton.hpp"

void Game::init(){
  StateHandler::getInstance()->push(new MainMenuState() );
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
  stop();
  StateHandler::getInstance()->clear();
  StateHandler::getInstance()->destroy();
  Console::getInstance()->exit();
  std::cerr<<"Game destroyed properly"<<std::endl;
}

void Game::loop(){
  std::cerr<<"Starting Game Loop"<<std::endl;
  while(running){
    StateHandler::getInstance()->update();
    StateHandler::getInstance()->render();
  }
}

int main(){
  char c = 27;
  std::cerr << "test 27 "<<c<<"-"<<(int)ESC<<std::endl;
  Game::getInstance()->init();
  Game::getInstance()->loop();
  Game::getInstance()->exit();
}
