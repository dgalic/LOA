#include "FiveOrMore.hpp"
#include "Random.hpp"

const std::array<Color, 10> FiveOrMore::sColorList = { 
  ANSI::RED, 
  ANSI::GREEN, 
  ANSI::BLUE, 
  ANSI::YELLOW, 
  ANSI::PINK, 
  ANSI::GRAY, 
  ANSI::BROWN, 
  ANSI::PURPLE, 
  ANSI::LIGHTCYAN, 
  ANSI::LIGHTGREEN
};

FiveOrMore::FiveOrMore(const unsigned short& dim,
                       const unsigned short& pieces)
  :BoardGame(dim, dim), mSize(dim), mAdds(pieces)
{
  mFreePlaces = mSize*mSize;
}

FiveOrMore::~FiveOrMore(){

}

void FiveOrMore::handle(const char& c){

}


void FiveOrMore::update(){
  if(not mIngame){

  }else{
    //ajout de n pions random
    for(unsigned short i = 0; i < mAdds; i++){
      if(addRandom() ){
        return;
      }
    }
    //le joueur joue
  }

}

void FiveOrMore::render(){

}


unsigned short FiveOrMore::drop(const unsigned short& x,
                                const unsigned short& y){
  /**
   * @brief Supprime les pions alignés avec @a x, @a y.
   * @details Les pions ne sont supprimés que si une ligne de 5 est faite.
   * @param x Abscisse du pion à tester.
   * @param y Ordonnée du pion à tester.
   * @return Nombre de pions effacés.
   */
  unsigned short res = 0;
  Color c((Color)mBoard.at(x, y) );
  
  //pion de la même couleur le plus à gauche

  //pion de la même couleur le plus en haut

  //pion de la même couleur le plus haut/gauche (diagonale)

  //pion de la même couleur le plus bas/gauche (anti-diagonale)

  return res;
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
  c = sColorList.at(Random::get(0, mNbColors-1) );
  do{
    x = Random::get(0, mSize-1);
    y = Random::get(0, mSize-1);
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


