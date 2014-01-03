#ifndef BOARDGAME_HPP
#define BOARDGAME_HPP

#include "Board.hpp"
#include "State.hpp"

#include "ANSI.hpp"

#include <set>
#include <utility> // pour std::pair
#include <functional>

/* le type de retour de la fonction de succession : 
   des paires (x,y) de positions possibles depuis la configuration courante */
typedef std::set< std::pair< unsigned short, unsigned short> > Positions;

typedef ANSI::Color Player;

class BoardGame : public State{

protected:
  Board board;
  unsigned short pointerX, pointerY; // case séléctionnée
  bool ingame; //dit si le jeu est terminé ou pas
  Player player1; //un jeu possède au moins 1 joueur, sinon c'est nul
  Player * currentPlayer;
  Positions successors; //les coups possibles depuis le plateau courant
  std::function<bool(Board, 
		     const unsigned short&,
		     const unsigned short&,
		     const Player&) > succ_function;
 
public:
  BoardGame(const unsigned int&, const unsigned int&);
  virtual ~BoardGame();
  virtual void handle(const char& c = ' ');
  virtual Positions computeNext(Board b, // plateau à tester
				const Player& p, //joueur dont on cherche les coups
				const std::function< bool(Board, const unsigned short&, const unsigned short&, const Player&)> & succ ); //fonction de succession
  virtual bool isNext(const unsigned short& x, 
		      const unsigned short& y,
		      const Positions& p) const;
  virtual void update() = 0;
  virtual void render() = 0;
  virtual bool init() = 0;
  virtual bool exit() = 0;
  
};

#endif
