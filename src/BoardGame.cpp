#include "BoardGame.hpp"

#include "State.hpp"

#include "Console.hpp"

#include <functional>
#include <utility>

BoardGame::BoardGame(const unsigned int& w = 0, 
		     const unsigned int& h = 0)
  : State(), mBoard(Board(w,h)), mPointerX(0), mPointerY(0), mIngame(true){

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
  /**
   * @brief Calcule les positions qui amènent à une configuration suivante.
   * @details Les configurations suivantes sont calculées relativement à la 
   * configuration courante, au joueur courant, et à la fonction de succession. 
   * @param b Plateau de jeu où on doit calculer les positions.
   * @param p Joueur pour lequel on calcule les coups possibles.
   * @param succ Fonction testant si une position est jouable pour le joueur 
   * donné, renvoyant vrai ou faux.
   **/
  short k; //itérateur de "ligne/droite"
  Positions res;
  for(unsigned short x = 0; x < b.getWidth(); x++){
    for(unsigned short y = 0; y < b.getHeight(); y++){
      if(succ(b, x, y, p) ){
	res.insert(std::make_pair(x,y) );
      }
    }
  }
  return res;
}

bool BoardGame::isNext(const unsigned short& x, 
		       const unsigned short& y,
		       const Positions& p) const{
  /**
   * @brief Calcule si la position est jouable dans l'ensemble des positions.
   * @details Les positions devraient avoir été calculées avec @e compute_next.
   * @param x Abscisse du coup à tester.
   * @param y Ordonnée du coup à tester.
   * @param p 
   **/
  std::pair<unsigned short, unsigned short> pos = std::make_pair(x, y);
  for(auto it = p.begin(); it != p.end(); ++it){
    if( (*it) == pos) 
      return true;
  }
  return false;
}

bool BoardGame::init(){
  return true;
}

bool BoardGame::exit(){
  return true;
}
