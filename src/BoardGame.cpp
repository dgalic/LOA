#include "BoardGame.hpp"

#include "State.hpp"

#include "Console.hpp"

BoardGame::BoardGame(const unsigned int& w = 0, 
		     const unsigned int& h = 0)
  : State(), board(Board(w,h)), pointerX(0), pointerY(0), ingame(true){
}

BoardGame::~BoardGame(){

}

void BoardGame::handle(const char& c){

}

void BoardGame::update(){
  
}

void BoardGame::render(){
  
}

bool BoardGame::init(){
  return true;
}

bool BoardGame::exit(){
  return true;
}
