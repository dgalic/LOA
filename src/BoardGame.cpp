#include "BoardGame.hpp"

#include "State.hpp"

#include "Console.hpp"

#include <functional>
#include <utility>

BoardGame::BoardGame(const unsigned int& w = 0, 
		     const unsigned int& h = 0)
  : State(), board(Board(w,h)), pointerX(0), pointerY(0), ingame(true), player1(ANSI::RED), currentPlayer(&player1){
}

BoardGame::~BoardGame(){

}

void BoardGame::handle(const char& c){

}

Positions BoardGame::computeNext(Board b,
				 const Player& p,
				 const std::function<\
					       
						bool	\
					       (Board, \
						const unsigned short&, \
						const unsigned short&,
						const Player&)>	\
				 & succ ){
  short k; //itérateur de "droite"
  Positions res;
  for(unsigned short x = 0; x < b.getWidth(); x++){
    for(unsigned short y = 0; y < b.getHeight(); y++){
      if(succ(b, x, y, p) ){
	std::cerr<<"trouvé un successeur"<<std::endl;
	res.insert(std::make_pair(x,y) );
      }
    }
  }
  return res;
}

bool BoardGame::isNext(const unsigned short& x, 
		       const unsigned short& y,
		       const Positions& p) const{
  std::pair<unsigned short, unsigned short> pos = std::make_pair(x, y);
  for(auto it = p.begin(); it != p.end(); ++it){
    if( (*it) == pos) 
      return true;
  }
  return false;
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
