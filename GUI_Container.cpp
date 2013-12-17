#include "GUI_Container.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace GUI{

  Container::Container()
    :Component(){
    selected = false;
    active = true;
    selectedChild = std::null_ptr;
  }

  /**
     Quand on détruit un conteneur, on détruit aussi tout ce qu'il contient :
     est-ce que c'est bon ??
  */
  Container::~Container(){
    for(unsigned int i =0; i < subcomponents.size(); i++){
      delete subcomponents[i];
      subcomponents[i] = std::null_ptr;
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
    if(subcomponents[index]->isSelectable() ){
      if(hasSelection() )
	subcomponents[selectChild]->deselect();
      subcomponents[index]->select();
      selectChild = index;
    }
  }

  /**
     Lors d'un clic gauche, on déclenche l'action relative à l'élément
     fils séléctionné (si il y en a un).
     Lors d'un déplacement de souris, on regarde la nouvelle position : 
     il se peut que le curseur soit sur un autre élément fils.
  */
  void Container::handle(const sf::Event& e){
    if(e.type == sf::Event::MouseButtonPressed){
      if(e.mouseButton.button == sf::Mouse::Left){
	if(selectedChild != std::null_ptr){
	  selectedChild->handle();
	}
      }
    }else if(e.type == sf::Event::MouseMoved){
      for(unsigned int i =0; i < subcomponents.size(); i++){
	if(subcomponents[i]->isSelectable
	   &&
	   subcomponents[i]->checkMouse(event.mouseMove.x, 
					event.mouseMove.y) 
	   ){
	  subcomponents[i]->onSelection();
	  selectedChild = subcomponents[i];
	  break;
	}
      }
    }
  }
  
  /**
     dessine les components contenus
  */
  void Container::draw(sf::RenderTarget& t,sf::RenderStates s){
    s.transform *= transform;
    for(unsigned int i = 0; i < subcomponents.size(); i++){
      subcomponents[i]->draw(t, s);
    }

  } 

}
