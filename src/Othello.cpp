#include "Othello.hpp"

#include "Game.hpp"
#include "ANSI.hpp"
#include "Console.hpp"
#include "Board.hpp"
#include "StateHandler.hpp"
#include "MainMenuState.hpp"

#include <sstream> // ostringstream
#include <utility> // pour std::pair
#include <functional>

Othello::Othello(Player p1,
		 Player p2,
		 const unsigned short& t)
  : BoardGame(8, 8){
  mPlayer1 = p1;
  mPlayer2 = p2;
  currentPlayer = p1;
  mTypeIA = t;
  succ_function = [this](Board b, 
			 const unsigned short& x,
			 const unsigned short& y,
			 const Player& p) 
    -> bool{
    return isSucc(b, x, y, p);
  };

}
  
Othello::~Othello(){
    
}

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
      if( currentPlayer == mPlayer1){
	mScore[0] ++;
      }else{
	mScore[1] ++;
      }
      shuffle(pointerX, pointerY);      
      currentPlayer = (Player) ((int)mPlayer1+(int)mPlayer2-( (int)(currentPlayer)) );
    }
  }
}

void Othello::shuffle(const unsigned short& x,
		      const unsigned short& y){
  /**
   * @brief Retourne les pions retournables depuis une position.
   * @details A utiliser après un coup joué (donc supposé correct. On cherche 
   * dans les 8 directions si on peut manger des pions adverses à la case donnée
   * par la position.
   * @param x Abscisse du coup joué.
   * @param y Ordonnée du coup joué.
   */
  Player p = (Player)board.get(x, y);
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
	    if( (Player)p == mPlayer1){
	      mScore[0] += k-1;
	      mScore[1] -= k-1;
	    }else{
	      mScore[0] -= k-1;
	      mScore[1] += k-1;
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
	    
	     
      

bool Othello::isSucc(Board b,
		     const unsigned short& x,
		     const unsigned short& y,
		     const Player& p) const{
  /**
   * @brief Teste si le coup amène à une position successeur.
   * @details C'est la fonction de succession à passer à @e compute_next.
   * @param b Plateau où on teste la validité du coup.
   * @param x Abscisse du coup à tester.
   * @param y Ordonnée du coup à tester.
   * @param p Joueur supposé jouer le coup.
   **/
  if(b.get(x, y) != -1) //seule une case vide est jouable
    return false;
  unsigned short k;
  for(short i = -1; i <= 1; i++){
    for(short j = -1; j <= 1; j++){
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
	    return true;
	  }
	  else
	    break; // la pièce amie est voisine de la "cible"
	}
	
      }
      
    } }
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
    successors = BoardGame::computeNext(board, currentPlayer, succ_function);
    Player opponent = (Player) ( (int)mPlayer1+(int)mPlayer2-(int)( currentPlayer) );
    if(successors.empty() ){
      //le joueur ne peut pas jouer si l'autre ne peut pas jouer, la partie finie
      if(computeNext(board, opponent, succ_function).empty() )
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
  Console::getInstance()->setForeground(mPlayer1);
  std::ostringstream oss(std::ostringstream::ate);
  /* construire avec ::ate permet d'ajouter avec "<<" à la FIN du contenu défini
     par str(...). Autrement, ça écrit au début, écrasant les 1ers caractères */
  oss.str("Joueur 1 - ");
  oss << mScore[0];
  Console::getInstance()->drawString(1, 3, oss.str() );
  Console::getInstance()->setCursor(25, 3);
  Console::getInstance()->setForeground(mPlayer2);
  oss.str("Joueur 2 - ");
  oss << mScore[1];
  Console::getInstance()->drawString(25, 3, oss.str() );
  oss.clear();
  // indicateur du joueur courant
  Console::getInstance()->setForeground(ANSI::Color::WHITE);
  if(currentPlayer == mPlayer1){
    Console::getInstance()->draw(6, 5, '^');
  }else{
    Console::getInstance()->draw(30, 5, '^');
  }
  board.draw(12, 8);
  Console::getInstance()->setCursor(13+(pointerX*2), 9+pointerY);
}

bool Othello::init(){
  BoardGame::init();
  mScore[0] = 2;
  mScore[1] = 2;
  board.at(3,3) = mPlayer1;
  board.at(4,4) = mPlayer1;
  board.at(3,4) = mPlayer2;
  board.at(4,3) = mPlayer2;
  return true;
}

bool Othello::exit(){
  BoardGame::exit();
  return true;
}
