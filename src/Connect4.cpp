#include "Connect4.hpp"

#include "Game.hpp"
#include "ANSI.hpp"
#include "Console.hpp"
#include "Board.hpp"
#include "StateHandler.hpp"
#include "MainMenuState.hpp"

#include <sstream> // ostringstream
#include <utility> // pour std::pair
#include <functional>


Connect4::Connect4(const Color& p1,
		 const Color& p2)
  : BoardGame(7, 6), mPlayer1(p1), mPlayer2(p2) {
  mPlayer1 = p1;
  mPlayer2 = p2;
  mCurrentPlayer = &mPlayer1;
  succ_function = [this](Board b, 
			 const unsigned short& x,
			 const unsigned short& y,
			 const Player& p) 
        -> bool {
            return b.at(x,0) == -1;
        };

}
  
Connect4::~Connect4(){}

void Connect4::handle(const char& c){
    /**
    * Cette fonction vérifie les touches tapées au clavier
    * par les joueurs.
    * @param c représente le caractère taper au clavier
    */
    
    ANSI::Arrow arr;
    arr = checkArrow(c);
   
    // si le joueur veut déplacer son curseur vers la gauche
    if (arr == ANSI::LEFT || c == 'q') {
        if (mPointerX > 0) {
                mPointerX--;
        }
        return;
    }

    // si le joueur veut déplacer son curseur vers la droite
    if ( arr == ANSI::RIGHT || c == 'd') {
        if ( mPointerX < mBoard.getWidth()-1 ) {
            mPointerX++;
        }
        return;
    }
  
    // si le joueur veut quitter le jeux
    if (c == 'x') {
        Game::getInstance()->getHandler().change(
                new MainMenuState());
        return;
    }

    // si le joueur veux executer une action, ici joueur une piece
    if (c == 'p' || c == MARK) {
        /* vérifie si b est en position gagnante 
        * avec le coup jouer */
        if( isNext( mPointerX, mPointerY, successors)) {
            if (isPosGa(MBoard, MPointerX, MPointerY)    
                mIngame = true;
                return;
            }
            mCurrentPlayer = opponent();
        }
    }
}

bool Connect4::isPosGa(Board b,
		     const unsigned short& x,
		     const unsigned short& y ) const{
    /**
    * @brief Teste si le coup amène à une position gagnante
    * @param b Plateau où on teste la validité du coup.
    * @param x Abscisse du coup à tester.
    * @param y Ordonnée du coup à tester.
    **/
    // tout d'abord determiner la vrai position y sur le tableau
    short i, tmp, good_color;
    unsigned short new_y = y;
    good_color = MCurrentPlayer.getColor();
    // on sauve la derniere position vide trouvé
    for (i = 0; i <= 6; i++) { 
        tmp = mBoard.at(x,i);
        // si case vide on sauve
        if ( tmp == -1){
            new_y = i;
        }
    }
   
    /*  maintenant on test la ligne , colonne et diagonales,
        si la position est gagnante, si 4 pieces aligné*/
    short j;
    int lig_p, lig_m, col_p, col_m;
    int dia1_p, dia1_m, dia2_p, dia2_m; // dia1 \ - dia2 /
    short right = mBoard.getWidth(), bottom = mBoard.getHeight();
    lig_p = lig_m = col_p = col_m = 1;
    dia1_p = dia1_m = dia2_p = dia2_m = 1;
    
    for(i = 1; i <= 4; i++) {
        for(j = 1; j <= 4; j++) {

            // test ligne des 2 cotes
            if ((x + i) <= right 
                    && lig_p == i 
                    && b.get(x+i,new_y) == good_color) {
                lig_p++;
            }
        
            if ((x - i) >= 0 
                    && lig_m == i 
                    && b.get(x-i,new_y) == good_color) {
                lig_m++;
            }

            //test colonne
            if ((new_y + i) <= bottom 
                    && col_p == i 
                    && b.get(x,new_y + i) == good_color) {
                col_p++;
            }
        
            if ((new_y - i) >= 0 
                    && col_m == i 
                    && b.get(x,new_y - i) == good_color) {
                col_m++;
            }

            // test une diagonale \*
            if ((x + i) <= right 
                    && (new_y + i) <= bottom
                    && dia1_p == i 
                    && b.get(x+i,new_y+i) == good_color) {
                dia1_p++;
            }
        
            if ((x - i) >= 0 
                    && (new_y - i) >= 0
                    && dia1_m == i 
                    && b.get(x - i,new_y - i) == good_color) {
                dia1_m++;
            }
            
            // test l'autre diagonale /
            if ((x + i) <= right 
                    && (new_y - i) <= 0
                    && dia2_p == i 
                    && b.get(x+i,new_y-i) == good_color) {
                dia1_p++;
            }
        
            if ((x - i) >= 0 
                    && (new_y + i) >= bottom
                    && dia2_m == i 
                    && b.get(x - i,new_y + i) == good_color) {
                dia1_m++;
            }

            // test si il y a un résultat égale à 4
            if ( (lig_p + lig_m -1 >= 4)
                    || (col_p + col_m -1 >= 4)
                    || (dia1_p + dia1_m -1 >= 4)
                    || (dia2_p + dia2_m -1 >= 4)) {
                return true;
            }
        }
    }

    // pose la piece du joueur courant²
    mBoard.at(&x, &new_y) = good_color;
    return false;
}

