#include "StateHandler.hpp"

#include "Singleton.hpp"

#include <iostream>

void StateHandler::push(State * gs){
  if( gs->init() )
    states.push(gs);
  
}

void StateHandler::pop(){
  if( states.empty() )
    return;
  State * gs = states.top();
  if(gs->exit() ){
    states.pop();
    delete gs;
  }
}

bool StateHandler::isEmpty(){
  return states.empty();
}

void StateHandler::change(State * gs ){
  pop();
  push(gs);
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
