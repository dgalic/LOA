#include "MainMenuState.hpp"
#include "Singleton.hpp"

#include <iostream>

#include "GameState.hpp"
#include "Console.hpp"
#include "ANSI.hpp"


void MainMenuState::update(){
  Console::getInstance()->getInput();
}

void MainMenuState::render(){
  Console::getInstance()->clear();
  Console::getInstance()->setCursor(4, 1);
  Console::getInstance()->draw("MAIN MENU");
  Console::getInstance()->setCursor(1, 4);
  Console::getInstance()->setBackground(ANSI::Color::BROWN);
  Console::getInstance()->setForeground(ANSI::Color::GREEN);
  Console::getInstance()->drawRectangle(82, 3, '#');
  Console::getInstance()->setBackground(ANSI::Color::DARKRED);
  Console::getInstance()->setCursor(1, 3);
}

bool MainMenuState::init(){

  return true;
}

bool MainMenuState::exit(){

  return true;
}