const Player *Connect4::opponent() const{
    /**
    * @brief Retourne le joueur prochain joueur à jouer
    * Cette fonction laisse la main au joueur suivant
    */
    if (*mCurrentPlayer == mPlayer1 ) {
        return &mPlayer2;
    } else {
        return &mPlayer1;
    }
}


void Connect4::update(){
    /**
    * Calculer  la logique de jeux
    */
    if (not mIngame) {
        //partie terminée 
        char c;
        std::cin>>c;
        Game::getInstance()->getHandler().change(new MainMenuState());
    } else {
        successors = BoardGame::computeNext(mBoard, *mCurrentPlayer, succ_function);
        const Player * other = opponent();
        if (successors.empty()) {
	        mIngame = false;
        } else{
            char c;
            std::cin>>c;
            handle(c);
        }
    }
}

void Connect4::render(){
    // nettoye l'interface et la rafraichie
    Console::getInstance()->clear();
    Console::getInstance()->setForeground(ANSI::Color::WHITE);
    Console::getInstance()->setCursor(1, 1);
    Console::getInstance()->draw("OTHELLO  -  q:left  d:right  !/p:place  x:quit");
    Console::getInstance()->setForeground(ANSI::Color::GRAY);
    Console::getInstance()->drawRectangle(1, 2, Console::getInstance()->getWidth(), 1, '#');
    Console::getInstance()->drawRectangle(1, 4, Console::getInstance()->getWidth(), 1, '#');

    std::ostringstream oss(std::ostringstream::ate);
    /* construire avec ::ate permet d'ajouter avec "<<" à la FIN du contenu défini
     par str(...). Autrement, ça écrit au début, écrasant les 1ers caractères */
    
    Console::getInstance()->setCursor(1, 3);
    Console::getInstance()->setForeground(mPlayer1.getColor() );
    oss.str("Joueur 1 - ");
    Console::getInstance()->drawString(1, 3, oss.str() );

    Console::getInstance()->setCursor(25, 3);
    Console::getInstance()->setForeground(mPlayer2.getColor() );
    oss.str("Joueur 2 - ");
    Console::getInstance()->drawString(25, 3, oss.str() );
    
    oss.clear();
   
    // si la partie n'est pas finie
    if (mIngame == true) {
        // indicateur du joueur courant
        Console::getInstance()->setForeground(ANSI::Color::WHITE);
        
        // affiche sur l'interface à quel joueur doit jouer
        if (*mCurrentPlayer == mPlayer1) {
            Console::getInstance()->draw(6, 5, '^');
        } else {
            Console::getInstance()->draw(30, 5, '^');
        }
    } else {
        // Si partie finie affiche qui à gagner ou égaliter
        oss.str("Joueur ");
        oss << ( (mCurrentPlayer == &mPlayer1)?1:2);
        Console::getInstance()->setForeground(ANSI::Color::WHITE);
        Console::getInstance()->drawString(7, 19, oss.str() );
        oss.clear();
    }
    mBoard.draw(12, 8);
    Console::getInstance()->setCursor(13+(mPointerX*2), 9+mPointerY);
}
