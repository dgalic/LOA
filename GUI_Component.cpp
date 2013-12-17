#include "GUI_Component.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace GUI{

  Component::Component() : selected(false), 
			   active(false), 
			   width(0), 
			   height(0){
  }


  Component::Component(const unsigned int& x,
		       const unsigned int& y) 
  : selected(false), 
    active(false), 
    width(w), 
    height(h){
  }

  Component::~Component(){
  }

  /** 
      Un component est quelque chose d'abstrait. Comme il ne peut pas être
      instancié, il ne peut pas être séléctionné.
      La séléction décrit "cet élément a le focus". Ici, ça voudra surtout
      dire "le curseur de la souris est dessus".
   */
  bool isSelectable(){
    return false;
  }
  
  /**
     Un component est activable si il y a un action quand on fait un input
     spécial (validation) lorsqu'il est séléctionné.
     comme un component ne représente rien de concret, il n'y a pas d'action
     associée : il n'est pas activée.
     Ici, l'activation se fera via le clic gauche.
   */
  bool isActivable(){
    return false;
  }

  /**
     Action a faire quand on notifie le composant qu'il a été séléctionné
   */
  void onSelection(){
    if(isSelectable() )
      selected = true;
  }

  /**
     Action a faire quand on notifie le composant qu'il n'est plus séléctionné
   */
  void onDeselection(){
      selected = false;
  }

  /**
     Action a faire quand on notifie le composant qu'il a été activé.
   */
  void onActivation(){
    if(isActivable() )
      active = true;
  }

  /**
     Action a faire quand on notifie le composant qu'il n'est plus actif.
     Normalement inutilisé.
   */
  void onDesactivation(){
      selected = false;
  }

  /**
     vérifie si le curseur est dans le rectangle contenant le composant.
     En gros, si le curseur est dessus.
     Les paramètres donnent le point (x,y) de la position a vérifier.
  */
  bool checkMouse(const unsigned int& x,
		  const unsigned int& y) const{
    return false;
  }



}
