#include "OthelloConfig.hpp"
#include "Othello.hpp"

#include "Game.hpp"
#include "ANSI.hpp"
#include "Console.hpp"
#include "StateHandler.hpp"
#include "MainMenuState.hpp"

#include <list>
#include <sstream>

OthelloConfig::OthelloConfig()
  :entry(0), type2(0){
}

OthelloConfig::~OthelloConfig(){

}

void OthelloConfig::handle(const char& c){
  ANSI::Arrow arr = checkArrow(c);
  if(c == 'z' || arr == ANSI::UP){
    entry = (entry == 0)? entry = 2:entry-1;
    return;
  }
  if(c == 'q' || arr == ANSI::LEFT){
    if(entry == 0){
      if( color1 == possible_colors.begin() ){
	color1 = (possible_colors.end() );
      }
      color1--;
      if(*color1 == *color2){
	color1--;
      }
      return;
    }
    if(entry == 1){
      if( color2 == possible_colors.begin() ){
	color2 = (possible_colors.end() );
      }
      color2--;      
      if(*color2 == *color1){
	color2--;
      }
      return;
    }
    if(entry == 2){
      type2 = (type2 == 0)? 5:type2-1;
    }
    return;
  }
  if(c == 's' || arr == ANSI::DOWN){
    entry = (entry >= 2)? 0 : entry+1;
    return;
  }
  if(c == 'd' || arr == ANSI::RIGHT){
    if(entry == 0){
      color1++;
      if(*color2 == *color1){
	color1++;
      }
      if( color1 == possible_colors.end() ){
	color1 = (possible_colors.begin() )++;
      }
      return;
    }
    if(entry == 1){
      color2++;
      if(*color2 == *color1){
	color2++;
      }
      if( color2 == possible_colors.end() ){
	color2 = (possible_colors.begin() )++;
      }
      return;
    }
    if(entry == 2){
      type2 = (type2 == 5)? 0:type2+1;
    }
    return;
  }

  if(c == 'p' || c == MARK){
    if(color1 != color2){
      StateHandler::getInstance()->change(new Othello(*color1, *color2, type2) );
    }else{
      Console::getInstance()->setForeground(ANSI::WHITE);
      Console::getInstance()->draw(1, 20, "Les deux joueurs ne peuvent pas avoir la même couleur ! ");
      Console::getInstance()->setCursor(Console::getInstance()->getWidth(), 0);
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
  Console::getInstance()->setForeground(ANSI::Color::GRAY);
  Console::getInstance()->drawRectangle(1, 2, Console::getInstance()->getWidth(), 1, '#');
  Console::getInstance()->setForeground(*color1);
  Console::getInstance()->draw(4, 4, "Couleur joueur 1");
  Console::getInstance()->setForeground(*color2);
  Console::getInstance()->draw(4, 5, "Couleur joueur 2");
  Console::getInstance()->setForeground(ANSI::Color::WHITE);
  Console::getInstance()->draw(4, 6, "Type adversaire : "); 
  if(type2 == 0){
    Console::getInstance()->draw(30, 6, "Humain");
  }else{
    std::ostringstream oss(std::ostringstream::ate);
    oss.str("IA niveau ");
    oss << type2;
    Console::getInstance()->draw(30, 6, oss.str() );
    oss.clear();
  }
  Console::getInstance()->draw(2, 4+entry, '~');
  
  Console::getInstance()->setCursor(Console::getInstance()->getWidth(), 0);
}

bool OthelloConfig::init(){
  possible_colors.push_front(ANSI::BROWN);
  possible_colors.push_front(ANSI::YELLOW);
  possible_colors.push_front(ANSI::GREEN);
  possible_colors.push_front(ANSI::LIGHTCYAN);
  possible_colors.push_front(ANSI::BLUE);
  possible_colors.push_front(ANSI::PURPLE);
  possible_colors.push_front(ANSI::PINK);
  possible_colors.push_front(ANSI::RED);
  color1 = (possible_colors.begin() )++;
  color2 = color1;
  color2++;
  return true;
}

bool OthelloConfig::exit(){
  return true;
}
