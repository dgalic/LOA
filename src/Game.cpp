#include "Game.hpp"

#include <iostream>

#include "StateHandler.hpp"
#include "Console.hpp"
#include "MainMenuState.hpp"
#include "Singleton.hpp"

void Game::init(){
  /**
   * @brief Initialise le programme.
   * @details L'état de commencement est @e StartState. Le membre @e mRunning est 
   * mis à true, permettant de lancer la boucle de jeu par la suite.
  */
  StateHandler::getInstance()->push(new MainMenuState() );
  mRunning = true;
  std::cerr<<"Game initialized"<<std::endl;
}

void Game::stop(){
  /**
   * @brief Stoppe l'exécution de la boucle.
   * @details Le membre @e mRunning est mis sur @e false.
  */
  mRunning = false;
}

void Game::resume(){
  /**
   * @brief Reprend l'exécution de la boucle.
   * @details Le membre @e mRunning est mis sur @e true.
  */
  mRunning = true;
}

void Game::exit(){
  stop();
  StateHandler::getInstance()->clear();
  StateHandler::getInstance()->destroy();
  Console::getInstance()->exit();  
  Console::getInstance()->destroy();
  std::cerr<<"Game destroyed properly"<<std::endl;
}

void Game::loop(){
  /**
   * @brief Lance la boucle de jeu.
   * @details La boucle de jeu va calculer le nouvel état suivant la logique de 
   * jeu, puis rendre l'état obtenu suite à cette mise à jour. Si le membre
   * @e mRunning passe à @e false, la boucle s'arrête.
   **/
  std::cerr<<"Starting Game Loop"<<std::endl;
  while(mRunning){
    StateHandler::getInstance()->update();
    StateHandler::getInstance()->render();
  }
}

int main(){
  char c = 16;
  std::cerr << "test 16: "<<c<<"-"<<"-"<<std::endl;
  c = 32;
  std::cerr << "test 32: "<<c<<"-"<<"-"<<std::endl;
  Game::getInstance()->init();
  Game::getInstance()->loop();
  Game::getInstance()->exit();
  Game::getInstance()->destroy();
}
