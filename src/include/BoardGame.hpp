#ifndef BOARDGAME_HPP
#define BOARDGAME_HPP

#include "Board.hpp"
#include "State.hpp"

#include "Player.hpp"

#include <set>
#include <utility> // pour std::pair
#include <functional>

/* le type de retour de la fonction de succession : 
   des paires (x,y) de positions possibles depuis la configuration courante */
typedef std::set< std::pair< unsigned short, unsigned short> > Positions;

class BoardGame : public State{

protected:
  Board mBoard;
  unsigned short mPointerX, mPointerY; // case séléctionnée
  bool mIngame; //dit si le jeu est terminé ou pas
  Positions successors; //les coups possibles depuis le plateau courant
  std::function<bool(Board, 
		     const unsigned short&,
		     const unsigned short&,
		     const Player&) > succ_function;
 
public:
  BoardGame(const unsigned int&, const unsigned int&);
  virtual ~BoardGame();
  virtual void handle(const char& c = ' ');
  virtual bool checkMove(const char&);
  Positions computeNext(Board b, // plateau à tester
				const Player& p, //joueur dont on cherche les coups
				const std::function< bool(Board, const unsigned short&, const unsigned short&, const Player&)> & succ ); //fonction de succession
  bool isNext(const unsigned short& x, 
		      const unsigned short& y,
		      const Positions& p) const;
  virtual void update() = 0;
  virtual void render() = 0;
  
};

#endif
