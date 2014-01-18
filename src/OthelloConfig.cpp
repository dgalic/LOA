#include "OthelloConfig.hpp"
#include "Othello.hpp"

#include "Game.hpp"
#include "ANSI.hpp"
#include "Color.hpp"
#include "Console.hpp"
#include "StateHandler.hpp"
#include "MainMenuState.hpp"

#include <list>
#include <sstream>

OthelloConfig::OthelloConfig()
  :mEntry(0), mType2(0){
  mPossibleColors.push_front(Color::BROWN);
  mPossibleColors.push_front(Color::YELLOW);
  mPossibleColors.push_front(Color::GREEN);
  mPossibleColors.push_front(Color::LIGHTCYAN);
  mPossibleColors.push_front(Color::BLUE);
  mPossibleColors.push_front(Color::PURPLE);
  mPossibleColors.push_front(Color::PINK);
  mPossibleColors.push_front(Color::RED);
  mColor1 = (mPossibleColors.begin() )++;
  mColor2 = mColor1;
  mColor2++;
}

OthelloConfig::~OthelloConfig(){

}

void OthelloConfig::handle(const char& c){
  ANSI::Arrow arr = checkArrow(c);
  if(c == 'z' || arr == ANSI::UP){
    mEntry = (mEntry == 0)? mEntry = 2:mEntry-1;
    return;
  }
  if(c == 'q' || arr == ANSI::LEFT){
    if(mEntry == 0){
      if( mColor1 == mPossibleColors.begin() ){
	mColor1 = (mPossibleColors.end() );
      }
      mColor1--;
      if(*mColor1 == *mColor2){
	mColor1--;
      }
      return;
    }
    if(mEntry == 1){
      if( mColor2 == mPossibleColors.begin() ){
	mColor2 = (mPossibleColors.end() );
      }
      mColor2--;      
      if(*mColor2 == *mColor1){
	mColor2--;
      }
      return;
    }
    if(mEntry == 2){
      mType2 = (mType2 == 0)? 5:mType2-1;
    }
    return;
  }
  if(c == 's' || arr == ANSI::DOWN){
    mEntry = (mEntry >= 2)? 0 : mEntry+1;
    return;
  }
  if(c == 'd' || arr == ANSI::RIGHT){
    if(mEntry == 0){
      mColor1++;
      if(*mColor2 == *mColor1){
	mColor1++;
      }
      if( mColor1 == mPossibleColors.end() ){
	mColor1 = (mPossibleColors.begin() )++;
      }
      return;
    }
    if(mEntry == 1){
      mColor2++;
      if(*mColor2 == *mColor1){
	mColor2++;
      }
      if( mColor2 == mPossibleColors.end() ){
	mColor2 = (mPossibleColors.begin() )++;
      }
      return;
    }
    if(mEntry == 2){
      mType2 = (mType2 == 5)? 0:mType2+1;
    }
    return;
  }

  if(c == 'p' || c == MARK){
    if(mColor1 != mColor2){
      Game::getInstance()->getHandler().change(new Othello(*mColor1, *mColor2) );
    }else{
      Console::getInstance()->setForeground(Color::WHITE);
      Console::getInstance()->draw(1, 20, "Les deux joueurs ne peuvent pas avoir la même couleur ! ");
      Console::getInstance()->setCursor(Console::getInstance()->getWidth(), 0);
    }
    return;
  }
  
  if(c == 'x'){
    Game::getInstance()->getHandler().change(new MainMenuState() );
    return;
  }


}

void OthelloConfig::update(){
  char c = Console::getInstance()->getInput();
  handle(c);
}

void OthelloConfig::render(){
  Console::getInstance()->clear();
  Console::getInstance()->setForeground(Color::WHITE);
  Console::getInstance()->setCursor(1, 1);
  Console::getInstance()->draw("Othello  -  z:up  s:down  !/p:select  x:quit");
  Console::getInstance()->setForeground(Color::GRAY);
  Console::getInstance()->drawRectangle(1, 2, Console::getInstance()->getWidth(), 1, '#');
  Console::getInstance()->setForeground(*mColor1);
  Console::getInstance()->draw(4, 4, "Couleur joueur 1");
  Console::getInstance()->setForeground(*mColor2);
  Console::getInstance()->draw(4, 5, "Couleur joueur 2");
  Console::getInstance()->setForeground(Color::WHITE);
  Console::getInstance()->draw(4, 6, "Type adversaire : "); 
  if(mType2 == 0){
    Console::getInstance()->draw(30, 6, "Humain");
  }else{
    std::ostringstream oss(std::ostringstream::ate);
    oss.str("IA niveau ");
    oss << mType2;
    Console::getInstance()->draw(30, 6, oss.str() );
    oss.clear();
  }
  Console::getInstance()->draw(2, 4+mEntry, '~');
  
  Console::getInstance()->setCursor(Console::getInstance()->getWidth(), 0);
}
