#include "FiveOrMore.hpp"
#include "FiveOrMore_var.hpp"
#include "FiveOrMoreConfig.hpp"

#include "Game.hpp"
#include "ANSI.hpp"
#include "Color.hpp"
#include "Console.hpp"
#include "StateHandler.hpp"
#include "MainMenuState.hpp"

#include <list>
#include <sstream>

FiveOrMoreConfig::FiveOrMoreConfig()
  :mEntry(0), mSize(10), mPiece(3),mColor(5), mJeux(0){
}

FiveOrMoreConfig::~FiveOrMoreConfig(){}

void FiveOrMoreConfig::handle(const char& c){
  ANSI::Arrow arr = checkArrow(c);
  
  if(c == 'z' || arr == ANSI::UP){
    mEntry = (mEntry == 0)? 3:mEntry-1;
    return;
  }
  
  if(c == 'q' || arr == ANSI::LEFT){
    if(mEntry == 0){
      mSize = (mSize == 8)? 15:mSize-1;
    } else if(mEntry == 1){
      mPiece = (mPiece == 3)? 6:mPiece-1;
    } else if(mEntry == 2){
      mColor = (mColor == 2)? 10:mColor-1;
    } else if(mEntry == 3){
      mJeux = (mJeux == 1)? 0:1;
    } 
    return;
  }
  
  if(c == 's' || arr == ANSI::DOWN){
    mEntry = (mEntry == 3)? 0 : mEntry+1;
    return;
  }

  if(c == 'd' || arr == ANSI::RIGHT){
    if(mEntry == 0){
      mSize = (mSize == 15)? 8:mSize+1;
    } else if(mEntry == 1){
      mPiece = (mPiece == 6)? 3:mPiece+1;
    } else if(mEntry == 2){
      mColor = (mColor == 10)? 2:mColor+1;
    } else if(mEntry == 3){
      mJeux = (mJeux == 1)? 0:1;
    }
    return;
  }

  if(c == 'p' || c == MARK){
      if (mJeux == 0) {
        Game::getInstance()->getHandler().change(new FiveOrMore(mSize,mColor,mPiece) );
      } else if (mJeux == 1) {
        Game::getInstance()->getHandler().change(new FiveOrMore_var(mSize,mColor,mPiece) );
      }
    return;
  }
  
  if(c == 'x'){
    Game::getInstance()->mainMenu();;
    return;
  }


}

void FiveOrMoreConfig::update(){
  char c = Console::getInstance()->getInput();
  handle(c);
}

void FiveOrMoreConfig::render(){
  Console::getInstance()->clear();
  Console::getInstance()->setForeground(Color::WHITE);
  Console::getInstance()->setCursor(1, 1);
  Console::getInstance()->draw("FiveOrMore  -  z:up  s:down  !/p:select  x:quit");
  Console::getInstance()->setForeground(Color::GRAY);
  Console::getInstance()->drawRectangle(1, 2, Console::getInstance()->getWidth(), 1, '#');
  Console::getInstance()->setForeground(Color::WHITE);
    std::ostringstream oss(std::ostringstream::ate);
    oss.str("Taille : ");
    oss << mSize;
    Console::getInstance()->draw(4, 4, oss.str() );
    oss.clear();
    oss.str("Nombre de piece :");
    oss << mPiece;
    Console::getInstance()->draw(4, 5, oss.str() );
    oss.clear();
    oss.str("Nombre de Couleur :");
    oss << mColor;
    Console::getInstance()->draw(4, 6, oss.str() );
    oss.clear();
    oss.str("Jeu choisi :");
    if (mJeux == 0) {
        oss << "Deplacement piece";
    } else if (mJeux == 1) {
        oss << "Changement de couleur";
    }
    Console::getInstance()->draw(4, 7, oss.str() );
    oss.clear();
  Console::getInstance()->draw(2, 4+mEntry, '~');
  
  Console::getInstance()->setCursor(Console::getInstance()->getWidth(), 0);
}
