#include "Tic_tac_toe.hpp"

#include "Game.hpp"
#include "ANSI.hpp"
#include "Console.hpp"
#include "Board.hpp"
#include "StateHandler.hpp"
#include "MainMenuState.hpp"

#include <sstream> // ostringstream
#include <utility> // pour std::pair
#include <functional>


Tic_tac_toe::Tic_tac_toe(const Color& p1,
                   const Color& p2,
                   const unsigned short& v)
: BoardGame(3, 3, p1, p2), mVictory(v){
  mScore[0] = 0;
  mScore[1] = 0;
  mCurrentPlayer = &mPlayer1;
  mSucc_function = [this](Board b, 
                          const Point& po,
			 const Player& pl) 
    -> bool {
    return (b.get(po.fst(), po.snd() ) == -1); //seule une case vide est jouable
  };

}
  
 Tic_tac_toe::~Tic_tac_toe(){
}

void Tic_tac_toe::handle(const char& c){
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
    if( isNext(mPointer, mSuccessors) ){
      mBoard.at(mPointer.fst(), mPointer.snd()) = mCurrentPlayer->getColor(); 
      searchLines(mPointer.fst(), mPointer.snd());
      mCurrentPlayer = opponent();
    }
  }
}

void Tic_tac_toe::searchLines(const unsigned short& x, const unsigned short& y){
  /**
   * @brief A partir du pion (@x, @y), vérifie si il y a un alignement de 3.
   * Si oui, alors met fin à la partie.
   */
    int h_g, h_m, h_d,// h :haut ,g: gauche ,m:milieu ,d :droite
       m_g, m_m, m_d,
       b_g, b_m, b_d;//b : bas

    h_g = mBoard.get(2,0);
    h_m = mBoard.get(2,1);
    h_d = mBoard.get(2,2);
    m_g = mBoard.get(1,0);
    m_m = mBoard.get(1,1);
    m_d = mBoard.get(1,2);
    b_g = mBoard.get(0,0);
    b_m = mBoard.get(0,1);
    b_d = mBoard.get(0,2);

    bool ligne_is_align = false;
    //test ligne
    if ( ((h_g == h_m) && (h_g == h_d) && (h_g != -1))
        || ((m_g == m_m) && (m_g == h_d) && (m_g != -1))
        || ((b_g == b_m) && (b_g == b_d)) && (b_g != -1)){
        ligne_is_align = true;
    }

    //test colonne
    if ( ((h_g == m_g) && (h_g == b_g) && (h_g != -1))
        || ((h_m == m_m) && (h_m == b_m) && (h_m != -1))
        || ((h_d == m_d) && (h_d == b_d)) && (h_d != -1)){
        ligne_is_align = true;
    }

    //test diagonale \ et /
    if ( ((h_g == m_m) && (h_g == b_d) && (h_g != -1))
        || ((b_g == m_m) && (b_g == h_d)) && (b_g != -1)){
        ligne_is_align = true;
    }

    if(ligne_is_align){
        if(*mCurrentPlayer == mPlayer1) {
            mScore[0]++;
        } else {
            mScore[1]++;
        }
          mCurrentPlayer = opponent();
    }
}

void Tic_tac_toe::update(){
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
    if (mSuccessors.empty() || mScore[0] >= mVictory || mScore[1] >= mVictory) {
      mIngame = false;
    } else{
      char c;
      std::cin>>c;
      handle(c);
    }
  }
}

void Tic_tac_toe::render(){
  // nettoye l'interface et la rafraichie
  static unsigned short boardX = 12, boardY = 8;
  Console::getInstance()->clear();

  Console::getInstance()->drawHeader("Tic Tac Toe -  z/up  s/down  q/left  d/right  !/p:place  x:quit");
  BoardGame::displayScore();
   
  // si la partie n'est pas finie
  if (mIngame == true) {
    // indicateur du joueur courant
  
    BoardGame::displayCurrentPlayer();
  } else {
    BoardGame::displayResult(boardX + 25, boardY+ 3);

  }
  mBoard.draw(boardX, boardY);
  Console::getInstance()->setCursor(boardX+1+(mPointer.fst()*2), boardY+1+mPointer.snd());
}
