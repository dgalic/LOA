#ifndef ISOLA_HPP
#define ISOLA_HPP

#include "BoardGame.hpp"

/**
   Dans Isola, on met des cases à -2 : cela signifie "case détruite".
   -1 signifie toujours "case vide".
   Il y a deux phases de jeu dans un tour : 
   le déplacement du pion, puis la destruction d'un case.
 */

class Isola: virtual public BoardGame{

protected:
  bool mMoved; //est-ce que le joueur courant a déplacé sa pièce ?
  unsigned short mCurrentX;
  unsigned short mCurrentY;
  unsigned short mP1x;
  unsigned short mP1y;
  unsigned short mP2x;
  unsigned short mP2y;

public:
  Isola(const Color&, const Color&,
        const unsigned short&, const unsigned short&);
  virtual ~Isola();

protected:
  virtual bool isSucc(Board, 
                      const unsigned short&, const unsigned short&,
                      const Player&) const;
  virtual void handle(const char& c = ' ');
  virtual void handleMove(const char& c);
  virtual void handleDestroy(const char& c);
  virtual void update();
  virtual void render();
};

#endif
