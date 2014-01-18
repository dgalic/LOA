#ifndef CONNECT4_HPP
#define CONNECT4_HPP

#include "BoardGame.hpp"
#include "Player.hpp"
#include "StateHandler.hpp"
#include "Color.hpp"

class Connext4: public BoardGame {

    protected :
        Player mPlayer1;
        Player mPlayer2;
        const Player * mCurrentPlayer;
    
    public:
        // Ctor et  Dtor
        Connect4(const Color&, const Color&);
        virtual ~Connect4();
        
        // gére les touches des joueurs
        void handle(const char&);
        // test si il y a une position gangante
        bool isPosGa(Board,
	        const unsigned short&,
	        const unsigned short&) const;        

        // change de joueur
        const Player * opponent() const;
       
        // calcul la logique de jeux
        virtual void update();
        
        //gére l'affichage
        virtual void render();
};

#endif
