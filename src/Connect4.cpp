#include "Connect4.hpp"

#include "Game.hpp"
#include "ANSI.hpp"
#include "Console.hpp"
#include "Board.hpp"
#include "StateHandler.hpp"
#include "MainMenuState.hpp"

#include <sstream> // ostringstream
#include <utility> // pour std::pair
#include <functional>


Connect4::Connect4(const Color& p1,
                   const Color& p2)
: BoardGame(7, 6), mPlayer1(p1), mPlayer2(p2) {
  mPlayer1 = p1;
  mPlayer2 = p2;
  mCurrentPlayer = &mPlayer1;
  succ_function = [this](Board b, 
			 const unsigned short& x,
			 const unsigned short& y,
			 const Player& p) 
    -> bool {
    return b.at(x,0) == -1;
  };

}
  
Connect4::~Connect4(){
}

bool Connect4::checkMove(const char& c){
  // si le joueur veut déplacer son curseur vers la gauche
  ANSI::Arrow arr;
  arr = checkArrow(c);
  if (arr == ANSI::LEFT || c == 'q') {
    if (mPointerX > 0) {
      mPointerX--;
    }
    return true;
  }

  // si le joueur veut déplacer son curseur vers la droite
  if ( arr == ANSI::RIGHT || c == 'd') {
    if ( mPointerX < mBoard.getWidth()-1 ) {
      mPointerX++;
    }
    return true;
  }
  return false;
}

void Connect4::handle(const char& c){
  /**
   * Cette fonction vérifie les touches tapées au clavier
   * par les joueurs.
   * @param c représente le caractère taper au clavier
   */
  if(checkMove(c) ){
    return;
  }
  
  // si le joueur veut quitter le jeux
  if (c == 'x') {
    Game::getInstance()->getHandler().change(
                                             new MainMenuState());
    return;
  }

  // si le joueur veux executer une action, ici joueur une piece
  if (c == 'p' || c == MARK) {
    /* vérifie si b est en position gagnante 
     * avec le coup jouer */
    if( isNext( mPointerX, mPointerY, successors)) {
      std::cerr<<"le coup "<<mPointerX<<","<<mPointerY\
               <<" est possible"<<std::endl;
      std::cerr<<"le coup n'est pas gagnant"<<std::endl;
      mBoard.at(mPointerX, 0) = mCurrentPlayer->getColor(); 
      unsigned short y2 = drop(mPointerX, 0);
      searchLines(mPointerX, y2);
      mCurrentPlayer = opponent();
    }
  }
}

unsigned short Connect4::drop(const unsigned short& x, const unsigned short& y){
  /** 
      @brief Fait tomber la pièce donnée via la gravité. 
      Retourne la nouvelle ordonnée.
  */
  int c = mBoard.at(x, y);
  unsigned short y2 = y;
  mBoard.at(x, y) = -1;
  while(y2 < mBoard.getHeight()-1 && mBoard.at(x, y2+1) == -1){
    y2++;
  }
  mBoard.at(x, y2) = c;
  return y2;
}

void Connect4::searchLines(const unsigned short& x, const unsigned short& y){
  /**
   * @brief A partir du pion (@x, @y), vérifie si il y a un alignement de 4.
   * Si oui, alors met fin à la partie.
   */
  unsigned short nb = 0; // nombre de pions détruits (le posé est cumulé)
  unsigned short count = 0;
  unsigned short c = mBoard.at(x, y);  
  unsigned short xtest, ytest;
  for(unsigned short ix = 0; ix <= 1; ix++){
    for(short iy = -1; iy <= 1; iy++){
      xtest = x;
      ytest = y;
      if(ix == 0 && iy == 0)
        continue;
      while( xtest > 0  && 
             (  iy == 0 
                || (iy < 0 && ytest < mBoard.getHeight()-1 ) 
                || (iy > 0 && ytest > 0 ) )
             && (mBoard.at(xtest-ix, ytest-iy) == c )   ){
        xtest -= ix;
        ytest -= iy;
      }
      count = 1;
      while(xtest < mBoard.getWidth()-1 &&            
            (  iy == 0 
               || (iy > 0 && ytest < mBoard.getHeight()-1 ) 
               || (iy < 0 && ytest > 0 ) )
            &&
            mBoard.at(xtest+ix, ytest+iy) == c){
        count++;
        xtest += ix;
        ytest += iy;
      }
      if(count >= 4){
        mIngame = false;
        mCurrentPlayer = opponent();
        /*        for(unsigned short i = 0; i < count; i++){
                  if(xtest != x or ytest != y)
                  mBoard.at(xtest, ytest) = -1;
                  xtest -= ix;
                  ytest -= iy;
                  nb++;
                  }*/
      }

    }
  }
}

