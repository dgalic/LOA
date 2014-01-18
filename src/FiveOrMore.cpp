#include "FiveOrMore.hpp"
#include "Random.hpp"
#include "Game.hpp"
#include "ANSI.hpp"
#include "Console.hpp"
#include "MainMenuState.hpp"
#include "StateHandler.hpp"
#include <sstream>

const std::array<Color, 10> FiveOrMore::sColorList = { 
  ANSI::RED, 
  ANSI::LIGHTGREEN, 
  ANSI::BLUE, 
  ANSI::YELLOW, 
  ANSI::PINK, 
  ANSI::GRAY, 
  ANSI::BROWN, 
  ANSI::PURPLE, 
  ANSI::LIGHTCYAN, 
  ANSI::GREEN
};

FiveOrMore::FiveOrMore(const unsigned short& dim,
                       const unsigned short& colors,
                       const unsigned short& pieces)
  :BoardGame(dim, dim), mSize(dim), mNbColors(colors), mAdds(pieces), mScore(0),
   mSelectedX(-1), mSelectedY(-1), mPlaced(true)
{
  mFreePlaces = mSize*mSize;
  /*  for(unsigned short i = 0; i < mAdds; i++){
      addRandom();
      }*/
  
}

FiveOrMore::~FiveOrMore(){

}

void FiveOrMore::handle(const char& c){
  std::cerr<<"FIVE OR MORE : sélécted : "<<mSelectedX<<" "<<mSelectedY<<std::endl;
  if(mSelectedX == -1 or mSelectedY == -1){
    std::cerr<<"FIVE OR MORE : mode séléction"<<std::endl;
    handleSelection(c);
  }else{
    std::cerr<<"FIVE OR MORE : mode déplacement"<<std::endl;
    handleMove(c);
  }
}

void FiveOrMore::handleSelection(const char& c){
  ANSI::Arrow arr; 
  arr = checkArrow(c);   
  if(arr == ANSI::UP 
     || c == 'z'){
    if(mPointerY > 0)
      mPointerY--;
    return;
  }
    
  if(arr == ANSI::LEFT 
     || c == 'q'){
    if(mPointerX > 0)
      mPointerX--;
    return;
  }

  if(arr == ANSI::DOWN 
     || c == 's'){
    if(mPointerY < mBoard.getHeight()-1 )
      mPointerY++;
    return;
  }

  if(arr == ANSI::RIGHT 
     || c == 'd'){
    if(mPointerX < mBoard.getWidth()-1 )
      mPointerX++;
    return;
  }
  if(c == 'p' || c == MARK){
    // séléction d'un pion, si la case n'est pas vide
    if(mBoard.at(mPointerX, mPointerY) != -1 ){
      mSelectedX = mPointerX;
      mSelectedY = mPointerY;
    }
  }
   
  if(c == 'x'){
    Game::getInstance()->getHandler().change(new MainMenuState() );
    return;
  }
}

void FiveOrMore::handleMove(const char& c){
  ANSI::Arrow arr;
  arr = checkArrow(c);
  if(arr == ANSI::UP 
     || c == 'z'){
    /* on peut bouger sur une case, soit si elle est vide, 
       soit si c'est la case d'origine */
    if( mPointerY > 0 && 
        ( (mPointerX == mSelectedX && mPointerY-1 == mSelectedY )
          || 
          (mBoard.at(mPointerX, mPointerY-1) == -1 )  )
        )
      mPointerY--;
    return;
  }
    
  if(arr == ANSI::LEFT 
     || c == 'q'){
    if( mPointerX > 0 && 
        ( (mPointerX-1 == mSelectedX && mPointerX == mSelectedY )
          || 
          (mBoard.at(mPointerX-1, mPointerY) == -1 )   )
        )
      mPointerX--;
    return;
  }

  if(arr == ANSI::DOWN 
     || c == 's'){
    if( mPointerY < mSize-1 && 
        ( (mPointerX == mSelectedX && mPointerY+1 == mSelectedY )
          || 
          (mBoard.at(mPointerX, mPointerY+1) == -1 )  )
        )
      mPointerY++;
    return;
  }

  if(arr == ANSI::RIGHT 
     || c == 'd'){  
    if( mPointerX < mSize-1 && 
        ( (mPointerX+1 == mSelectedX && mPointerY == mSelectedY )
          || 
          (mBoard.at(mPointerX+1, mPointerY) == -1 )  )
        )
      mPointerX++;
    return;
  }
  if(c == 'p' || c == MARK){
    /* fixage du pion, mais attention : si on n'a pas changé sa position,
       on doit pouvoir rejouer */

    if(mPointerX != mSelectedX or mPointerY != mSelectedY){
      mBoard.at( mPointerX, mPointerY) = mBoard.at(mSelectedX, mSelectedY);
      mBoard.at(mSelectedX, mSelectedY) = -1;
      drop(mPointerX, mPointerY);
      mPlaced = true;
    }
    mSelectedX = -1;
    mSelectedY = -1;
  }
}

void FiveOrMore::update(){
  if(not mIngame){
    char c;
    std::cin>>c;
    Game::getInstance()->getHandler().change(new MainMenuState() );
  }else{
    //le joueur joue
    char c;
    std::cin >> c;
    handle(c);
    //ajout de n pions randoms si on a déplacé un pion
    if(mPlaced){
      std::cerr<<"FIVE OR MORE : ajout de "<<mAdds<<" pièces"<<std::endl;
      for(unsigned short i = 0; i < mAdds; i++){
        if(addRandom() ){
          return;
        }
      }
      mPlaced = false;
    }

  }

}

