#include "Isola.hpp"

#include "ANSI.hpp"
#include "Console.hpp"
#include "Game.hpp"
#include "MainMenuState.hpp"

Isola::Isola(const Color& p1, 
             const Color& p2,
             const unsigned short& w,
             const unsigned short& h)
  :BoardGame(w, h, p1, p2)
{
  mBoard.at(w/2, 0) = p1;
  mBoard.at(w/2, h-1) = p2;

}

Isola::~Isola(){

}

void Isola::handle(const char& c){
  if(mMoved){
    handleDestroy(c);
  }else{
    handleMove(c);
  }
}

void Isola::handleMove(const char& c){
  ANSI::Arrow arr;
  static const unsigned short width = mBoard.getWidth(), 
    height = mBoard.getHeight();
  arr = checkArrow(c);
  if(arr != ANSI::NOARROW){
    if ( (abs(mPointerX-mCurrentX) <= 1) 
         && (abs(mPointerY-mCurrentY) <= 1 ) )
      return; // interdit de déplacer trop loin
  }
  if(arr == ANSI::UP 
     || c == 'z'){
    /* on peut bouger sur une case, soit si elle est vide, 
       soit si c'est la case d'origine */
    if( mPointerY > 0 && 
        ( (mPointerX == mCurrentX && mPointerY-1 == mCurrentY )
          || 
          (mBoard.at(mPointerX, mPointerY-1) == -1 )
          )
        )
      mPointerY--;
    return;
  }
    
  if(arr == ANSI::LEFT 
     || c == 'q'){
    if( mPointerX > 0 && 
        ( (mPointerX-1 == mCurrentX && mPointerX == mCurrentY )
          || 
          (mBoard.at(mPointerX-1, mPointerY) == -1 )   )
        )
      mPointerX--;
    return;
  }

  if(arr == ANSI::DOWN 
     || c == 's'){
    if( mPointerY < width-1 && 
        ( (mPointerX == mCurrentX && mPointerY+1 == mCurrentY )
          || 
          (mBoard.at(mPointerX, mPointerY+1) == -1 )  )
        )
      mPointerY++;
    return;
  }

  if(arr == ANSI::RIGHT 
     || c == 'd'){  
    if( mPointerX < height-1 && 
        ( (mPointerX+1 == mCurrentX && mPointerY == mCurrentY )
          || 
          (mBoard.at(mPointerX+1, mPointerY) == -1 )  )
        )
      mPointerX++;
    return;
  }

  BoardGame::handle(c);
  if(c == 'p' or c == MARK){
    mBoard.at( mPointerX, mPointerY) = mBoard.at(mCurrentX, mCurrentY);
    mBoard.at(mCurrentX, mCurrentY) = -1;
    if(*mCurrentPlayer == mPlayer1){
      mP1x = mPointerX;
      mP1y = mPointerY;
    }else{
      mP2x = mPointerX;
      mP2y = mPointerY;
    }
    mMoved = true;
    mCurrentX = -1;
    mCurrentY = -1;
    return;
  }   


}

void Isola::handleDestroy(const char& c){
  if(BoardGame::checkMove(c) )
    return;
  BoardGame::handle(c);
  if(c == 'p' or c == MARK){
    if(mBoard.at(mPointerX, mPointerY) == -1 ){
      mBoard.at(mPointerX, mPointerY) = -2;
      mMoved = false;
      mCurrentPlayer = opponent();
      if(*mCurrentPlayer == mPlayer1){
        mCurrentX = mP1x;
        mCurrentY = mP1y;        
      }else{
        mCurrentX = mP2x;
        mCurrentY = mP2y;
      }
      mPointerX = mCurrentX;
      mPointerY = mCurrentY;
      return;
    }    
  }
  
}

void Isola::update(){
  char c;
  if(not mIngame){
    std::cin >> c;
    Game::getInstance()->getHandler().change(new MainMenuState() );
  }else{
    std::cin >> c;
    handle(c);    
  }
}

void Isola::render(){
  static unsigned short boardX = 12, boardY = 8;
  Console::getInstance()->clear();
  Console::getInstance()->drawHeader("ISOLA  -  z/up  s/down  q/left  d/right  !/p:place/destroy  x:quit");
  BoardGame::displayScore();
  if(mIngame == true){
    // indicateur du joueur courant
    BoardGame::displayCurrentPlayer();
  }else{
    BoardGame::displayResult(boardX+25, boardY+4);
  }
  mBoard.draw(boardX, boardY);
  unsigned short w = mBoard.getWidth(), h = mBoard.getHeight();
  Console::getInstance()->setForeground(Color::GRAY);
  for(unsigned short i = 0; i < w; i++){
    for(unsigned short j = 0; j < h; j++){
      if(mBoard.at(i, j) == -2)
        Console::getInstance()->draw(mPointerX+i, mPointerY+j, '@');
    }
  }
  Console::getInstance()->setForeground(Color::WHITE);
  Console::getInstance()->setCursor(boardX+1+(mPointerX*2), boardY+1+mPointerY);

}
