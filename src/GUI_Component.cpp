#include "GUI_Component.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace GUI{

  Component::Component()
  : selected(false), 
    active(false){
  }

  Component::~Component(){
  }

  /** 
      Un component est quelque chose d'abstrait. Comme il ne peut pas être
      instancié, il ne peut pas être séléctionné.
      La séléction décrit "cet élément a le focus". Ici, ça voudra surtout
      dire "le curseur de la souris est dessus".
   */
  bool Component::isSelectable(){
    return false;
  }

  /**
     Action a faire quand on notifie le composant qu'il a été séléctionné
   */
  void Component::onSelection(){
    if(isSelectable() )
      selected = true;
  }

  /**
     Action a faire quand on notifie le composant qu'il n'est plus séléctionné
   */
  void Component::onDeselection(){
      selected = false;
  }

  /**
     Action a faire quand on notifie le composant qu'il a été activé.
   */
  void Component::onActivation(){
      active = true;
  }

  /**
     Action a faire quand on notifie le composant qu'il n'est plus actif.
     Normalement inutilisé.
   */
  void Component::onDesactivation(){
      selected = false;
  }

  /**
     vérifie si le curseur est dans le rectangle contenant le composant.
     En gros, si le curseur est dessus.
     Les paramètres donnent le point (x,y) de la position a vérifier.
  */
  bool Component::checkMouse(const unsigned int& x,
			     const unsigned int& y) const{
    return false;
  }

  void Component::handle(const sf::Event& e){
    
  }



}
