#ifndef IA_HPP
#define IA_HPP

#include "Player.hpp"
#include "Color.hpp"

/**
   Tentative d'IA pouvant gérer des jeux combinatoires : 
   -minmax
   -alphabeta
   ( -recherche aveugle )
 */

class IA : public Player{

private:
  unsigned short mLevel;
  

public:
  IA(const Color&, const unsigned short&);
  virtual ~IA();

};


#endif
