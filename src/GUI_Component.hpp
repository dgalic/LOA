#ifndef GUI_COMPONENT_HPP
#define GUI_COMPONENT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

/**
   classe de composant graphique : un conteneur, un bouton, un label, 
   une combobox,... sont des composants graphiques. 
   Non instanciable car un "composant" ne désigne rien de concret.
   hérite de sf::Drawable et sf::Transformable pour factoriser un peu plus,
   sans devoir tout le temps définir comment on dessine le composant.
 */

namespace GUI{

  class Component : public sf::Drawable, public sf::Transformable{
  public:
    Component();
    virtual~Component();
    virtual bool isSelectable();
    virtual void onSelection();
    virtual void onDeselection();
    virtual void onActivation();
    virtual void onDesactivation();
    virtual bool checkMouse(const unsigned int&, 
			    const unsigned int&) const;
    virtual void handle(const sf::Event&);
    virtual void draw(sf::RenderTarget&, sf::RenderStates ) const = 0;

  protected:
    bool selected;
    bool active;
  };


}

#endif
