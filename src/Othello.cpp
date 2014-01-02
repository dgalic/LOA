#include "Othello.hpp"

#include "Game.hpp"
#include "ANSI.hpp"
#include "Console.hpp"
#include "Board.hpp"
#include "StateHandler.hpp"
#include "MainMenuState.hpp"

#include <sstream> // ostringstream
#include <utility> // pour std::pair

Othello::Othello(ANSI::Color c1,
		 ANSI::Color c2,
		 const unsigned short& t)
  : BoardGame(8, 8), player1(c1), player2(c2), currentPlayer(c1), typeIA(t){
  
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

  if(c == 'p' || c == MARK){
    /* optimisation : lister tous les coups possibles, et regarder si le coup
       est dedans. On doit tout calculer 1 fois, mais pas de doublons, et 
       surtout, possibilité de faire passer le joueur qui ne peut pas jouer */
    if( isNext(pointerX, pointerY, successors) ){
      board.at(pointerX, pointerY ) = currentPlayer;
      if( currentPlayer == player1){
	score[0] ++;
      }else{
	score[1] ++;
      }
      shuffle(pointerX, pointerY);      
      currentPlayer = (ANSI::Color) ((int)player1+(int)player2-(int)currentPlayer);
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
	    if( (ANSI::Color)p == player1){
	      score[0] += k-1;
	      score[1] -= k-1;
	    }else{
	      score[0] -= k-1;
	      score[1] += k-1;
	    }
	    std::cerr<<"shuffle "<<x+k2*i<<","<<y+k2*j<<"/"<<x<<","<<y <<std::endl;
	    while(x+(k2*i) != x || y+(k2*j) != y){		  
	      std::cerr<<"shuffle "<<x+k2*i<<","<<y+k2*j<<"/"<<x<<","<<y <<std::endl;

	      board.at(x+k2*i, y+k2*j) = p;

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
succ Othello::next(Board b,
		   const ANSI::Color& p) const{
  short k; //itérateur de "droite"
  succ res;
  for(unsigned short x = 0; x < b.getWidth(); x++){
    for(unsigned short y = 0; y < b.getHeight(); y++){
      if(b.get(x, y) != -1) //seule une case vide est jouable
	continue;
      for(short i = -1; i <= 1; i++){
	for(short j = -1; j <= 1; j++){
	  //	  std::cerr<<"Othello : "<<i<<","<<j<<" (itérateurs)"<<std::endl;
	  k = 1;
	  while(k < 9){ // normalement infini, mais c'est une sécurité en plus
	    if( (k*i+x) < 0 
		|| (k*i+x) >= (short)b.getWidth()
		|| (k*j+y) < 0 
		|| (k*j+y) >= (short)b.getHeight() 
		) // sortie du plateau en cherchant un pion allié
	      break;
	    short element = b.get(x+k*i, y+k*j);
	    if(element == -1) //case vide
	      break;
	    else if(element != p)
	      k++;
	    else if(element == p){
	      if(k > 1){ // la pièce amie a été rencontrée après des ennemies
		res.insert(std::make_pair(x, y) );
		std::cerr<<"Othello "<<k<<": ("<<x<<","<<y<<") est possible pour "<<player1<<std::endl;
		std::cerr<<"Othello "<<k<<": "<<successors.size()<<" coups possibles"<<std::endl;
		
		break;
	      }
	      else
		break; // la pièce amie est voisine de la "cible"
	    }
	    
	  }
	  
	} }

    } }
  return res;
}

bool Othello::isNext(const unsigned short& x, 
		     const unsigned short& y, 
		     const succ& s) const{
  std::pair<unsigned short, unsigned short> p = std::make_pair(x, y);
  for(auto it = s.begin(); it != s.end(); ++it){
    if( (*it) == p) 
      return true;
  }
  return false;
}


void Othello::update(){
  if(not ingame){
    //partie terminée 
    char c;
    std::cin>>c;
    StateHandler::getInstance()->change(new MainMenuState() );
  }else{
    BoardGame::update();
    successors = next(board, currentPlayer);
    ANSI::Color opponent = (ANSI::Color) ( (int)player1+(int)player2-(int)currentPlayer);
    if(successors.empty() ){
      //le joueur ne peut pas jouer si l'autre ne peut pas jouer, la partie finie
      if(next(board, opponent).empty() )
	// partie terminée
	ingame = false;
      else{
	// changement de joueurs
	currentPlayer = opponent;
      }
    }else{
      char c;
      std::cin>>c;
      handle(c);
    }
  }
}

void Othello::render(){
  BoardGame::render();
  Console::getInstance()->clear();
  Console::getInstance()->setForeground(ANSI::Color::WHITE);
  Console::getInstance()->setCursor(1, 1);
  Console::getInstance()->draw("OTHELLO  -  z:up  s:down  q:left  d:right  !/p:place  x:quit");
  Console::getInstance()->setForeground(ANSI::Color::GRAY);
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
  oss.str("Joueur 2 - ");
  oss << score[1];
  Console::getInstance()->drawString(25, 3, oss.str() );
  oss.clear();
  // indicateur du joueur courant
  Console::getInstance()->setForeground(ANSI::Color::WHITE);
  if(currentPlayer == player1){
    Console::getInstance()->draw(6, 5, '^');
  }else{
    Console::getInstance()->draw(30, 5, '^');
  }
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
