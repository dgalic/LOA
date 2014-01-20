#include "MainMenuState.hpp"
#include "Singleton.hpp"

#include <iostream>

#include "Game.hpp"
#include "State.hpp"
#include "StateHandler.hpp"
#include "Console.hpp"
#include "ANSI.hpp"
#include "OthelloConfig.hpp"
#include "FiveOrMore.hpp"
#include "FiveOrMore_var.hpp"
#include "Connect4.hpp"
#include "Connect4_long.hpp"
#include "Tic_tac_toe.hpp"
#include "Isola.hpp"
#include "Chomp.hpp"

MainMenuState::MainMenuState(){
  mEntry = 0;
  mGameDescs.push_back("Dans Othello, vous devez prendre en sandwich plusieurs \
pions ennemis pour les retourner. Le gagnant est celui qui possède le plus de \
pions de sa couleur à la fin de la partie.");
  mGameDescs.push_back("Dans Puissance 4, vous devez faire une ligne de 4 pions de même couleur.");
  mGameDescs.push_back("Dans Puissance 4, vous devez faire une ligne de 4 pions de même couleur. Chaque ligne vous rapporte 1 point et disparait ensuite.");
  mGameDescs.push_back("Dans 5 or more, il faut faire des lignes de 5 pions de même couleurs ou plus, en déplaçant un pion. Chaque pion vous rapporte des points avant de disparaitre. Faites vite avant que le plateau ne soit rempli !!");
  mGameDescs.push_back("Dans cette variante de Five or more, vous ne déplacez pas les pions, vous changez leur couleur.");
  mGameDescs.push_back("Dans Morpion, il faut aligner 3 pion de la même couleur");  
  mGameDescs.push_back("Dans Isola, il faut empêcher l'ennemi de bouger en detruisant des cases. Un pion peut bouger dans les 8 directions. ");
  mGameDescs.push_back("Dans Chomp, celui qui remplie tout le plateaux à perdue");  
  mNbGames = mGameDescs.size();
 
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
     
    case 1:
      Game::getInstance()->getHandler().change(new Connect4(Color::RED, Color::YELLOW) );
      break;

    case 2:
      Game::getInstance()->getHandler().change(new Connect4_long(Color::RED, Color::YELLOW, 6) );
      break;

    case 3:
      Game::getInstance()->getHandler().change(new FiveOrMore(10) );
      break;
      
    case 4:
      Game::getInstance()->getHandler().change(new FiveOrMore_var(10) );
      break;

    case 5:
      Game::getInstance()->getHandler().change(new Tic_tac_toe(Color::RED, Color::BLUE) );
      break;

    case 6:
      Game::getInstance()->getHandler().change(new Isola(Color::RED, Color::BLUE, 7, 6) );
      break;

    case 7:
      Game::getInstance()->getHandler().change(new Chomp() );
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
  Console::getInstance()->setForeground(Color::WHITE);
  Console::getInstance()->setCursor(1, 1);
  Console::getInstance()->draw("MAIN MENU  -  z:up  s:down  x:quit  !/p:ok");
  Console::getInstance()->setForeground(Color::GRAY);
  Console::getInstance()->drawRectangle(1, 2, Console::getInstance()->getWidth(), 1, '#');  
  Console::getInstance()->drawRectangle(1, 16, Console::getInstance()->getWidth(), 1, '#');
  Console::getInstance()->setForeground(Color::WHITE);
  Console::getInstance()->draw(4, 4, "Othello");
  Console::getInstance()->draw(4, 5, "Puissance 4");
  Console::getInstance()->draw(4, 6, "Puissance 4 - variante à points");
  Console::getInstance()->draw(4, 7, "5 or more");
  Console::getInstance()->draw(4, 8, "5 or more - variante couleurs");
  Console::getInstance()->draw(4, 9, "Morpion");
  Console::getInstance()->draw(4, 10, "Isola");
  Console::getInstance()->draw(4, 11, "Chomp");
  Console::getInstance()->setCursor(1, 14);
  Console::getInstance()->setForeground(Color::WHITE);
  Console::getInstance()->drawString(2, 18, mGameDescs.at(mEntry) );
  Console::getInstance()->draw(2, 4+mEntry, '~');
  Console::getInstance()->setCursor(Console::getInstance()->getWidth(), 0);
}


