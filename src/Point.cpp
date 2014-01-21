#include "Point.hpp"

Point::Point(const int& t1, const int& t2)
  : mPair(std::make_pair(t1, t2) ) 
{
}

Point::Point(const Point& p){
  fst() = p.fst();
  snd() = p.snd();
}

Point::~Point(){
  
}


int Point::first() const{
  return std::get<0>(mPair);
}


int Point::second() const{
  return std::get<1>(mPair);
}


int Point::fst() const{
  return std::get<0>(mPair);
}


int Point::snd() const{
  return std::get<1>(mPair);
}

int& Point::first() {
  return std::get<0>(mPair);
}


int& Point::second(){
  return std::get<1>(mPair);
}


int& Point::fst(){
  return std::get<0>(mPair);
}


int& Point::snd(){
  return std::get<1>(mPair);
}


std::pair<int,int> Point::getPair() const{
  return mPair;
}


void Point::operator=(const Point& t){
  mPair = std::make_pair(t.fst(), t.snd() );
}

bool Point::operator==(const Point& t) const{
  return getPair() == t.getPair();
}


bool Point::operator<(const Point& t) const{
  return getPair() < t.getPair() ;
}


bool Point::operator<=(const Point& t) const{
  return getPair() <= t.getPair() ;
}



bool Point::operator>(const Point& t) const{
  return getPair() > t.getPair();
}


bool Point::operator>=(const Point& t) const{
  return getPair() >= t.getPair();
}
