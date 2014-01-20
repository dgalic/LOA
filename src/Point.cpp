#include "Point.hpp"

#include <iostream>

Point::Point(const unsigned short& t1, const unsigned short& t2)
  : mPair(std::make_pair(t1, t2) ) 
{
  std::cerr<<"point construit : "<<t1<<","<<t2<<std::endl;
}


Point::~Point(){
  
}


unsigned short Point::first() const{
  return std::get<0>(mPair);
}


unsigned short Point::second() const{
  return std::get<1>(mPair);
}


unsigned short Point::fst() const{
  return std::get<0>(mPair);
}


unsigned short Point::snd() const{
  return std::get<1>(mPair);
}


std::pair<unsigned short,unsigned short> Point::getPair() const{
  return mPair;
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

/*
bool operator==(const Point& t1, const Point& t2){
  return t1 == t2;
}


bool operator>(const Point& t1, const Point& t2){
  return t1 > t2;
}


bool operator>=(const Point& t1, const Point& t2){
  return t1 >= t2;
}


bool operator<(const Point& t1, const Point& t2){
  return t1 < t2;
}

bool operator<=(const Point& t1, const Point& t2){
  return t1 <= t2;
}


*/
