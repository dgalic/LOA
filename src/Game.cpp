#include "Game.hpp"

#include <iostream>

#include "GameStateHandler.hpp"
#include "Console.hpp"
#include "MainMenuState.hpp"
#include "ResourceManager.hpp"
#include "Singleton.hpp"

void Game::init(){
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
  stop();
  GameStateHandler::getInstance()->clear();
  GameStateHandler::getInstance()->destroy();
  Console::getInstance()->exit();
  std::cerr<<"Game destroyed properly"<<std::endl;
}

void Game::loop(){
  std::cerr<<"Starting Game Loop"<<std::endl;
  while(running){
    GameStateHandler::getInstance()->update();
    GameStateHandler::getInstance()->render();
  }
}

int main(){
  Game::getInstance()->init();
  Game::getInstance()->loop();
  Game::getInstance()->exit();
}