const Player *Connect4::opponent() const{
  /**
   * @brief Retourne le joueur prochain joueur à jouer
   * Cette fonction laisse la main au joueur suivant
   */
  if (*mCurrentPlayer == mPlayer1 ) {
    return &mPlayer2;
  } else {
    return &mPlayer1;
  }
}


void Connect4::update(){
  /**
   * Calculer  la logique de jeux
   */
  if (not mIngame) {
    //partie terminée 
    char c;
    std::cin>>c;
    Game::getInstance()->getHandler().change(new MainMenuState());
  } else {
    successors = BoardGame::computeNext(mBoard, *mCurrentPlayer, succ_function);
    if (successors.empty()) {
      mIngame = false;
    } else{
      char c;
      std::cin>>c;
      handle(c);
    }
  }
}

void Connect4::render(){
  // nettoye l'interface et la rafraichie
  Console::getInstance()->clear();
  Console::getInstance()->setForeground(ANSI::Color::WHITE);
  Console::getInstance()->setCursor(1, 1);
  Console::getInstance()->draw("OTHELLO  -  q:left  d:right  !/p:place  x:quit");
  Console::getInstance()->setForeground(ANSI::Color::GRAY);
  Console::getInstance()->drawRectangle(1, 2, Console::getInstance()->getWidth(), 1, '#');
  Console::getInstance()->drawRectangle(1, 4, Console::getInstance()->getWidth(), 1, '#');

  std::ostringstream oss(std::ostringstream::ate);
  /* construire avec ::ate permet d'ajouter avec "<<" à la FIN du contenu défini
     par str(...). Autrement, ça écrit au début, écrasant les 1ers caractères */
    
  Console::getInstance()->setCursor(1, 3);
  Console::getInstance()->setForeground(mPlayer1.getColor() );
  oss.str("Joueur 1 - ");
  Console::getInstance()->drawString(1, 3, oss.str() );

  Console::getInstance()->setCursor(25, 3);
  Console::getInstance()->setForeground(mPlayer2.getColor() );
  oss.str("Joueur 2 - ");
  Console::getInstance()->drawString(25, 3, oss.str() );
    
  oss.clear();
   
  // si la partie n'est pas finie
  if (mIngame == true) {
    // indicateur du joueur courant
    Console::getInstance()->setForeground(ANSI::Color::WHITE);
        
    // affiche sur l'interface à quel joueur doit jouer
    if (*mCurrentPlayer == mPlayer1) {
      Console::getInstance()->draw(6, 5, '^');
    } else {
      Console::getInstance()->draw(30, 5, '^');
    }
  } else {
    // Si partie finie affiche qui à gagner ou égaliter
    oss.str("Joueur ");
    oss << ( (mCurrentPlayer == &mPlayer1)?1:2);
    Console::getInstance()->setForeground(ANSI::Color::WHITE);
    Console::getInstance()->drawString(7, 19, oss.str() );
    oss.clear();
  }
  mBoard.draw(12, 8);
  Console::getInstance()->setCursor(13+(mPointerX*2), 9+mPointerY);
}
