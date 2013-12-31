#include "Othello.hpp"

#include "Game.hpp"
#include "ANSI.hpp"
#include "Console.hpp"
#include "Board.hpp"
#include "StateHandler.hpp"
#include "MainMenuState.hpp"

#include <sstream>

Othello::Othello(ANSI::Color c1,
		 ANSI::Color c2)
  : BoardGame(8, 8), player1(c1), player2(c2){
  
}

Othello::~Othello(){

}

bool Othello::handle(const char& c){
  switch(c){
  case 'z':
    if(pointerY > 0)
      pointerY--;
    break;
    
  case 'q':
    if(pointerX > 0)
      pointerX--;
    break;
  
  case 's':
    if(pointerY < board.getHeight()-1 )
      pointerY++;
    break;
  
  case 'd':
    if(pointerX < board.getWidth()-1 )
      pointerX++;
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

void Othello::update(){
  BoardGame::update();
  char c;
  std::cin >> c;
  std::cerr<<"caractère "<<c<<" - "<<(int)c<<std::endl;
  if(c == ESC){
    std::cin >> c;
    if(c == '['){
      std::cerr<<"char2 "<<c<<std::endl;
      std::cin >> c;
      if(c =='A' )
	std::cerr<<"flèche haut!"<<std::endl;
      if(c =='B' )
	std::cerr<<"flèche bas!"<<std::endl;
      if(c =='C' )
	std::cerr<<"flèche droite!"<<std::endl;
      if(c =='D' )
	std::cerr<<"flèche gauche!"<<std::endl;
    }
  }
  handle(c);
}

void Othello::render(){
  BoardGame::render();
  Console::getInstance()->clear();
  Console::getInstance()->setForeground(ANSI::Color::WHITE);
  Console::getInstance()->setCursor(1, 1);
  Console::getInstance()->draw("OTHELLO  -  z:up  s:down  q:left  d:right  p:place  x:quit");
  Console::getInstance()->setForeground(ANSI::Color::WHITE);
  Console::getInstance()->drawRectangle(1, 2, Console::getInstance()->getWidth(), 1, '#');
  Console::getInstance()->drawRectangle(1, 4, Console::getInstance()->getWidth(), 1, '#');
  Console::getInstance()->setCursor(1, 3);
  Console::getInstance()->setForeground(player1);
  std::ostringstream oss(std::ostringstream::ate);
  /* construire avec ::ate permet d'ajouter avec "<<" à la FIN du contenu défini
   par str(...). Autrement, ça écrit au début, écrasant les 1ers caractères */
  oss.str("Joueur 1 - ");
  oss << score[0];
  Console::getInstance()->drawString(1, 3, oss.str() );
  Console::getInstance()->setCursor(25, 3);
  Console::getInstance()->setForeground(player2);
  oss.str("Joueur 2 -");
  oss << score[1];
  Console::getInstance()->drawString(25, 3, oss.str() );
  oss.clear();
  board.draw(12, 8);
  Console::getInstance()->setCursor(13+(pointerX*2), 9+pointerY);
}

bool Othello::init(){
  BoardGame::init();
  score[0] = 2;
  score[1] = 2;
  board.at(3,3) = player1;
  board.at(4,4) = player1;
  board.at(3,4) = player2;
  board.at(4,3) = player2;
  return true;
}

bool Othello::exit(){
  BoardGame::exit();
  return true;
}
