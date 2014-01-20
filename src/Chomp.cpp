#include "Chomp.hpp"

#include "Game.hpp"
#include "ANSI.hpp"
#include "Console.hpp"
#include "Board.hpp"
#include "StateHandler.hpp"
#include "MainMenuState.hpp"

#include <sstream> // ostringstream
#include <utility> // pour std::pair
#include <functional>

Chomp::Chomp()
: BoardGame(8, 10, Color::RED, Color::BLUE){
  mScore[0] = 0;
  mScore[1] = 0;
  mCurrentPlayer = &mPlayer1;
  mSucc_function = [this](Board b, 
			 const unsigned short& x,
			 const unsigned short& y,
			 const Player& p) 
    -> bool {
    return (b.get(x, y) == -1); //seule une case vide est jouable
  };

}
  
 Chomp::~Chomp(){
}

void Chomp::handle(const char& c){
  /**
   * Cette fonction vérifie les touches tapées au clavier
   * par les joueurs.
   * @param c représente le caractère taper au clavier
   */
  if(checkMove(c) ){
    return;
  }
  
  // si le joueur veut quitter le jeux
  if (c == 'x') {
    Game::getInstance()->getHandler().change(
                                             new MainMenuState());
    return;
  }

  // si le joueur veux executer une action, ici joueur une piece
  if (c == 'p' || c == MARK) {
    /* vérifie si b est en position gagnante 
     * avec le coup jouer */
    if( isNext(mPointerX, mPointerY, mSuccessors) ){
      mBoard.at(mPointerX, mPointerY) = mCurrentPlayer->getColor(); 
      fillcolor(mPointerX, mPointerY);
      mCurrentPlayer = opponent();
    }
  }
}

void Chomp::fillcolor(const unsigned short& x, const unsigned short& y){
    /**
     * @brief remplie les case qui sont aprés x ou y
     * si case la case du en haut et gauche remplie le joueur oppose gagne
     * Si oui, alors met fin à la partie.
     */
    int color_player = mCurrentPlayer->getColor();

    if ((x == 0 ) && (y == mBoard.getHeight()-1)) {
        if(*mCurrentPlayer == mPlayer1) {
            mScore[1]++;
        } else {
            mScore[0]++;
        }
        mCurrentPlayer = opponent();
    }

    // sinon on remplie les case
    unsigned short i;
    int j;
    for (i = x; i < mBoard.getWidth(); i++) {
        for (j = y; j >= 0; j--) {
            mBoard.at(i, j) = color_player; 
        }
    }
}

const Player *Chomp::opponent() const{
  /**
   * @brief Retourne le joueur prochain joueur à jouer
   * Cette fonction laisse la main au joueur suivant
   */
  if (*mCurrentPlayer == mPlayer1 ) {
    return &mPlayer2;
  } else {
    return &mPlayer1;
  }
}


void Chomp::update(){
  /**
   * Calculer  la logique de jeux
   */
  if (not mIngame) {
    //partie terminée 
    char c;
    std::cin>>c;
    Game::getInstance()->getHandler().change(new MainMenuState());
  } else {
    mSuccessors = BoardGame::computeNext(mBoard, *mCurrentPlayer);
    if (mSuccessors.empty()) {
      mIngame = false;
    } else{
      char c;
      std::cin>>c;
      handle(c);
    }
  }
}

void Chomp::render(){
  // nettoye l'interface et la rafraichie
  static unsigned short boardX = 12, boardY = 8;
  Console::getInstance()->clear();

  Console::getInstance()->drawHeader("Chomp -  z/up  s/down  q/left  d/right  !/p:place  x:quit");
  BoardGame::displayScore();
   
  // si la partie n'est pas finie
  if (mIngame == true) {
    // indicateur du joueur courant
  
    BoardGame::displayCurrentPlayer();
  } else {
    BoardGame::displayResult(boardX + 25, boardY+ 3);

  }
  mBoard.draw(boardX, boardY);
  Console::getInstance()->setCursor(boardX+1+(mPointerX*2), boardY+1+mPointerY);
}
