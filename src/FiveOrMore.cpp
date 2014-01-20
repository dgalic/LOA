#include "FiveOrMore.hpp"
#include "Random.hpp"
#include "Game.hpp"
#include "Console.hpp"

#include <sstream>

const std::array<Color, 10> FiveOrMore::sColorList = { 
  Color::RED, 
  Color::LIGHTGREEN, 
  Color::BLUE, 
  Color::YELLOW, 
  Color::PINK, 
  Color::GREEN,
  Color::BROWN, 
  Color::LIGHTCYAN, 
  Color::PURPLE, 
  Color::GRAY
};

FiveOrMore::FiveOrMore(const unsigned short& dim,
                       const unsigned short& colors,
                       const unsigned short& pieces)
  :BoardGame(dim, dim, Color::RED, Color::BLUE), 
   mSize(dim), mNbColors(colors), mAdds(pieces),
   mSelected(-1, -1), mPlaced(true)
{
  mScore[0] = 0;
  mScore[1] = 0;
  mFreePlaces = mSize*mSize;
  
}

FiveOrMore::~FiveOrMore(){

}

void FiveOrMore::handle(const char& c){
  if(mSelected.fst() == -1 or mSelected.snd() == -1){
    handleSelection(c);
  }else{
    handleAction(c);
  }
  BoardGame::handle(c);
}

void FiveOrMore::handleSelection(const char& c){
  BoardGame::checkMove(c);
  if(c == 'p' || c == MARK){
    // séléction d'un pion, si la case n'est pas vide
    if(mBoard.at(mPointer.fst(), mPointer.snd()) != -1 ){
      mSelected.fst() = mPointer.fst();
      mSelected.snd() = mPointer.snd();
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
    if( mPointer.snd() > 0 && 
        ( (mPointer.fst() == mSelected.fst() && mPointer.snd()-1 == mSelected.snd() )
          || 
          (mBoard.at(mPointer.fst(), mPointer.snd()-1) == -1 )  )
        )
      mPointer.snd()--;
    return;
  }
    
  if(arr == ANSI::LEFT 
     || c == 'q'){
    if( mPointer.fst() > 0 && 
        ( (mPointer.fst()-1 == mSelected.fst() && mPointer.fst() == mSelected.snd() )
          || 
          (mBoard.at(mPointer.fst()-1, mPointer.snd()) == -1 )   )
        )
      mPointer.fst()--;
    return;
  }

  if(arr == ANSI::DOWN 
     || c == 's'){
    if( mPointer.snd() < mSize-1 && 
        ( (mPointer.fst() == mSelected.fst() && mPointer.snd()+1 == mSelected.snd() )
          || 
          (mBoard.at(mPointer.fst(), mPointer.snd()+1) == -1 )  )
        )
      mPointer.snd()++;
    return;
  }

  if(arr == ANSI::RIGHT 
     || c == 'd'){  
    if( mPointer.fst() < mSize-1 && 
        ( (mPointer.fst()+1 == mSelected.fst() && mPointer.snd() == mSelected.snd() )
          || 
          (mBoard.at(mPointer.fst()+1, mPointer.snd()) == -1 )  )
        )
      mPointer.fst()++;
    return;
  }
 
  if(c == 'p' || c == MARK){
    /* fixage du pion, mais attention : si on n'a pas changé sa position,
       on doit pouvoir rejouer : d'où le mPlaced */

    if(mPointer.fst() != mSelected.fst() or mPointer.snd() != mSelected.snd()){
      mBoard.at( mPointer.fst(), mPointer.snd()) = mBoard.at(mSelected.fst(), mSelected.snd());
      mBoard.at(mSelected.fst(), mSelected.snd()) = -1;
      searchLines(mPointer.fst(), mPointer.snd());
      mPlaced = true;
    }
    mSelected.fst() = -1;
    mSelected.snd() = -1;
  }
}

void FiveOrMore::update(){
  if(not mIngame){
    char c;
    std::cin>>c;
    Game::getInstance()->mainMenu();
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
    displayResult(boardX+mSize+2, boardY + mSize/2);
  } 
  mBoard.draw(boardX, boardY);
  // surlignage de la case séléctionnée
  if(mSelected.fst() != -1 && mSelected.snd() != -1){
    Console::getInstance()->setBackground(Color::WHITE);
    Console::getInstance()->setForeground((Color) mBoard.at(mSelected.fst(), mSelected.snd()) );
    Console::getInstance()->draw(boardX+1+(mSelected.fst()*2), boardY+1+(mSelected.snd()), "ʘ");
    Console::getInstance()->setBackground(Color::BLACK);
    Console::getInstance()->setForeground(Color::WHITE);   
  }
  Console::getInstance()->setCursor(boardX+1+(mPointer.fst()*2), boardY+1+mPointer.snd());
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
  int c = mBoard.at(x, y);  
  if(c == -1)
    return;
  unsigned short xtest, ytest;
  for(unsigned short ix = 0; ix <= 1; ix++){
    for(short iy = -1; iy <= 1; iy++){
      xtest = x;
      ytest = y;
      if(ix == 0 && iy == 0) //prévient des boucles
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
      while( (ix == 0 || xtest < mSize-1) &&      
             (  iy == 0 
                || (iy > 0 && ytest < mSize-1 ) 
                || (iy < 0 && ytest > 0 ) )
             && mBoard.at(xtest+ix, ytest+iy) == c )
        {
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
  searchLines(x, y);
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