void FiveOrMore::render(){
  // petit marqueur de l'emplacement d'origine du pion séléctionné
  Console::getInstance()->clear();
  Console::getInstance()->setForeground(ANSI::Color::WHITE);
  Console::getInstance()->setCursor(1, 1);
  Console::getInstance()->draw("FIVE OR MORE  -  z:up  s:down  q:left  d:right  !/p:select/place  x:quit");
  Console::getInstance()->setForeground(ANSI::Color::GRAY);
  Console::getInstance()->drawRectangle(1, 2, Console::getInstance()->getWidth(), 1, '#');
  Console::getInstance()->drawRectangle(1, 4, Console::getInstance()->getWidth(), 1, '#');
  Console::getInstance()->setCursor(1, 3);
  std::ostringstream oss(std::ostringstream::ate);
  /* construire avec ::ate permet d'ajouter avec "<<" à la FIN du contenu défini
     par str(...). Autrement, ça écrit au début, écrasant les 1ers caractères */
  oss.str("Score - ");
  oss << mScore;
  Console::getInstance()->setForeground(ANSI::Color::WHITE);
  Console::getInstance()->drawString(1, 3, oss.str() );
  oss.clear();
  if(mIngame == false){
    oss.str("Game Over. Score final : ");
    oss << mScore;
    Console::getInstance()->drawString(7, 19, oss.str() );
    oss.clear();
  } 
  static unsigned short boardX = 12, boardY = 8;
  mBoard.draw(boardX, boardY);
  // surlignage de la case séléctionnée
  if(mSelectedX != -1 && mSelectedY != -1){
    Console::getInstance()->setBackground(ANSI::Color::WHITE);
    Console::getInstance()->setForeground((ANSI::Color) mBoard.at(mSelectedX, mSelectedY) );
    Console::getInstance()->draw(boardX+1+(mSelectedX*2), boardY+1+(mSelectedY), "ʘ");
    Console::getInstance()->setBackground(ANSI::Color::BLACK);
    Console::getInstance()->setForeground(ANSI::Color::WHITE);   
  }
  Console::getInstance()->setCursor(boardX+1+(mPointerX*2), boardY+1+mPointerY);
}


void FiveOrMore::drop(const unsigned short& x,
                      const unsigned short& y){
  /**
   * @brief Supprime les pions alignés avec @a x, @a y et met à jour le score.
   * @details Les pions ne sont supprimés que si une ligne de 5 est faite. 
   * Le score gagné est x*( (x+difficulté)/2)
   * @param x Abscisse du pion à tester.
   * @param y Ordonnée du pion à tester.
   */
  std::cerr<<"FIVE OR MORE : test des pions à supprimer à cause de "<<x<<","<<y<<std::endl;
  unsigned short nb = 0; // nombre de pions détruits (le posé est cumulé)
  unsigned short count = 0;
  unsigned short c = mBoard.at(x, y);  
  unsigned short xtest, ytest;
  for(unsigned short ix = 0; ix <= 1; ix++){
    for(short iy = -1; iy <= 1; iy++){
      xtest = x;
      ytest = y;
      std::cerr<<"FIVE OR MORE : direction "<<ix<<","<<iy<<std::endl;
      if(ix == 0 && iy == 0)
        continue;
      //pion de la même couleur le plus à gauche
      while( xtest > 0  && 
             (  iy == 0 
                || (iy < 0 && ytest < mSize-1 ) 
                    || (iy > 0 && ytest > 0 ) )
             && (mBoard.at(xtest-ix, ytest-iy) == c )   ){
        xtest -= ix;
        ytest -= iy;
      }
      std::cerr<<"FIVE OR MORE : pion de la même couleur le plus à gauche :  "<<xtest<<","<<ytest<<std::endl;
      count = 1;
      while(xtest < mSize-1 &&            
            (  iy == 0 
               || (iy > 0 && ytest < mSize-1 ) 
                   || (iy < 0 && ytest > 0 ) )
            &&
            mBoard.at(xtest+ix, ytest+iy) == c){
        std::cerr<<"FIVE OR MORE : "<<xtest+ix<<","<<ytest+iy<<" = "<<mBoard.at(xtest+ix, ytest+iy)<<"/"<<c<<std::endl; 
        count++;
        xtest += ix;
        ytest += iy;
      }
      std::cerr<<"FIVE OR MORE : "<<count<<" pions alignés"<<std::endl;
      if(count >= 5){
        for(unsigned short i = 0; i < count; i++){
          if(xtest != x or ytest != y)
            mBoard.at(xtest, ytest) = -1;
          xtest -= ix;
          ytest -= iy;
          nb++;
        }
      }

    }
  }
  // fin des vérifications
  if(nb > 0){
    mBoard.at(x, y) = -1;
    nb++;
  }
  mScore += (nb * ( (nb+mAdds)/2) ); // proportionnel aux pions posés, et au challenge
  
}  

bool FiveOrMore::addRandom(){
  /**
   * @brief Ajoute une pion aléatoirement
   * @details La couleur et la position sont choisies aléatoirement. On vérifie
   * si la pose du pion entraine la suppression de lignes, et on retourne vrai
   * si après tout ça le plateau est plein
   * @return True si le plateau est plein après la pose.
   */
  unsigned short x, y;
  Color c;
  unsigned short r = Random::get(0, mNbColors);
  std::cerr<< "accès aux couleurs : "<<r<<"/"<<sColorList.size() <<std::endl;
  c = sColorList.at(r);
  do{  
    std::cerr<< "accès aux cases : "<<mSize<<" /"<<mSize <<std::endl;
    x = Random::get(0, mSize);
    y = Random::get(0, mSize);
  }while( mBoard.at(x, y) != -1 );
  mBoard.at(x, y) = c;
  drop(x, y);
  return end();
}


bool FiveOrMore::end(){
  if(mFreePlaces <= 0){
    mIngame = false;
    return true;
  }else{
    return false;
  }
}


