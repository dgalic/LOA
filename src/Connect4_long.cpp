#include "Connect4_long.hpp"

Connect4_long::Connect4_long(const Color& p1, 
                             const Color& p2,
                             const unsigned short& v)
:Connect4(p1, p2, v){

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
  for(unsigned short ix = 0; ix <= 1; ix++){
    for(short iy = -1; iy <= 1; iy++){
      xtest = x;
      ytest = y;
      if(ix == 0 && iy == 0)
        continue;
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
      while(xtest < width-1 &&            
            (  iy == 0 
               || (iy > 0 && ytest < height-1 ) 
               || (iy < 0 && ytest > 0 ) )
            &&
            mBoard.at(xtest+ix, ytest+iy) == c){
        count++;
        xtest += ix;
        ytest += iy;
      }
      //si il y a plus de 5, on fait machine arrière et on fait l'action
      if(count >= 4){
        for(unsigned short i = 0; i < count; i++){
          if(xtest != x or ytest != y){
            mBoard.at(xtest, ytest) = -1;
          }          
          xtest -= ix;
          ytest -= iy;
          nb++;
        }
      }

    }
  }

  if(nb > 0){
    mBoard.at(x, y) = -1;
    if(y > 0 )
      drop(x, y-1);
    std::cerr<<"mise à jour du score ? "<<nb/4<<" -> "<<mScore[0]<<"-"<<mScore[1]<<std::endl;
    if(c == mPlayer1.getColor() )
      mScore[0] += nb/4;
    else 
      mScore[1] += nb/4;
  }

  do{
    nb = 0; //nb prend le nombre de pions étant tombés à cause de la suppression
    unsigned short j2;  
    for(unsigned short j = height-1; j-1 > 0; j--){
      for(unsigned short i = width-1; i-1 > 0; i--){
        std::cerr<<"dans la boucle "<<i<<","<<j<<std::endl;
        j2 = drop(i, j);
        if(j2 != j){
          nb++;
          searchLines(i, j2);
        }
      }
    }
  }while(nb > 0);
  
  std::cerr<<"SORTIE"<<std::endl;
  
}
