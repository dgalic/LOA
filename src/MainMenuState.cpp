#include "MainMenuState.hpp"
#include "Singleton.hpp"

#include <iostream>

#include "GameState.hpp"

#include "GUI_Button.hpp"
#include "GUI_Container.hpp"
#include "GUI_Label.hpp"
#include "GUI_Window.hpp"


void MainMenuState::update(){
  //  container_main->update();
}

void MainMenuState::render(){
  GUI::Window::getInstance()->getTexture()->clear(Color(0,0,0) );
  GUI::Window::getInstance()->getTexture()->draw(*container_main);
}

bool MainMenuState::init(){
  container_main = new GUI::Container();
  container_buttons = new GUI::Container();
  container_buttons->setPosition(sf::Vector2f(400, 300) );;
  label_title = new GUI::Label("PIXOGAMES");
  label_title->setCharacterSize(64);
  label_title->setPosition(sf::Vector2f(100, 60) );
  button_play = new GUI::Button("PLAY", Color(20,20,200), 
				[this]() ->void{
				  std::cout<<" to PLAY state "<<std::endl;
				} );
  button_quit = new GUI::Button("QUIT", Color(200,20,20), 
				[this]() ->void{
				  GUI::Window::getInstance()->exit();
				} );
  container_buttons->add(button_play);
  container_buttons->add(button_quit);
  container_main->add(label_title);
  container_main->add(container_buttons);
  return true;
}

bool MainMenuState::exit(){
  delete label_title;
  delete button_play;
  delete button_quit;
  delete container_buttons;
  delete container_main;
  return true;
}

