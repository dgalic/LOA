#include "GUI_Component.hpp"
#include "GUI_Container.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace GUI{

  Container::Container()
    : Component(){
    selected = false;
    active = true;
    selectedChild = nullptr;
  }

  /**
     Quand on détruit un conteneur, on détruit aussi tout ce qu'il contient :
     est-ce que c'est vrai ??
  */
  Container::~Container(){
    for(unsigned int i = 0; i < subcomponents.size(); i++){
      delete subcomponents.at(i);
      subcomponents.at(i) = nullptr;
    }
    subcomponents.clear();
  }

  /**
     ajoute le component [c] aux éléments fils
  */
  void Container::add(Component * c){
    subcomponents.push_back(c);
  }

  /**
     Séléctionne le component fils numéro [index]. Pas utilie ici, mais
     peu servir pour l'extensibilité (navigation avec le clavier).
  */
  void Container::select(const unsigned int& index){
    if(subcomponents.at(index)->isSelectable() ){
      if( hasSelection() )
	selectedChild->onDeselection();
      subcomponents.at(index)->onSelection();
      selectedChild = subcomponents.at(index);
    }
  }

  bool Container::hasSelection() const{
    return ( (selectedChild) == (nullptr) );
  } 

  /**
     Lors d'un clic gauche, on déclenche l'action relative à l'élément
     fils séléctionné (si il y en a un).
     Lors d'un déplacement de souris, on regarde la nouvelle position : 
     il se peut que le curseur soit sur un autre élément fils.
  */
  void Container::handle(const sf::Event& e){
 
    if(e.type == sf::Event::MouseMoved){
      for(unsigned int i = 0; i < subcomponents.size(); i++){
	if(subcomponents.at(i)->isSelectable()
	   &&
	   subcomponents.at(i)->checkMouse(e.mouseMove.x, 
					   e.mouseMove.y ) 
	   ){
	  subcomponents.at(i)->onSelection();
	  selectedChild = subcomponents.at(i);
	  return;
	}
      }
      selectedChild = nullptr;
    }else{
      if( selectedChild != nullptr)
	selectedChild->handle(e);
    }
  }
  
  /**
     dessine les components contenus
  */
  void Container::draw(sf::RenderTarget& t, sf::RenderStates s) const{
    s.transform *= getTransform();
    for(unsigned int i = 0; i < subcomponents.size(); i++){
      subcomponents.at(i)->draw(t, s);
    }

  } 

}
