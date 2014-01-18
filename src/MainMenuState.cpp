#include "MainMenuState.hpp"
#include "Singleton.hpp"

#include <iostream>

#include "Game.hpp"
#include "State.hpp"
#include "StateHandler.hpp"
#include "Console.hpp"
#include "ANSI.hpp"
#include "OthelloConfig.hpp"

MainMenuState::MainMenuState(){
  mEntry = 0;
  mNbGames = 3;
  mGameDescs.push_back("Dans Othello, vous devez prendre en sandwich plusieurs \
pions ennemis pour les retourner. Le gagnant est celui qui possède le plus de \
pions de sa couleur à la fin de la partie.");
  mGameDescs.push_back("Dans Puissance 4, vous devez faire une ligne de 4 pions de même couleur.");
  mGameDescs.push_back("Dans 5 or more, il faut faire des lignes de 5 pions de même couleurs ou plus. Chaque pion vous rapporte des points avant de disparaitre. Faites vite avant que le plateau ne soit rempli !!");
 
}

MainMenuState::~MainMenuState(){

}

void MainMenuState::handle(const char& c){
  ANSI::Arrow arr;
  arr = checkArrow(c);
  if( arr == ANSI::UP
      || c == 'z'){
    mEntry = (mEntry == 0)? mNbGames-1:mEntry-1;
    return;
  }

  if( arr == ANSI::DOWN 
      || c == 's'){
    mEntry = (mEntry+1)%mNbGames;
    return;
  }

  if( c == 'x'){
    Game::getInstance()->stop();
    Game::getInstance()->exit();
    return;
  }

  if(c == 'p' || c == MARK){
    switch(mEntry){
    case 0:
      Game::getInstance()->getHandler().change(new OthelloConfig() );
      break;
      
    default:
      break;
    }
  }

}

void MainMenuState::update(){
  char c = Console::getInstance()->getInput();
  handle(c);
}

void MainMenuState::render(){
  Console::getInstance()->clear();
  Console::getInstance()->setForeground(ANSI::Color::WHITE);
  Console::getInstance()->setCursor(1, 1);
  Console::getInstance()->draw("MAIN MENU  -  z:up  s:down  x:quit  !/p:ok");
  Console::getInstance()->setForeground(ANSI::Color::GRAY);
  Console::getInstance()->drawRectangle(1, 2, Console::getInstance()->getWidth(), 1, '#');  
  Console::getInstance()->drawRectangle(1, 12, Console::getInstance()->getWidth(), 1, '#');
  Console::getInstance()->setForeground(ANSI::Color::WHITE);
  Console::getInstance()->draw(4, 4, "Othello");
  Console::getInstance()->draw(4, 5, "Puissance 4");
  Console::getInstance()->draw(4, 6, "5 or more");
  Console::getInstance()->setCursor(1, 14);
  Console::getInstance()->setForeground(ANSI::Color::WHITE);
  Console::getInstance()->drawString(mGameDescs.at(mEntry) );
  Console::getInstance()->draw(2, 4+mEntry, '~');
  Console::getInstance()->setCursor(Console::getInstance()->getWidth(), 0);
}


