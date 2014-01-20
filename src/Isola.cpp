#include "Isola.hpp"

#include "ANSI.hpp"
#include "Console.hpp"
#include "Game.hpp"

Isola::Isola(const Color& p1, 
             const Color& p2,
             const unsigned short& w,
             const unsigned short& h)
  :BoardGame(w, h, p1, p2), mP1(w/2, h-1), mP2(w/2, 0)
{
  mMoved = false;
  mBoard.at( mP1.fst(), mP1.snd() ) = mPlayer1.getColor();
  mBoard.at( mP2.fst(), mP2.snd() ) = mPlayer2.getColor();
  mScore[0] = 0;
  mScore[1] = 0;
  mCurrentPlayer = &mPlayer1;
  mCurrent = mP1;
  mPointer = mCurrent;
  mSucc_function = [this](Board b, 
                          const Point& pos,
                          const Player& pl) 
    -> bool{
    return isSucc(b, pos, pl);
  };


  mIngame = true;

}

Isola::~Isola(){

}

bool Isola::isSucc(Board b,
                   const Point& pos,
                   const Player& pl) const{
  Point test(mP1);
  int x = pos.fst(), y = pos.snd();
  if(pl == mPlayer2){
    test = mP2;
  }
  if(x > (int)mBoard.getWidth() && y > (int)mBoard.getHeight() ){
    return false; // coup hors du plateau
  }

  if(mBoard.at(x, y) != -1 ){ // case non vide
    return false;
  }

  if( (abs(x-test.fst() ) > 1) 
      or (abs(y-test.snd() ) > 1 )
      )
    {
    return false; // déplacement trop éloigné
    }
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
  int& x = mPointer.fst(), & y = mPointer.snd();

  arr = checkArrow(c);
    
  if(arr == ANSI::UP
     || c == 'z'){
    if( y > 0){
      
      if(mBoard.at(x, y-1) == mCurrentPlayer->getColor()
         || isNext(Point(x, y-1), mSuccessors) ){
        y--; // interdit de déplacer trop loin
      }
      return;


    }
  }
    
  if(arr == ANSI::LEFT 
     || c == 'q'){
    if( x > 0){
      
      if(mBoard.at(x-1, y) == mCurrentPlayer->getColor()
         || isNext(Point(x-1, y), mSuccessors) ){
        x--;
      }
      return;

    }
  }  
  
  if(arr == ANSI::DOWN 
     || c == 's'){
    if( y < height-1  ){
      if(mBoard.at(x, y+1) == mCurrentPlayer->getColor()
         || isNext(Point(x, y+1), mSuccessors) ){
        y++;
      }
      return;
    }
  }
  
  if(arr == ANSI::RIGHT 
     || c == 'd'){  
    if( x < width-1){      
      if(mBoard.at(x+1, y) == mCurrentPlayer->getColor()
         || isNext(Point(x+1, y), mSuccessors) ){
        x++; 
      }
      return;
    }
  }
  
  BoardGame::handle(c);

  if(c == 'p' or c == MARK){
    if(isNext(Point(x, y), mSuccessors) ){
      mBoard.at( x, y) = mBoard.at(mCurrent.fst(), mCurrent.snd());
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
    Game::getInstance()->mainMenu();
  }else{
    mSuccessors = BoardGame::computeNext(mBoard, *mCurrentPlayer);
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
