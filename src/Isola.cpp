#include "Isola.hpp"

#include "ANSI.hpp"
#include "Console.hpp"
#include "Game.hpp"
#include "MainMenuState.hpp"

Isola::Isola(const Color& p1, 
             const Color& p2,
             const unsigned short& w,
             const unsigned short& h)
  :BoardGame(w, h, p1, p2), mP1(w/2, h-1), mP2(w/2, 0)
{
  mMoved = false;
  mBoard.at( mP1.fst(), mP1.snd() ) = mPlayer1.getColor();
  mBoard.at( mP2.fst(), mP2.snd() ) = mPlayer2.getColor();
  
  mCurrentPlayer = &mPlayer1;
  mCurrent = mP1;
  mPointer = mCurrent;
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
    testX = mP1.fst();
    testY = mP1.snd();
  }else{
    testX = mP2.fst();
    testY = mP2.snd();
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
    if( mPointer.snd() > 0){
      
      if(mBoard.at(mPointer.fst(), mPointer.snd()-1) == mCurrentPlayer->getColor()
         || isNext(mPointer.fst(), mPointer.snd()-1, mSuccessors) ){
        mPointer.snd()--; // interdit de déplacer trop loin
      }
      return;


    }
  }
    
  if(arr == ANSI::LEFT 
     || c == 'q'){
    if( mPointer.fst() > 0){
      
      if(mBoard.at(mPointer.fst()-1, mPointer.snd()) == mCurrentPlayer->getColor()
         || isNext(mPointer.fst()-1, mPointer.snd(), mSuccessors) ){
        mPointer.fst()--;
      }
      return;

    }
  }  
  
  if(arr == ANSI::DOWN 
     || c == 's'){
    if( mPointer.snd() < height-1  ){
      if(mBoard.at(mPointer.fst(), mPointer.snd()+1) == mCurrentPlayer->getColor()
         || isNext(mPointer.fst(), mPointer.snd()+1, mSuccessors) ){
        mPointer.snd()++;
      }
      return;
    }
  }
  
  if(arr == ANSI::RIGHT 
     || c == 'd'){  
    if( mPointer.fst() < width-1){      
      if(mBoard.at(mPointer.fst()+1, mPointer.snd()) == mCurrentPlayer->getColor()
         || isNext(mPointer.fst()+1, mPointer.snd(), mSuccessors) ){
        mPointer.fst()++; 
      }
      return;
    }
  }
  
  BoardGame::handle(c);

  if(c == 'p' or c == MARK){
    if(isNext(mPointer.fst(), mPointer.snd(), mSuccessors) ){
      mBoard.at( mPointer.fst(), mPointer.snd()) = mBoard.at(mCurrent.fst(), mCurrent.snd());
      mBoard.at(mCurrent.fst(), mCurrent.snd() ) = -1;
      if(*mCurrentPlayer == mPlayer1){
        mP1 = mPointer;
      }else{
        mP2 = mPointer;
      }
      mMoved = true;
      mCurrent.fst() = -1;
      mCurrent.snd() = -1;
    }
    return;
  }   


}

void Isola::handleDestroy(const char& c){
  if(BoardGame::checkMove(c) )
    return;
  BoardGame::handle(c);
  if(c == 'p' or c == MARK){
    if(mBoard.at(mPointer.fst(), mPointer.snd()) == -1 ){
      mBoard.at(mPointer.fst(), mPointer.snd()) = -2;
      mMoved = false;
      mCurrentPlayer = opponent();
      if(*mCurrentPlayer == mPlayer1){
        mCurrent = mP1;
      }else{
        mCurrent = mP2;
      }
      mPointer = mCurrent;
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
  Console::getInstance()->setCursor(boardX+1+(mPointer.fst()*2), boardY+1+mPointer.snd() );

}
