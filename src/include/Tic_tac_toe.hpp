#ifndef Tic_tac_toe_HPP
#define Tic_tac_toe_HPP

#include "BoardGame.hpp"
#include "Player.hpp"
#include "StateHandler.hpp"
#include "ANSI.hpp"
#include "Color.hpp"

class Tic_tac_toe: public BoardGame {

protected:
    const unsigned short mVictory; //nb de points pour la victoire
    
    public:
        // Ctor et  Dtor
        Tic_tac_toe(const Color&, const Color&, const unsigned short& = 1);
        virtual ~Tic_tac_toe();
        
        // gére les touches des joueurs
        void handle(const char&);

        // change de joueur
        const Player * opponent() const;
       
        // calcul la logique de jeux
        virtual void update();

        virtual void searchLines(const unsigned short&, const unsigned short&);

        //gére l'affichage
        virtual void render();

};

#endif
