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
    mPlayer1(p1), mPlayer2(p2), mCurrentPlayer(&mPlayer1),
    mPointer(0,0), mIngame(true){

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
    if(mPointer.snd() > 0)
      mPointer.snd()--;
    return true;
  }
    
  if(arr == ANSI::LEFT 
     || c == 'q'){
    if(mPointer.fst() > 0)
      mPointer.fst()--;
    return true;
  }

  if(arr == ANSI::DOWN 
     || c == 's'){
    if(mPointer.snd() < (int)mBoard.getHeight()-1 )
      mPointer.snd()++;
    return true;
  }

  if(arr == ANSI::RIGHT 
     || c == 'd'){
    if(mPointer.fst() < (int)mBoard.getWidth()-1 )
      mPointer.fst()++;
    return true;
  }
  return false;
}

Positions BoardGame::computeNext(Board b,
				 const Player& p){
  /**
   * @brief Calcule les positions qui amènent à une configuration suivante.
   * @details Les configurations suivantes sont calculées relativement à la 
   * configuration courante, au joueur courant, et à la fonction de succession. 
   * @param b Plateau de jeu où on doit calculer les positions.
   * @param p Joueur pour lequel on calcule les coups possibles.
   * @param succ Fonction testant si une position est jouable pour le joueur 
   * donné, renvoyant vrai ou faux.
   **/
  Positions res;
  for(unsigned short x = 0; x < b.getWidth(); x++){
    for(unsigned short y = 0; y < b.getHeight(); y++){
      Point po(x,y);
      if(mSucc_function(b, po, p) ){
	res.insert(po);      
      }
    }
  }
  return res;
}

bool BoardGame::isNext(const Point& p,
		       const Positions& e) const{
  /**
   * @brief Calcule si la position est jouable dans l'ensemble des positions.
   * @details Les positions devraient avoir été calculées avec @e compute_next.
   * @param x Abscisse du coup à tester.
   * @param y Ordonnée du coup à tester.
   * @param p 
   **/
  for(auto it = e.begin(); it != e.end(); ++it){
    if( (*it) == p) 
      return true;
  }
  return false;
}

const Player * BoardGame::opponent() const{
    /**
   * @brief Retourne l'opposant au joueur courant
   */
  if(*mCurrentPlayer == mPlayer1 )
    return &mPlayer2;
  else 
    return &mPlayer1;
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
