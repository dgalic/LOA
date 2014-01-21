
#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <string>
#include <vector>



/** 
    Cette classe représente un état de jeu, et par extension, un état du programme.
    Un jeu est défini par : 
    -une position initiale : méthode init
    -pour chaque position, un ensemble de positions atteignables : méthode compute
    -un état final : méthode compute, mais mène à la méthode exit
    Dans le cas d'un jeu graphique, on a besoin en plus : 
    -gestion des inputs : méthode compute
    -une manière de représenter une position : méthode render.

    Le champ ID permet d'identifier le type d'état, afin de ne pas empiler le même état au sommet.
    
    Toute autre méthode devrait être privée : 
    par exemple on pourra séparer compute en deux, computeInput et computeLogic, mais ces deux méthodes
    devront être privées.
    Les membres aussi, on peut en rajouter tant qu'on veut, mais ils doivent être privés (de toutes façons,
    les membres devraient toujours être privés/protégés).
 */

class State {

public:
  virtual ~State(){};
  /** traite l'évènement décrit par la touche entrée */
  virtual void handle(const char& = ' ') = 0;
  /** calcule la prochaine configuration, selon la logique de jeu */
  virtual void update() = 0;
  /** dit à la GUI comment représenter la configuration courante */
  virtual void render() = 0;


};

#endif
