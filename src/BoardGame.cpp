#include "BoardGame.hpp"

#include "State.hpp"

#include "ANSI.hpp"
#include "Color.hpp"
#include "Console.hpp"
#include "Game.hpp"
#include "MainMenuState.hpp"

#include <functional>
#include <string>
#include <sstream>
#include <utility>

BoardGame::BoardGame(const unsigned int& w, 
		     const unsigned int& h,
                     const Color& p1, const Color& p2)
  : State(), mBoard(w, h),
    mPlayer1(p1), mPlayer2(p2),
    mPointerX(0), mPointerY(0), mIngame(true){

}

BoardGame::~BoardGame(){

}

void BoardGame::handle(const char& c){
  if(c == 'x'){
    Game::getInstance()->getHandler().change(new MainMenuState() );
    return;
  }
}

bool BoardGame::checkMove(const char& c){
  /**
   * @brief Bouge le curseur si on a pressé les touches standard.
   * @details Sur pression d'une flèche ou de zqsd.
   * @param c Caractère à tester (touche entrée).
   * @return True si on a déplace, false sinon.
   */
  ANSI::Arrow arr;
  arr = checkArrow(c);
  if(arr == ANSI::UP 
     || c == 'z'){
    if(mPointerY > 0)
      mPointerY--;
    return true;
  }
    
  if(arr == ANSI::LEFT 
     || c == 'q'){
    if(mPointerX > 0)
      mPointerX--;
    return true;
  }

  if(arr == ANSI::DOWN 
     || c == 's'){
    if(mPointerY < mBoard.getHeight()-1 )
      mPointerY++;
    return true;
  }

  if(arr == ANSI::RIGHT 
     || c == 'd'){
    if(mPointerX < mBoard.getWidth()-1 )
      mPointerX++;
    return true;
  }
  return false;
}

Positions BoardGame::computeNext(Board b,
				 const Player& p,
				 const std::function<\
					       
						bool	\
					       (Board, \
						const unsigned short&, \
						const unsigned short&,
						const Player&)>	\
				 & succ ){
  /**
   * @brief Calcule les positions qui amènent à une configuration suivante.
   * @details Les configurations suivantes sont calculées relativement à la 
   * configuration courante, au joueur courant, et à la fonction de succession. 
   * @param b Plateau de jeu où on doit calculer les positions.
   * @param p Joueur pour lequel on calcule les coups possibles.
   * @param succ Fonction testant si une position est jouable pour le joueur 
   * donné, renvoyant vrai ou faux.
   **/
  short k; //itérateur de "ligne/droite"
  Positions res;
  for(unsigned short x = 0; x < b.getWidth(); x++){
    for(unsigned short y = 0; y < b.getHeight(); y++){
      if(succ(b, x, y, p) ){
	res.insert(std::make_pair(x,y) );
      }
    }
  }
  return res;
}

bool BoardGame::isNext(const unsigned short& x, 
		       const unsigned short& y,
		       const Positions& p) const{
  /**
   * @brief Calcule si la position est jouable dans l'ensemble des positions.
   * @details Les positions devraient avoir été calculées avec @e compute_next.
   * @param x Abscisse du coup à tester.
   * @param y Ordonnée du coup à tester.
   * @param p 
   **/
  std::pair<unsigned short, unsigned short> pos = std::make_pair(x, y);
  for(auto it = p.begin(); it != p.end(); ++it){
    if( (*it) == pos) 
      return true;
  }
  return false;
}


void BoardGame::displayScore(){
   std::ostringstream oss(std::ostringstream::ate);
  /* construire avec ::ate permet d'ajouter avec "<<" à la FIN du contenu défini
     par str(...). Autrement, ça écrit au début, écrasant les 1ers caractères */
  oss.str("Joueur 1 - ");
  oss << mScore[0];
  Console::getInstance()->setForeground(mPlayer1.getColor() );
  Console::getInstance()->drawString(1, 3, oss.str() );
  oss.str("Joueur 2 - ");
  oss << mScore[1];
  Console::getInstance()->setForeground(mPlayer2.getColor() );
  Console::getInstance()->drawString(25, 3, oss.str() );
  oss.clear();
}

void BoardGame::displayCurrentPlayer(){
    Console::getInstance()->setForeground(Color::WHITE);
    if(*mCurrentPlayer == mPlayer1){
      Console::getInstance()->draw(6, 5, '^');
    }else{
      Console::getInstance()->draw(30, 5, '^');
    }
}

void BoardGame::displayResult(const unsigned short& x, const unsigned short& y){
  Console::getInstance()->setForeground(Color::WHITE);
  if( mScore[0] == mScore[1]){
    Console::getInstance()->drawString(x, y, "Egalité" );
  }else{
    std::ostringstream oss(std::ostringstream::ate);
    oss.str("Joueur ");
    oss << ( (mScore[1]>mScore[0])?2:1 );
    oss << " gagne par " <<mScore[0]<<" - "<<mScore[1];
    Console::getInstance()->drawString(x, y, oss.str() );
    oss.clear();
  }
}
