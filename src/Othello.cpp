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

Othello::Othello(const Color& p1,
		 const Color& p2)
  : BoardGame(8, 8), mPlayer1(p1), mPlayer2(p2) {
  mPlayer1 = p1;
  mPlayer2 = p2;
  mCurrentPlayer = &mPlayer1;
  succ_function = [this](Board b, 
			 const unsigned short& x,
			 const unsigned short& y,
			 const Player& p) 
    -> bool{
    return isSucc(b, x, y, p);
  };
  mScore[0] = 2;
  mScore[1] = 2;
  mBoard.at(3,3) = mPlayer1.getColor();
  mBoard.at(4,4) = mPlayer1.getColor();
  mBoard.at(3,4) = mPlayer2.getColor();
  mBoard.at(4,3) = mPlayer2.getColor();
}
  
Othello::~Othello(){
    
}

void Othello::handle(const char& c){

  ANSI::Arrow arr;
  arr = checkArrow(c);
  if(arr == ANSI::UP 
     || c == 'z'){
    if(mPointerY > 0)
      mPointerY--;
    return;
  }
    
  if(arr == ANSI::LEFT 
     || c == 'q'){
    if(mPointerX > 0)
      mPointerX--;
    return;
  }

  if(arr == ANSI::DOWN 
     || c == 's'){
    if(mPointerY < mBoard.getHeight()-1 )
      mPointerY++;
    return;
  }

  if(arr == ANSI::RIGHT 
     || c == 'd'){
    if(mPointerX < mBoard.getWidth()-1 )
      mPointerX++;
    return;
  }
  
  if(c == 'x'){
    Game::getInstance()->getHandler().change(new MainMenuState() );
    return;
  }

  if(c == 'p' || c == MARK){
    /* optimisation : lister tous les coups possibles, et regarder si le coup
       est dedans. On doit tout calculer 1 fois, mais pas de doublons, et 
       surtout, possibilité de faire passer le joueur qui ne peut pas jouer */
    if( isNext(mPointerX, mPointerY, successors) ){
      mBoard.at(mPointerX, mPointerY ) = mCurrentPlayer->getColor();
      if( mCurrentPlayer == &mPlayer1){
	mScore[0] ++;
      }else{
	mScore[1] ++;
      }
      shuffle(mPointerX, mPointerY);      
      mCurrentPlayer = opponent();
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
  Color pcolor = (Color)mBoard.get(x, y);
  unsigned short right = mBoard.getWidth(), bottom = mBoard.getHeight();
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
	short element = mBoard.get(x+k*i, y+k*j);
	std::cerr<<"element => "<<element<<std::endl;
	if(element == -1) //case vide
	  break;
	if(element != pcolor )
	  k++;
	if(element == pcolor ){
	  if(k > 1){ // la pièce amie a été rencontrée après des ennemies
	    short k2 = k;
	    if( pcolor == mPlayer1.getColor() ){
	      mScore[0] += k-1;
	      mScore[1] -= k-1;
	    }else{
	      mScore[0] -= k-1;
	      mScore[1] += k-1;
	    }
	    std::cerr<<"shuffle "<<x+k2*i<<","<<y+k2*j<<"/"<<x<<","<<y <<std::endl;
	    while(x+(k2*i) != x || y+(k2*j) != y){		  
	      std::cerr<<"shuffle "<<x+k2*i<<","<<y+k2*j<<"/"<<x<<","<<y <<std::endl;

	      mBoard.at(x+k2*i, y+k2*j) = pcolor ;

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
	else if(element != p.getColor() )
	  k++;
	else if(element == p.getColor() ){
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

const Player * Othello::opponent() const{
  if(*mCurrentPlayer == mPlayer1 )
    return &mPlayer2;
  else 
    return &mPlayer1;
}


void Othello::update(){
  if(not mIngame){
    //partie terminée 
    char c;
    std::cin>>c;
    Game::getInstance()->getHandler().change(new MainMenuState() );
  }else{
    successors = BoardGame::computeNext(mBoard, *mCurrentPlayer, succ_function);
    const Player * other = opponent();
    if(successors.empty() ){
      //le joueur ne peut pas jouer si l'autre ne peut pas jouer, la partie finie
      if(computeNext(mBoard, *other, succ_function).empty() )
	// partie terminée
	mIngame = false;
      else{
	// changement de joueurs
	mCurrentPlayer = other;
      }
    }else{
      char c;
      std::cin>>c;
      handle(c);
    }
  }
}

void Othello::render(){
  Console::getInstance()->clear();
  Console::getInstance()->setForeground(ANSI::Color::WHITE);
  Console::getInstance()->setCursor(1, 1);
  Console::getInstance()->draw("OTHELLO  -  z:up  s:down  q:left  d:right  !/p:place  x:quit");
  Console::getInstance()->setForeground(ANSI::Color::GRAY);
  Console::getInstance()->drawRectangle(1, 2, Console::getInstance()->getWidth(), 1, '#');
  Console::getInstance()->drawRectangle(1, 4, Console::getInstance()->getWidth(), 1, '#');
  Console::getInstance()->setCursor(1, 3);
  Console::getInstance()->setForeground(mPlayer1.getColor() );
  std::ostringstream oss(std::ostringstream::ate);
  /* construire avec ::ate permet d'ajouter avec "<<" à la FIN du contenu défini
     par str(...). Autrement, ça écrit au début, écrasant les 1ers caractères */
  oss.str("Joueur 1 - ");
  oss << mScore[0];
  Console::getInstance()->drawString(1, 3, oss.str() );
  Console::getInstance()->setCursor(25, 3);
  Console::getInstance()->setForeground(mPlayer2.getColor() );
  oss.str("Joueur 2 - ");
  oss << mScore[1];
  Console::getInstance()->drawString(25, 3, oss.str() );
  oss.clear();
  if(mIngame == true){
    // indicateur du joueur courant
    Console::getInstance()->setForeground(ANSI::Color::WHITE);
    if(*mCurrentPlayer == mPlayer1){
      Console::getInstance()->draw(6, 5, '^');
    }else{
      Console::getInstance()->draw(30, 5, '^');
    }
  }else{
    oss.str("Joueur ");
    oss << ( (mScore[1]>mScore[0])?2:1 );
    oss << " gagne par " <<mScore[0]<<" - "<<mScore[1];
    Console::getInstance()->setForeground(ANSI::Color::WHITE);
    Console::getInstance()->drawString(7, 19, oss.str() );
    oss.clear();
  }
  mBoard.draw(12, 8);
  Console::getInstance()->setCursor(13+(mPointerX*2), 9+mPointerY);
}
