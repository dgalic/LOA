#include "GUI_Component.hpp"
#include "GUI_Container.hpp"

#include "Event.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>

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
    c->parent = this;
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
    return ( (selectedChild) != (nullptr) );
  } 

  /**
     Lors d'un clic gauche, on déclenche l'action relative à l'élément
     fils séléctionné (si il y en a un).
     Lors d'un déplacement de souris, on regarde la nouvelle position : 
     il se peut que le curseur soit sur un autre élément fils.
  */
  void Container::handle(const Event& e){
    std::cerr<<"container"<<this<<" handles an event : "<<selectedChild<<std::endl;
    std::cerr<<"mouse moved : "<<e.mouseMove.x<<","<<e.mouseMove.y<<std::endl;

    if(e.type == sf::Event::MouseMoved){
      for (auto it = subcomponents.begin(); it != subcomponents.end(); ++it){
	  
	if( (*it)->isSelectable() 
	    && (*it)->checkMouse(e.mouseMove.x, e.mouseMove.y ) 
	    ){
	  std::cerr<< "selecting child "<<(*it)<<std::endl;
	  (*it)->onSelection();
	  selectedChild = (*it);
	  return;
	}
	
      }
      
      selectedChild = nullptr;

      std::cerr<< "selected child is now "<<selectedChild<<std::endl;

    }else
      if(selectedChild != nullptr){
	selectedChild->handle(e);
      }
    
    
    for (auto it = subcomponents.begin(); it != subcomponents.end(); ++it)
      (*it)->handle(e);

  }
  

  
  /**
     dessine les components contenus dans le component courant
  */
  void Container::draw(sf::RenderTarget& t, sf::RenderStates s) const{
    s.transform *= getTransform();
    for (auto it = subcomponents.begin(); it != subcomponents.end(); ++it){
      (*it)->draw(t, s);
    }
    
  } 

}
