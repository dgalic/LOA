#include "StateHandler.hpp"

#include "Singleton.hpp"

#include <iostream>

void StateHandler::push(State * gs){
  if( gs->init() )
    states.push(gs);
  
}

State * StateHandler::pop(){
  if( states.empty() )
    return NULL;
  State * gs = states.top();
  if(gs->exit() )
    states.pop();
  return gs;
}

bool StateHandler::isEmpty(){
  return states.empty();
}

State * StateHandler::change(State * gs ){
  State * old = pop();
  push(gs);
  return old;
}

void StateHandler::clear(){
  while( !states.empty() )
    pop();
}

void StateHandler::update(){
  if( not states.empty() )
    states.top()->update();
}

void StateHandler::render(){
  if( not states.empty() )
     states.top()->render();
}
