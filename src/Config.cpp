#include "Config.hpp"

#include "Console.hpp"
#include "Game.hpp"

#include <sstream>

//TODO delete
#include <iostream>

Config::Config(const unsigned short& nb)
  : State(), mEntry(0), mNbEntries(nb), mWidth(8), mHeight(8)
{
  mPossibleColors.push_front(Color::YELLOW);
  mPossibleColors.push_front(Color::BROWN);
  mPossibleColors.push_front(Color::BLUE);
  mPossibleColors.push_front(Color::PURPLE);
  mPossibleColors.push_front(Color::GREEN);
  mPossibleColors.push_front(Color::RED);
  mPossibleColors.push_front(Color::PINK);
  mPossibleColors.push_front(Color::LIGHTCYAN);
  mColor1 = (mPossibleColors.begin() )++;
  mColor2 = mColor1;
  mColor2++;

}

Config::~Config(){

}

void Config::handle(const char & c){
  ANSI::Arrow arr = checkArrow(c);
    if(c == 'z' || arr == ANSI::UP){
    mEntry = (mEntry == 0)? mNbEntries-1:mEntry-1;
    return;
  }
  
  if(c == 's' || arr == ANSI::DOWN){
    mEntry = (mEntry >= mNbEntries-1)? 0 : mEntry+1;
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
      mWidth = (mWidth == 4)? 16:mWidth-1;
      return;
    }
    if(mEntry == 3){
      mHeight = (mHeight == 4)? 15:mHeight-1;
    }
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
      mWidth = (mWidth == 16)? 4:mWidth+1;
      return;
    }
    if(mEntry == 3){
      mHeight = (mHeight == 15)? 4:mHeight+1;
    }
    return;
  }
    
  if(c == 'x'){
    Game::getInstance()->mainMenu();
    return;
  }

}



void Config::update(){
  char c = Console::getInstance()->getInput();
  handle(c);
}

void Config::render(){
  Console::getInstance()->clear();
  Console::getInstance()->setForeground(Color::GRAY);
  Console::getInstance()->drawRectangle(1, 2, Console::getInstance()->getWidth(), 1, '#');
  Console::getInstance()->setForeground(*mColor1);
  Console::getInstance()->draw(4, 4, "Couleur joueur 1");
  Console::getInstance()->setForeground(*mColor2);
  Console::getInstance()->draw(4, 5, "Couleur joueur 2");
  Console::getInstance()->setForeground(Color::WHITE);
  std::ostringstream oss(std::ostringstream::ate);
  oss.str("Longueur du plateau : ");
  oss << mWidth;
  Console::getInstance()->draw(4, 6, oss.str() );
  oss.clear();
  oss.str("Largeur du plateau  : ");
  oss << mHeight;
  Console::getInstance()->draw(4, 7, oss.str() );
  oss.clear();
  Console::getInstance()->draw(2, 4+mEntry, '~');


  Console::getInstance()->setForeground(Color::WHITE);
  Console::getInstance()->setCursor(Console::getInstance()->getWidth(), 0);


}
