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
  :BoardGame(dim, dim, Color::RED, Color::BLUE), 
   mSize(dim), mNbColors(colors), mAdds(pieces),
   mSelectedX(-1), mSelectedY(-1), mPlaced(true)
{
  mScore[0] = 0;
  mScore[1] = 0;
  mFreePlaces = mSize*mSize;
  /*  for(unsigned short i = 0; i < mAdds; i++){
      addRandom();
      }*/
  
}

FiveOrMore::~FiveOrMore(){

}

void FiveOrMore::handle(const char& c){
  //std::cerr<<"FIVE OR MORE : sélécted : "<<mSelectedX<<" "<<mSelectedY<<std::endl;
  if(mSelectedX == -1 or mSelectedY == -1){
    //std::cerr<<"FIVE OR MORE : mode séléction"<<std::endl;
    handleSelection(c);
  }else{
    //std::cerr<<"FIVE OR MORE : mode déplacement"<<std::endl;
    handleAction(c);
  }
  BoardGame::handle(c);
}

void FiveOrMore::handleSelection(const char& c){
 checkMove(c);
  if(c == 'p' || c == MARK){
    // séléction d'un pion, si la case n'est pas vide
    if(mBoard.at(mPointerX, mPointerY) != -1 ){
      mSelectedX = mPointerX;
      mSelectedY = mPointerY;
    }
  }
   
}

void FiveOrMore::handleAction(const char& c){
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
       on doit pouvoir rejouer : d'où le mPlaced */

    if(mPointerX != mSelectedX or mPointerY != mSelectedY){
      mBoard.at( mPointerX, mPointerY) = mBoard.at(mSelectedX, mSelectedY);
      mBoard.at(mSelectedX, mSelectedY) = -1;
      searchLines(mPointerX, mPointerY);
      mPlaced = true;
    }
    mSelectedX = -1;
    mSelectedY = -1;
  }
}

void FiveOrMore::update(){
  if(not mIngame){
    std::cerr<<"c'est vraiment la fin"<<std::endl;
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
      for(unsigned short i = 0; i < mAdds; i++){
        if(addRandom() ){
          mPlaced = false;
          return;
        }
      }
      mPlaced = false;
    }

  }

}

void FiveOrMore::render(){
  // petit marqueur de l'emplacement d'origine du pion séléctionné
  static unsigned short boardX = 12, boardY = 8;
  Console::getInstance()->clear();
  Console::getInstance()->drawHeader("FIVE OR MORE  -  z:up  s:down  q:left  d:right  !/p:select/place  x:quit");
  displayScore();
  if(mIngame == false){
    displayResult(boardX+2, boardY + mSize/2);
  } 
  mBoard.draw(boardX, boardY);
  // surlignage de la case séléctionnée
  if(mSelectedX != -1 && mSelectedY != -1){
    Console::getInstance()->setBackground(Color::WHITE);
    Console::getInstance()->setForeground((Color) mBoard.at(mSelectedX, mSelectedY) );
    Console::getInstance()->draw(boardX+1+(mSelectedX*2), boardY+1+(mSelectedY), "ʘ");
    Console::getInstance()->setBackground(Color::BLACK);
    Console::getInstance()->setForeground(Color::WHITE);   
  }
  Console::getInstance()->setCursor(boardX+1+(mPointerX*2), boardY+1+mPointerY);
}


void FiveOrMore::displayScore(){
  std::ostringstream oss(std::ostringstream::ate);
  /* construire avec ::ate permet d'ajouter avec "<<" à la FIN du contenu défini
     par str(...). Autrement, ça écrit au début, écrasant les 1ers caractères */
  oss.str("Score - ");
  oss << mScore[0];
  Console::getInstance()->setForeground(Color::WHITE);
  Console::getInstance()->drawString(1, 3, oss.str() );
  oss.clear();
}

void FiveOrMore::displayResult(const unsigned short& x, const unsigned short& y){
  std::ostringstream oss(std::ostringstream::ate);
  oss.str("Game Over. Score final : ");
  oss << mScore[0];
  Console::getInstance()->drawString(x, y, oss.str() );
  oss.clear();
}


void FiveOrMore::searchLines(const unsigned short& x,
                             const unsigned short& y){
  /**
   * @brief Supprime les pions alignés avec @a x, @a y et met à jour le score.
   * @details Les pions ne sont supprimés que si une ligne de 5 est faite. 
   * Le score gagné est x*( (x+difficulté)/2)
   * @param x Abscisse du pion à tester.
   * @param y Ordonnée du pion à tester.
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
      //pion de la même couleur le plus éloigné
      while( xtest > 0  && 
             (  iy == 0 
                || (iy < 0 && ytest < mSize-1 ) 
                    || (iy > 0 && ytest > 0 ) )
             && (mBoard.at(xtest-ix, ytest-iy) == c )   ){
        xtest -= ix;
        ytest -= iy;
      }
      count = 1;
      //on cherche les pions, dans la direction opposée, en comptant
      while(xtest < mSize-1 &&            
            (  iy == 0 
               || (iy > 0 && ytest < mSize-1 ) 
                   || (iy < 0 && ytest > 0 ) )
            &&
            mBoard.at(xtest+ix, ytest+iy) == c){
        count++;
        xtest += ix;
        ytest += iy;
      }
      //si il y a plus de 5, on fait machine arrière et on fait l'action
      if(count >= 5){
        for(unsigned short i = 0; i < count; i++){
          if(xtest != x or ytest != y){
            mBoard.at(xtest, ytest) = -1;
            mFreePlaces++;
          }          
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
    mFreePlaces++;
    nb++;
  }
  mScore[0] += (nb * ( (nb+mAdds)/2) ); // proportionnel aux pions posés, et au challenge
  
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
  c = sColorList.at(r);
  do{  
    x = Random::get(0, mSize);
    y = Random::get(0, mSize);
  }while( mBoard.at(x, y) != -1 );
  mBoard.at(x, y) = c;
  mFreePlaces--;
  std::cerr<<"avant"<<std::endl;
  searchLines(x, y);
  int theory = 0;
  for(unsigned int i = 0; i < mSize; i++)    
    for(unsigned int j = 0; j < mSize; j++)
    if(mBoard.at(i, j) == -1)
      theory++;
  std::cerr<<"après : "<<mFreePlaces<<"/"<<theory<<std::endl;
  return end();
}


bool FiveOrMore::end(){
  if(mFreePlaces <= 0){
    mIngame = false;
    std::cerr<<"c'est la fin"<<std::endl;
    return true;
  }else{
    return false;
  }
}


