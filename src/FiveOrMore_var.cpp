#include "FiveOrMore_var.hpp"
#include "FiveOrMore.hpp"

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
    int i = mBoard.at(mPointerX, mPointerY);
    if( i != -1 ){
      mSelectedX = mPointerX;
      mSelectedY = mPointerY;
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
    mBoard.at(mPointerX, mPointerY) = sColorList[mColorIndex];    
    return;
  }

  if(arr == ANSI::RIGHT 
     || c == 'd'){  
    if(mColorIndex < 10 && mColorIndex < mNbColors){
      mColorIndex++;
    }else{
      mColorIndex = 0;
    }      
    mBoard.at(mPointerX, mPointerY) = sColorList[mColorIndex];
    return;
  }

  if(arr == ANSI::DOWN 
     || c == 's'){
    // annulation, retour à la couleur initiale
    mBoard.at(mPointerX, mPointerY) = sColorList[mPreviousColor];
    mSelectedX = -1;
    mSelectedY = -1;
    return;
  }
 
 if(c == 'p' || c == MARK){
    /* fixage du pion, mais attention : si on n'a pas changé sa position,
       on doit pouvoir rejouer : d'où le mPlaced */

   if(mColorIndex != mPreviousColor){
      searchLines(mPointerX, mPointerY);
      mPlaced = true;
   }
   mSelectedX = -1;
   mSelectedY = -1;
 }

}


int FiveOrMore_var::findIndex(const int& v){
  for(unsigned int i = 0; i < mNbColors; i++){
    if(sColorList[i] == v)
      return i;
  }
  return -1;
}
