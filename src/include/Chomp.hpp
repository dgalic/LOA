#ifndef Chomp_HPP
#define Chomp_HPP

#include "BoardGame.hpp"
#include "Player.hpp"
#include "StateHandler.hpp"
#include "ANSI.hpp"
#include "Color.hpp"

class Chomp: public BoardGame {

    public:
        // Ctor et  Dtor
        Chomp();
        virtual ~Chomp();
        
        // gére les touches des joueurs
        void handle(const char&);

        // change de joueur
        const Player * opponent() const;
       
        // calcul la logique de jeux
        virtual void update();

        virtual void fillcolor(const unsigned short&, const unsigned short&);

        //gére l'affichage
        virtual void render();

};

#endif
