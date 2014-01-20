#ifndef POINT_HPP
#define POINT_HPP

#include <utility>


class Point{

protected:
  const std::pair<unsigned short, unsigned short> mPair;

public:
  Point(const unsigned short&, const unsigned short&);
  virtual ~Point();
  unsigned short first() const;
  unsigned short second() const;
  unsigned short fst() const;
  unsigned short snd() const;
  std::pair<unsigned short, unsigned short> getPair() const;
  bool operator==(const Point&) const;
  bool operator<(const Point&) const;
  bool operator<=(const Point&) const;
  bool operator>(const Point&) const;
  bool operator>=(const Point&) const;
 };


#endif
