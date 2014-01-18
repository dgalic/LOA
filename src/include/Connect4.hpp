#ifndef CONNECT4_HPP
#define CONNECT4_HPP

#include "BoardGame.hpp"
#include "Player.hpp"
#include "StateHandler.hpp"
#include "ANSI.hpp"
#include "Color.hpp"

class Connect4: public BoardGame {
    
    public:
        // Ctor et  Dtor
        Connect4(const Color&, const Color&);
        virtual ~Connect4();
        
        // gére les touches des joueurs
        void handle(const char&);

  bool checkMove(const char&);

        // change de joueur
        const Player * opponent() const;
       
        // calcul la logique de jeux
        virtual void update();

  virtual unsigned short drop(const unsigned short&, const unsigned short&);

  virtual void searchLines(const unsigned short&, const unsigned short&);

        //gére l'affichage
        virtual void render();
};

#endif
