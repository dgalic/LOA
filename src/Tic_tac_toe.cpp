#include "Tic_tac_toe.hpp"

#include "Game.hpp"
#include "ANSI.hpp"
#include "Console.hpp"
#include "Board.hpp"
#include "StateHandler.hpp"
#include "MainMenuState.hpp"

#include <sstream> // ostringstream
#include <utility> // pour std::pair
#include <functional>


Tic_tac_toe::Tic_Tac_toe(const Color& p1,
                   const Color& p2,
                   const unsigned short& v)
: BoardGame(3, 3, p1, p2), mVictory(v){
  mScore[0] = 0;
  mScore[1] = 0;
  mPointerY --;
  mCurrentPlayer = &mPlayer1;
  mSucc_function = [this](Board b, 
			 const unsigned short& x,
			 const unsigned short& y,
			 const Player& p) 
    -> bool {
    return (b.get(x, y) != -1); //seule une case vide est jouable
  };

}
  
 Tic_tac_toe::~Tic_tac_toe(){
}

bool Tic_tac_toe::checkMove(const char& c){
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

void Tic_tac_toe::handle(const char& c){
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
    if( isNext(mPointerX, mPointerY, mSuccessors) ){
      mBoard.at(mPointerX, mPointerY) = mCurrentPlayer->getColor(); 
      searchLines(mPointerX, y2);
      mCurrentPlayer = opponent();
    }
  }
}

void Tic_tac_toe::searchLines(const unsigned short& x, const unsigned short& y){
  /**
   * @brief A partir du pion (@x, @y), vérifie si il y a un alignement de 3.
   * Si oui, alors met fin à la partie.
   */
  unsigned short count = 0;
  unsigned short c = mBoard.at(x, y);  
  unsigned short xtest, ytest;
  for(unsigned short ix = 0; ix <= 1; ix++){
    for(short iy = -1; iy <= 1; iy++){
      count = 0;
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
        if(*mCurrentPlayer == mPlayer1)
          mScore[0]++;
        else
          mScore[1]++;
        mIngame = false;
        mCurrentPlayer = opponent();
      }

    }
  }
}

const Player *Tic_tac_toe::opponent() const{
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


void Tic_tac_toe::update(){
  /**
   * Calculer  la logique de jeux
   */
  if (not mIngame) {
    //partie terminée 
    char c;
    std::cin>>c;
    Game::getInstance()->getHandler().change(new MainMenuState());
  } else {
    mSuccessors = BoardGame::computeNext(mBoard, *mCurrentPlayer);
    if (mSuccessors.empty() || mScore[0] >= mVictory || mScore[1] >= mVictory) {
      mIngame = false;
    } else{
      char c;
      std::cin>>c;
      handle(c);
    }
  }
}

void Tic_tac_toe::render(){
  // nettoye l'interface et la rafraichie
  static unsigned short boardX = 12, boardY = 8;
  Console::getInstance()->clear();

  Console::getInstance()->drawHeader("Tic Tac Toe -  z/up  s/down  q/left  d/right  !/p:place  x:quit");
  BoardGame::displayScore();
   
  // si la partie n'est pas finie
  if (mIngame == true) {
    // indicateur du joueur courant
  
    BoardGame::displayCurrentPlayer();
  } else {
    BoardGame::displayResult(boardX + 25, boardY+ 3);

  }
  mBoard.draw(boardX, boardY);
  Console::getInstance()->setCursor(boardX+1+(mPointerX*2), boardY+1+mPointerY);
}
