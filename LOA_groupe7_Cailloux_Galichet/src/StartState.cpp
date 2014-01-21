#include "StartState.hpp"

#include "Game.hpp"
#include "Console.hpp"
#include "MainMenuState.hpp"

StartState::StartState()
  :State(){

}

StartState::~StartState(){

}

void StartState::handle(const char& c){
  if(c == 'p' || c == MARK)
    Game::getInstance()->getHandler().change(new MainMenuState() );
}

void StartState::update(){
  char c = Console::getInstance()->getInput();
  handle(c);
}

void StartState::render(){
  Console::getInstance()->clear();
  Console::getInstance()->drawString(2,3, "Bienvenue dans la compilation de \
jeux de plateau de Nicolas Cailloux et David  Galichet. Nous espérons que vous \
passerez un agréable moment, mais il y a    certaines choses à savoir : ");
  Console::getInstance()->drawString(2,7, "La plupart des déplacements se font \
grace aux flèches. Si votre terminal ne  supporte pas, il y a toujours les \
touches ZQSD. Si vous avez un clavier Qwerty nous vous souhaitons bon courage.");
  Console::getInstance()->drawString(2,11, "Les validations peuvent se faire \
avec les touches '!' ou 'p'. La touche 'x'    sert, elle, à revenir au menu \
principal à tout instant.");
  Console::getInstance()->drawString(2,15, "Nous nous excusons d'avance pour \
les éventuels bugs visuels du terminal, ou   des problèmes d'encodage.");
  Console::getInstance()->draw(2,19, "Bon jeu ! Appuyez sur '!' pour continuer.");


}
