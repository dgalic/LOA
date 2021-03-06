#include "Connect4.hpp"

#include "Game.hpp"
#include "Console.hpp"
#include "Board.hpp"

#include <functional>


Connect4::Connect4(const Color& p1,
                   const Color& p2,
                   const unsigned short& v)
: BoardGame(7, 6, p1, p2), mVictory(v){
  mScore[0] = 0;
  mScore[1] = 0;
  mPointer.snd() --;
  mCurrentPlayer = &mPlayer1;
  mSucc_function = [this](Board b, 
                          const Point& pos,
			 const Player& pl) 
    -> bool {
    return b.at(pos.fst() , 0) == -1;
  };

}
  
Connect4::~Connect4(){
}

bool Connect4::checkMove(const char& c){
  // si le joueur veut déplacer son curseur vers la gauche
  ANSI::Arrow arr;
  arr = checkArrow(c);
  if (arr == ANSI::LEFT || c == 'q') {
    if (mPointer.fst() > 0) {
      mPointer.fst()--;
    }
    return true;
  }

  // si le joueur veut déplacer son curseur vers la droite
  if ( arr == ANSI::RIGHT || c == 'd') {
    if ( mPointer.fst() < (int)mBoard.getWidth()-1 ) {
      mPointer.fst()++;
    }
    return true;
  }
  return false;
}


Positions Connect4::computeNext(Board b,
                                const Player& p){
  Positions res;
  for(unsigned short x = 0; x < b.getWidth(); x++){
      Point po(x,0);
      if(mSucc_function(b, po, p) ){
	res.insert(po);            
    }
  }
  return res;
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
  // si le joueur veux executer une action, ici joueur une piece
  if (c == 'p' || c == MARK) {
    /* vérifie si b est en position gagnante 
     * avec le coup jouer */
    if( isNext( Point(mPointer.fst(), 0), mSuccessors)) {
      mBoard.at(mPointer.fst(), 0) = mCurrentPlayer->getColor(); 
      unsigned short y2 = drop(mPointer.fst(), 0);
      searchLines(mPointer.fst(), y2);
      mCurrentPlayer = opponent();
    }
  }
  BoardGame::handle(c);
}

unsigned short Connect4::drop(const unsigned short& x, const unsigned short& y){
  /** 
      @brief Fait tomber la pièce donnée via la gravité. 
      Retourne la nouvelle ordonnée.
  */
  int c = mBoard.at(x, y);
  unsigned short y2 = y;
  if(c == -1)
    return y;
  mBoard.at(x, y) = -1;
  while(y2 < mBoard.getHeight()-1 && mBoard.at(x, y2+1) == -1){
    y2++;
  }
  mBoard.at(x, y2) = c;
  if( (y != 0) && (mBoard.get(x,y-1) != -1)) {
    drop(x, y-1);
  }
  //  if( y2 != y)
  //  searchLines(x, y2);
  return y2;
}

void Connect4::searchLines(const unsigned short& x, const unsigned short& y){
  /**
   * @brief A partir du pion (@x, @y), vérifie si il y a un alignement de 4.
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
      while((ix == 0 || xtest < mBoard.getWidth()-1) &&            
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
          if(*mCurrentPlayer == mPlayer1) {
            mScore[0]++;
          } else {
            mScore[1]++;
          }
          mCurrentPlayer = opponent();
          return;
      }
    }
  }
}


void Connect4::update(){
  /**
   * Calculer  la logique de jeux
   */
  if (not mIngame) {
    //partie terminée 
    char c = Console::getInstance()->getInput();
    Game::getInstance()->mainMenu();
  } else {
    mSuccessors = BoardGame::computeNext(mBoard, *mCurrentPlayer);
    if (mSuccessors.empty() || mScore[0] >= mVictory || mScore[1] >= mVictory) {
      mIngame = false;
    } else{
      char c = Console::getInstance()->getInput();
      handle(c);
    }
  }
}

void Connect4::render(){
  // nettoye l'interface et la rafraichie
  static unsigned short boardX = 12, boardY = 8;
  Console::getInstance()->clear();

  Console::getInstance()->drawHeader("Connect 4 - q/left  d/right  !/p:drop  x:quit");
  BoardGame::displayScore();
   
  // si la partie n'est pas finie
  if (mIngame == true) {
    // indicateur du joueur courant
  
    BoardGame::displayCurrentPlayer();
  } else {
    BoardGame::displayResult(boardX + 25, boardY+ 3);

  }
  mBoard.draw(boardX, boardY);
  Console::getInstance()->setCursor(boardX+1+(mPointer.fst()*2), boardY+1+mPointer.snd());
}
