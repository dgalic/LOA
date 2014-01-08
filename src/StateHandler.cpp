#include "StateHandler.hpp"

#include <stack>

StateHandler::~StateHandler(){ }

void StateHandler::push(State * s){
  /**
   * @brief Empile un nouvel état au sommet du StateHandler.
   * @details L'état posé est le nouvel état courant.
   * @param s Etat à poser.
   **/
  if( s->init() )
    mStates.push(s);
  
}

void StateHandler::pop(){
  /**
   * @brief Dépile l'état au sommet du StateHandler.
   * @details L'état dépilé appelle sa fonction @e exit.
   **/
  if( mStates.empty() )
    return;
  State * s = mStates.top();
  if(s->exit() ){
    mStates.pop();
    delete s;
  }
}

bool StateHandler::isEmpty(){
  return mStates.empty();
}

void StateHandler::change(State * s ){
  pop();
  push(s);
}

void StateHandler::clear(){
  /**
   * @brief Depile tous les états.
   */
  while( !mStates.empty() )
    pop();
}

void StateHandler::update(){
  /**
   * @brief Appelle @e update de l'état courant (sommet de la pile).
   */
  if( not mStates.empty() )
    mStates.top()->update();
}

void StateHandler::render(){
  /**
   * @brief Appelle @e render de l'état courant (sommet de la pile).
   */
  if( not mStates.empty() )
     mStates.top()->render();
}
