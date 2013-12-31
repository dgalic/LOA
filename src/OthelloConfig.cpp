#include "OthelloConfig.hpp"
#include "Othello.hpp"

#include "Game.hpp"
#include "ANSI.hpp"
#include "Console.hpp"
#include "StateHandler.hpp"
#include "MainMenuState.hpp"

OthelloConfig::~OthelloConfig(){

}

bool OthelloConfig::handle(const char& c){
  switch(c){
  case 'z':

    break;
    
  case 's':

    break;
    
  case 'p':
    switch(entry){
    case 2:
      StateHandler::getInstance()->change(new Othello() );
    default:
      break;
    }
    break;
  
  case 'x':
    StateHandler::getInstance()->change(new MainMenuState() );
    break;
    
  default:
    return false;
    break;
  }
  return true;
}

void OthelloConfig::update(){
  char c = Console::getInstance()->getInput();
  handle(c);
}

void OthelloConfig::render(){
  Console::getInstance()->clear();
  Console::getInstance()->setForeground(ANSI::Color::WHITE);
   Console::getInstance()->setCursor(1, 1);
  Console::getInstance()->draw("Othello  -  z:up  s:down  p:select  x:quit");
  Console::getInstance()->setForeground(ANSI::Color::BLUE);
  Console::getInstance()->drawRectangle(1, 2, Console::getInstance()->getWidth(), 1, '#');
  Console::getInstance()->setCursor(Console::getInstance()->getWidth(), 0);
}

bool OthelloConfig::init(){
  entry = 2;
  return true;
}

bool OthelloConfig::exit(){
  return true;
}
