#ifndef POINT_HPP
#define POINT_HPP

#include <utility>


class Point{

protected:
  std::pair<int, int> mPair;

public:
  Point(const int& = 0, const int& = 0);
  Point(const Point&);
  virtual ~Point();
  int first() const;
  int second() const;
  int fst() const;
  int snd() const;
  int& first();
  int& second();
  int& fst();
  int& snd();
  std::pair<int, int> getPair() const;
  void operator=(const Point&);
  bool operator==(const Point&) const;
  bool operator<(const Point&) const;
  bool operator<=(const Point&) const;
  bool operator>(const Point&) const;
  bool operator>=(const Point&) const;
 };


#endif
