#include "Connect4_long.hpp"
#include "Point.hpp"
#include "BoardGame.hpp"
#include <set>

Connect4_long::Connect4_long(const Color& p1, 
                             const Color& p2,
                             const unsigned short& v)
:BoardGame(7, 6, p1, p2), Connect4(p1, p2, v){

}

Connect4_long::~Connect4_long(){
}



void Connect4_long::searchLines(const unsigned short& x, const unsigned short& y){
  unsigned short nb = 0; // nombre de pions détruits (le posé est cumulé)
  unsigned short count = 0;
  unsigned short c = mBoard.at(x, y);  
  unsigned short xtest, ytest;
  static const unsigned short width = mBoard.getWidth(), 
    height = mBoard.getHeight();

  Positions res;
  for(unsigned short ix = 0; ix <= 1; ix++) {
      for(short iy = -1; iy <= 1; iy++) {
          xtest = x;
          ytest = y;
          if(ix == 0 && iy == 0) {
              continue;
          }
          //pion de la même couleur le plus éloigné
          while( xtest > 0  && 
                  (  iy == 0 
                     || (iy < 0 && ytest < height-1 ) 
                     || (iy > 0 && ytest > 0 ) )
                  && (mBoard.at(xtest-ix, ytest-iy) == c )   ){
              xtest -= ix;
              ytest -= iy;
          }
          
          count = 1; 
          //on cherche les pions, dans la direction opposée, en comptant
          while((ix == 0 || xtest < width-1)
                && (iy == 0 
                     || (iy > 0 && ytest < height-1 ) 
                     || (iy < 0 && ytest > 0 ))
                && mBoard.at(xtest+ix, ytest+iy) == c){
              count++;
              xtest += ix;
              ytest += iy;
          }
          
          //si il y a plus de 5, on fait machine arrière et on fait l'action
          if(count >= 4){
              mBoard.at(x, y) = -1;
              for(unsigned short i = 0; i < count; i++){
                mBoard.at(xtest, ytest) = -1;
                if ((ytest != 0) && (mBoard.get(xtest,ytest-1) != -1)) {
                    res.insert(Point( (int)xtest,(int) (ytest-1)));
                }
                xtest -= ix;
                ytest -= iy;
                nb++;
              }
              mBoard.at(x, y) = mCurrentPlayer->getColor();
          }
      }
  }


  if (nb > 0) {
    mBoard.at(x, y) = -1;
    if (y > 0 ) {
      drop(x, y-1);
    }
    
    if(c == mPlayer1.getColor()) {
      mScore[0] += nb/4;
    } else { 
      mScore[1] += nb/4;
    }
  }

  if (not res.empty()) {
    unsigned short x_s, y_s;
    std::set<Point>::iterator it;
    for (it = res.begin() ; it != res.end() ; it ++) {
        Point t = *it;
        x_s = (unsigned short)t.first();
        y_s = (unsigned short)t.second();
        drop(x_s, y_s);
        res.erase(t);
    }
    for (unsigned short i = 0; i < mBoard.getWidth(); i++) {
        for (unsigned short j = 0; j < mBoard.getHeight(); j++) {
            if (mBoard.get(i,j) != -1) {
                searchLines(i,j);            
            }
        }
    }
  }

}
