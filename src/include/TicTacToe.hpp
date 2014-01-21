#ifndef TicTacToe_HPP
#define TicTacToe_HPP

#include "BoardGame.hpp"
#include "Player.hpp"
#include "StateHandler.hpp"
#include "ANSI.hpp"
#include "Color.hpp"

class TicTacToe: public BoardGame {

protected:
    const unsigned short mVictory; //nb de points pour la victoire
    
    public:
        // Ctor et  Dtor
        TicTacToe(const Color&, const Color&, const unsigned short& = 1);
        virtual ~TicTacToe();
        
        // gére les touches des joueurs
        void handle(const char&);

        // calcul la logique de jeux
        virtual void update();

        virtual void searchLines();

        //gére l'affichage
        virtual void render();

};

#endif
