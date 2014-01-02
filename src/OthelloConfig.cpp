#include "OthelloConfig.hpp"
#include "Othello.hpp"

#include "Game.hpp"
#include "ANSI.hpp"
#include "Console.hpp"
#include "StateHandler.hpp"
#include "MainMenuState.hpp"

OthelloConfig::~OthelloConfig(){

}

void OthelloConfig::handle(const char& c){
  ANSI::Arrow arr = checkArrow(c);
  if(c == 'z' || arr == ANSI::UP){
    return;
  }
  if(c == 'q' || arr == ANSI::LEFT){
    return;
  }
  if(c == 's' || arr == ANSI::DOWN){
    return;
  }
  if(c == 'd' || arr == ANSI::RIGHT){
    return;
  }

  if(c == 'p' || c == MARK){
    switch(entry){
    case 2:
      StateHandler::getInstance()->change(new Othello() );
    default:
      break;
    }
    return;
  }
  
  if(c == 'x'){
    StateHandler::getInstance()->change(new MainMenuState() );
    return;
  }


}

void OthelloConfig::update(){
  char c = Console::getInstance()->getInput();
  handle(c);
}

void OthelloConfig::render(){
  Console::getInstance()->clear();
  Console::getInstance()->setForeground(ANSI::Color::WHITE);
   Console::getInstance()->setCursor(1, 1);
  Console::getInstance()->draw("Othello  -  z:up  s:down  !/p:select  x:quit");
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
