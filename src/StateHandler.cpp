#include "StateHandler.hpp"

#include "Singleton.hpp"

#include <iostream>

void StateHandler::push(State * s){
  /**
   * @brief Empile un nouvel état au sommet du StateHandler.
   * @details L'état posé est le nouvel état courant.
   * @param s Etat à poser.
   **/
  if( s->init() )
    states.push(s);
  
}

void StateHandler::pop(){
  /**
   * @brief Dépile l'état au sommet du StateHandler.
   * @details L'état dépilé appelle sa fonction @e exit.
   **/
  if( states.empty() )
    return;
  State * s = states.top();
  if(s->exit() ){
    states.pop();
    delete s;
  }
}

bool StateHandler::isEmpty(){
  return states.empty();
}

void StateHandler::change(State * s ){
  pop();
  push(s);
}

void StateHandler::clear(){
  /**
   * @brief Depile tous les états.
   */
  while( !states.empty() )
    pop();
}

void StateHandler::update(){
  /**
   * @brief Appelle @e update de l'état courant (sommet de la pile).
   */
  if( not states.empty() )
    states.top()->update();
}

void StateHandler::render(){
  /**
   * @brief Appelle @e render de l'état courant (sommet de la pile).
   */
  if( not states.empty() )
     states.top()->render();
}
