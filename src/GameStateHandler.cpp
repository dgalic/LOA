#include "GameStateHandler.hpp"

#include "Singleton.hpp"


void GameStateHandler::push(GameState * gs){
  if( gs->init() )
    states.push(gs);
  
}

GameState * GameStateHandler::pop(){
  if( states.empty() )
    return NULL;
  GameState * gs = states.top();
  if(gs->exit() )
    states.pop();
  return gs;
}

bool GameStateHandler::isEmpty(){
  return states.empty();
}

GameState * GameStateHandler::change(GameState * gs ){
  GameState * old = pop();
  push(gs);
  return old;
}

void GameStateHandler::clear(){
  while( !states.empty() )
    pop();
}

void GameStateHandler::update(){
  if( not states.empty() )
    states.top()->update();
}

void GameStateHandler::render(){
  if( not states.empty() )
     states.top()->render();
}
