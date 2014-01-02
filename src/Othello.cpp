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
  : BoardGame(8, 8), player1(c1), player2(c2), currentPlayer(c1){
  
}

Othello::~Othello(){

}

/**
   controles : 
   -flèches/ zqsd : bouger
   -p : placer pion
   -x : retour au menu principal
*/
void Othello::handle(const char& c){
  ANSI::Arrow arr;
  arr = checkArrow(c);
  if(arr == ANSI::UP 
     || c == 'z'){
    if(pointerY > 0)
      pointerY--;
    return;
  }
    
  if(arr == ANSI::LEFT 
     || c == 'q'){
    if(pointerX > 0)
      pointerX--;
    return;
  }

  if(arr == ANSI::DOWN 
     || c == 's'){
    if(pointerY < board.getHeight()-1 )
      pointerY++;
    return;
  }

  if(arr == ANSI::RIGHT 
     || c == 'd'){
    if(pointerX < board.getWidth()-1 )
      pointerX++;
    return;
  }
  
  if(c == 'x'){
    StateHandler::getInstance()->change(new MainMenuState() );
    return;
  }

  if(c == 'p'){
    /* optimisation : lister tous les coups possibles, et regarder si le coup
       est dedans. On doit tout calculer 1 fois, mais pas de doublons, et 
       surtout, possibilité de faire passer le joueur qui ne peut pas jouer */
    if( next(pointerX, pointerY, currentPlayer) > 0){
      board.at(pointerX, pointerY ) = currentPlayer;
      shuffle(pointerX, pointerY);
    }
  }
}

/** 
    retourne les pions qui devraient l'être, lors d'un coup supposé correct.
*/
void Othello::shuffle(const unsigned short& x,
		      const unsigned short& y){
  ANSI::Color p = (ANSI::Color) board.get(x, y);
  unsigned short right = board.getWidth(), bottom = board.getHeight();
  for(short i = -1; i <= 1 ; i++){
    for(short j = -1; j <= 1; j++){
      short k = 1;
      while( k < 49){ // normalement infini, mais on se fait une sécurité
	if( (k*i+x) < 0 
	    || (k*i+x) >= (short)right 
	    || (k*j+y) < 0 
			 || (k*j+y) >= (short)bottom 
	      )
	  break;
	    short element = board.get(x+k*i, y+k*j);
	    std::cerr<<"element => "<<element<<std::endl;
	    if(element == -1) //case vide
	      break;
	    if(element != p)
	      k++;
	    if(element == p){
	      if(k > 1){ // la pièce amie a été rencontrée après des ennemies
		short k2 = k;
		std::cerr<<"shuffle "<<x+k2*i<<","<<y+k2*j<<"/"<<x<<","<<y <<std::endl;
		while(x+(k2*i) != x || y+(k2*j) != y){		  
		std::cerr<<"shuffle "<<x+k2*i<<","<<y+k2*j<<"/"<<x<<","<<y <<std::endl;

		  board.at(x+k2*i, y+k2*j) = p;
		  if( (ANSI::Color)p == player1){
		    score[0]++;
		    score[1]--;
		  }else{
		    score[0]--;
		    score[1]++;
		  }
		k2--;
		}
		break;
	      }
	      else
		break; // la pièce amie est voisine de la "cible"
	    }
	    
	    }
      }
    }
  }
	    
	    
      

/** un coup est possible si il prend en sandwich au moins 1 pion adverse : 
    depuis la position courante, on va chercher des pions adverses dans le 8
    directions, jusqu'à ce que : 
    -on tombe sur du vide -> échec 
    -on tombe sur le bord -> échec
    -on trouve un pion ami -> possible
*/
short Othello::next(const unsigned short& x, 
		    const unsigned short& y, 
		    const ANSI::Color& p) const{
  std::cerr << "est-ce que "<<x<<","<<y<<" est un coup possible pour"<<p<<"?"<<std::endl;
  if(board.get(x, y) != -1)
    return 0;
  short k = 1;
  unsigned short right = board.getWidth(), bottom = board.getHeight();
  for(short i = -1; i <= 1 ; i++){
    for(short j = -1; j <= 1; j++){
      k = 1;
      while( k < 49){ // normalement infini, mais on se fait une sécurité
	std::cerr << "case "<<k*i+x<<","<<k*j+y<<" (accu : "<<k<<")"<<std::endl;
	if( (k*i+x) < 0 
	    || (k*i+x) >= (short)right 
	    || (k*j+y) < 0 
			 || (k*j+y) >= (short)bottom 
	      )
	  break;
	    short element = board.get(x+k*i, y+k*j);
	    std::cerr<<"element => "<<element<<std::endl;
	    if(element == -1) //case vide
	      break;
	    if(element != p)
	      k++;
	    if(element == p){
	      if(k > 1) // la pièce amie a été rencontrée après des ennemies
		return k-1;
	      else
		break; // la pièce amie est voisine de la "cible"
	    }
	    }
      }
    }
    return 0;
  }

  void Othello::update(){
    BoardGame::update();
    char c;
    std::cin>>c;
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
