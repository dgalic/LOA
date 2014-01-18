#include "Player.hpp"
#include "Color.hpp"

Player::Player(const Color& c): mColor(c){

}

Player::Player(const Player& p){
  setColor(p.getColor() );
}

Color Player::getColor() const{
  return mColor;
}

void Player::setColor(const Color& c){
  mColor = c;
}

void Player::operator=(const Player& p){
  mColor = p.getColor();
}

bool Player::operator==(const Player& p) const{
  return (mColor == p.getColor() );
}

bool Player::operator!=(const Player& p) const{
  return not ((*this)==(p));
}
