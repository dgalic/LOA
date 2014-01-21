#include "FiveOrMore_var.hpp"
#include "FiveOrMore.hpp"

#include "Game.hpp"
#include "Console.hpp"

FiveOrMore_var::FiveOrMore_var(const unsigned short& dim,
                               const unsigned short& c,
                               const unsigned short& a)
  :BoardGame(dim, dim, Color::RED, Color::BLUE), 
   FiveOrMore(dim, c, a)
{
}

FiveOrMore_var::~FiveOrMore_var(){}


void FiveOrMore_var::handleSelection(const char& c){
 checkMove(c);
  if(c == 'p' || c == MARK){
    int i = mBoard.at(mPointer.fst(), mPointer.snd());
    if( i != -1 ){
      mSelected.fst() = mPointer.fst();
      mSelected.snd() = mPointer.snd();
      mPreviousColor = findIndex( i );
      mColorIndex = mPreviousColor;
    }
  }
   
}

void FiveOrMore_var::handleAction(const char& c){
  ANSI::Arrow arr;
  arr = checkArrow(c);
  if(arr == ANSI::LEFT 
     || c == 'q'){
    if(mColorIndex > 0){
      mColorIndex--;
    }else{
      mColorIndex = mNbColors-1;
    }
    mBoard.at(mPointer.fst(), mPointer.snd()) = sColorList[mColorIndex];    
    return;
  }

  if(arr == ANSI::RIGHT 
     || c == 'd'){  
    if(mColorIndex < 10 && mColorIndex < mNbColors-1){
      mColorIndex++;
    }else{
      mColorIndex = 0;
    }      
    mBoard.at(mPointer.fst(), mPointer.snd()) = sColorList[mColorIndex];
    return;
  }

  if(arr == ANSI::DOWN 
     || c == 's'){
    // annulation, retour à la couleur initiale
    mBoard.at(mPointer.fst(), mPointer.snd()) = sColorList[mPreviousColor];
    mSelected.fst() = -1;
    mSelected.snd() = -1;
    return;
  }
 
 if(c == 'p' || c == MARK){
    /* fixage du pion, mais attention : si on n'a pas changé sa position,
       on doit pouvoir rejouer : d'où le mPlaced */

   if(mColorIndex != mPreviousColor){
      searchLines(mPointer.fst(), mPointer.snd());
      mPlaced = true;
   }
   mSelected.fst() = -1;
   mSelected.snd() = -1;
 }

}


int FiveOrMore_var::findIndex(const int& v){
  for(unsigned int i = 0; i < mNbColors; i++){
    if(sColorList[i] == v)
      return i;
  }
  return -1;
}










FiveOrMore_var::Config::Config()
  : FiveOrMore::Config() {
  mWidth = 10;
}


FiveOrMore_var::Config::~Config(){

}


void FiveOrMore_var::Config::launchGame(){
  Game::getInstance()->getHandler().change( \
             new FiveOrMore_var(mWidth,mColors,mPieces) );
}
