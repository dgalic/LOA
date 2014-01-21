#include "Chomp.hpp"

#include "Game.hpp"
#include "Console.hpp"
#include "Board.hpp"

#include <functional>

Chomp::Chomp(const Color& p1, const Color& p2,
             const unsigned short& w, const unsigned short& h)
: BoardGame(w, h, p1, p2){
  mScore[0] = 0;
  mScore[1] = 0;
  mSucc_function = [this](Board b, 
			 const Point& pos,
			 const Player& p) 
    -> bool {
    return (b.get(pos.fst(), pos.snd() ) == -1); //seule une case vide est jouable
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
    Game::getInstance()->mainMenu();
    return;
  }

  // si le joueur veux executer une action, ici joueur une piece
  if (c == 'p' || c == MARK) {
    /* vérifie si b est en position gagnante 
     * avec le coup jouer */
    if( isNext(mPointer, mSuccessors) ){
      mBoard.at(mPointer.fst(), mPointer.snd()) = mCurrentPlayer->getColor(); 
      fillcolor(mPointer.fst(), mPointer.snd());
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

    // sinon on remplie les cases
    unsigned short i;
    int j;
    for (i = x; i < mBoard.getWidth(); i++) {
        for (j = y; j >= 0; j--) {
            mBoard.at(i, j) = color_player; 
        }
    }
}


void Chomp::update(){
  /**
   * Calculer  la logique de jeux
   */
  if (not mIngame) {
    //partie terminée 
    char c = Console::getInstance()->getInput();
    Game::getInstance()->mainMenu();
  } else {
    mSuccessors = BoardGame::computeNext(mBoard, *mCurrentPlayer);
    if (mSuccessors.empty()) {
      mIngame = false;
    } else{
      char c = Console::getInstance()->getInput();
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
  Console::getInstance()->setForeground(Color::WHITE);
  Console::getInstance()->draw(boardX+1, boardY+mBoard.getHeight(), 'X');
  Console::getInstance()->setCursor(boardX+1+(mPointer.fst()*2), boardY+1+mPointer.snd());
}










Chomp::Config::Config()
  : ::Config(4)
{

}

Chomp::Config::~Config(){ 
  
}

void Chomp::Config::launchGame(){
  Game::getInstance()->getHandler().change(new Chomp(*mColor1, *mColor2,
                                                   mWidth, mHeight) );
}

void Chomp::Config::render(){
  ::Config::render();
  Console::getInstance()->draw(1, 1, "Chomp  -  !/p:select  x:quit");
  Console::getInstance()->setForeground(Color::WHITE);
  Console::getInstance()->setCursor(Console::getInstance()->getWidth(), 0);
}
