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
  mMoved = false;
  mP1x = w/2;
  mP1y = h-1;
  mP2x = w/2;
  mP2y = 0;
  mBoard.at(mP1x, mP1y) = mPlayer1.getColor();
  mBoard.at(mP2x, mP2y) = mPlayer2.getColor();
  
  mCurrentPlayer = &mPlayer1;
  mCurrentX = mP1x;
  mCurrentY = mP1y;
  mPointerX = mCurrentX;
  mPointerY = mCurrentY;

  mSucc_function = [this](Board b, 
                          const unsigned short& x,
                          const unsigned short& y,
                          const Player& p) 
    -> bool{
    return isSucc(b, x, y, p);
  };


  mIngame = true;

}

Isola::~Isola(){

}

bool Isola::isSucc(Board b,
                   const unsigned short& x, const unsigned short& y,
                   const Player& p) const{
  bool res;
  unsigned short testX, testY;
  if(p == mPlayer1){
    testX = mP1x;
    testY = mP1y;
  }else{
    testX = mP2x;
    testY = mP2y;
  }
  if(x > mBoard.getWidth() && y > mBoard.getHeight() ){
    std::cerr<<x<<","<<y<<" hors du plateau" <<std::endl;
    return false; // coup hors du plateau
  }

  if(mBoard.at(x, y) != -1 ){ // case non vide
    std::cerr<<x<<","<<y<<" non vide" <<std::endl;
    return false;
  }

  if( (abs(x-testX) > 1) 
      or (abs(y-testY) > 1 )
      )
    {
    std::cerr<<x<<","<<y<<" trop loin" <<std::endl;
    return false; // déplacement trop éloigné
    }
  std::cerr<<x<<","<<y<<" est possible" <<std::endl;
  return true; 
  
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
    
  if(arr == ANSI::UP
     || c == 'z'){
    if( mPointerY > 0){
      
      if(mBoard.at(mPointerX, mPointerY-1) == mCurrentPlayer->getColor()
         || isNext(mPointerX, mPointerY-1, mSuccessors) ){
        mPointerY--; // interdit de déplacer trop loin
      }
      return;


    }
  }
    
  if(arr == ANSI::LEFT 
     || c == 'q'){
    if( mPointerX > 0){
      
      if(mBoard.at(mPointerX-1, mPointerY) == mCurrentPlayer->getColor()
         || isNext(mPointerX-1, mPointerY, mSuccessors) ){
        mPointerX--;
      }
      return;

    }
  }  
  
  if(arr == ANSI::DOWN 
     || c == 's'){
    if( mPointerY < height-1  ){
      if(mBoard.at(mPointerX, mPointerY+1) == mCurrentPlayer->getColor()
         || isNext(mPointerX, mPointerY+1, mSuccessors) ){
        mPointerY++;
      }
      return;
    }
  }
  
  if(arr == ANSI::RIGHT 
     || c == 'd'){  
    if( mPointerX < width-1){      
      if(mBoard.at(mPointerX+1, mPointerY) == mCurrentPlayer->getColor()
         || isNext(mPointerX+1, mPointerY, mSuccessors) ){
        mPointerX++; 
      }
      return;
    }
  }
  
  BoardGame::handle(c);

  if(c == 'p' or c == MARK){
    if(isNext(mPointerX, mPointerY, mSuccessors) ){
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
    }
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
    mSuccessors = BoardGame::computeNext(mBoard, *mCurrentPlayer);
    std::cerr<<mSuccessors.size()<<" coups possibles" <<std::endl;
    if(mSuccessors.empty() ){
      mIngame = false;
      if(*mCurrentPlayer == mPlayer1){
        mScore[1]++;
      }else{
        mScore[0]++;
      }
      return;
    }
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
        Console::getInstance()->draw(boardX+(2*i)+1, boardY+j+1, '@');
    }
  }
  Console::getInstance()->setForeground(Color::WHITE);
  Console::getInstance()->setCursor(boardX+1+(mPointerX*2), boardY+1+mPointerY);

}
