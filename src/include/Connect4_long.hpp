#ifndef CONNECT4_LONG_HPP
#define CONNECT4_LONG_HPP

#include "Connect4.hpp"

class Connect4_long : public Connect4{

public:
  Connect4_long(const Color&, const Color&, const unsigned short& = 42);
  virtual ~Connect4_long();
  
protected:
  virtual void searchLines(const unsigned short&, const unsigned short&);

};

#endif
