LOA
===
#Informations générales

Le but est de réaliser une application en C++ permettant de jouer à différents jeux. Certains jeux vous sont imposés les autres sont à prendre dans l’ensemble des jeux de combinatoire abstraite dont une liste (non-exhaustive) est disponible sur la page Wikipédia correspondante. Le nombre de jeux auxquels on doit pouvoir avoir accès à travers votre application doit être au minimum de 4, on ne compte pas les variantes imposées (vous sont donc imposés 3 jeux et vous êtes libres d’en implémenter au moins 1 autre à choisir vous-même).

Il est donc demandé de trouver les diverses abstractions utiles permettant de décrire l’essence commune à ses différents jeux. La réalisation concrète de ces abstractions pourra utiliser toute construction C++ adéquate : classes, héritage, généricité, etc. Ce qui est important et à privilégier est :

une bonne conception qui permettra d’envisager l’implantation aisée de nouveaux jeux (on pense toujours à la réutilisabilité/extensibilité);
une implémentation C++ claire et lisible.
La violation de certaines règles de jeux est possible pourvu que cela n’altère pas trop le jeu lui-même (i.e.: ne pas réduire les règles d’un jeu à une simple règle élémentaire, par contre pour un jeu comme les échecs on peut se limiter aux mouvements élémentaires et oublier le roque, et la prise en passant, par exemple).

#Réalisation

Le projet est à réaliser par groupe de deux étudiants au moins et trois au plus (aucune dérogation ne sera admise sauf cas très particuliers - ceux-ci se reconnaîtront et prendront contact avec moi par mail).

Il est impératif de constituer vos groupes de projets et de m’envoyer avant vendredi 13 décembre 2013 un courrier éléctronique avec la liste des membres de votre groupe-projet (nom ET prénom de chaque membre du groupe). Le choix de la date devrait vous rappeler que si vous ne le faites pas, la foudre s’abattra sur vous sans aucun doute (la foudre c’est « pas de groupe-projet déclaré, pas de soutenance »).

Le projet sera rendu quelques jours à peine avant la soutenance qui aura lieu à une date non encore déterminée mais courant janvier (après les examens). La remise se fera via Didel. Des précisions seront données en temps et en heure.

IMPORTANT ne traînez pas pour commencer votre projet, mais constituez avant votre groupe-projet.

Les jeux auxquels vous ne saurez échapper

#Puissance 4

Ce jeu se joue à deux. Le « plateau » est en fait une grille verticale qui comporte 6 lignes et 7 colonnes. Au début du jeu, la grille est vide. Chaque joueur possède des pions de couleur uniforme (par exemple, jaune pour le joueur 1 et rouge pour le joueur 2). Chacun leur tour, les joueurs choisissent une colonne et lâchent un pion de leur couleur dedans. La gravité entraîne le pion qui tombe alors dans la case vide de moindre hauteur.

Le premier joueur qui réussit à aligner 4 pions de sa couleur (horizontalement, verticalement ou en diagonale) gagne la partie. Si la grille est complètement remplie sans qu’aucun des joueurs n’ait aligné 4 pions, la partie est déclarée nulle.

#Variante

Dans cette variante, losrqu’on obtient un alignement (ou plusieurs simultanément). les pions concernés sont éliminés, et les pions restants subissent à nouveau l’effet de la gravité et tombent vers le bas.

On obtient un point par alignement et on s’arrête après un nombre de coups pré-définit à l’avance par un accord commun des deux joueurs ou lorsque la grille est pleine.

#Five or more

Ce jeu se joue seul. Le « plateau » est carré. Ses dimensions peuvent varier. Le nombre de couleurs des pions aussi.

Le but du jeu est ici de faire le plus d’alignements possibles avant que le plateau ne soit plein.

Au début du jeu, le plateau est vide. À chaque tour, l’ordinateur place trois pions de couleurs choisies au hasard (dans une collection de couleurs prédéfinie à l’avance) dans des cases choisies aléatoirement.

Le joueur a alors le droit d’en déplacer un à condition qu’il y ait un chemin entre la case de départ du pion et la case d’arrivée. Un chemin connecte deux emplacements par une suite de mouvements élémentaires horizontaux et verticaux.

Lorsqu’au moins 5 pions de la même couleur sont alignés (horizontalement, verticalement ou en diagonale), ils sont éliminés. Le joueur correspondant gagne des points et a le droit de rejouer sans que l’ordinateur ne pose d’autres pions, et ceci même si l’alignement survient au moment où l’ordinateur ajoute les pions au hasard.

On peut bien sûr compléter plusieurs alignements en même temps (on peut faire simulaténement un alignement vertical et un diagonal, par exemple).

Le nombre de points gagnés est fonction du nombre total de pions effacés. Nous vous laissons choisir cette fonction, elle devrait ne pas être linéaire.

##Variante

Dans cette variante, au lieu d’avoir le droit de déplacer un pion, on a le droit de changer sa couleur. Le reste des règles est inchangé.

#Othello

Ce jeu utilise un plateau de 8x8 cases et des pions avec une face blanche et une face noire. Un joueur utilise une couleur donnée.

Au départ la configuration est telle que deux « pions noirs » et deux « pions blancs » sont placés dans les 4 cases centrales de sorte que les pions d’une même couleur soient placés en diagonale.

Les joueurs placent à tour de rôle et si c’est possible un pion avec la face de leur couleur vers le haut. La pose n’est possible que si le pion posé emprisonne des pions de la couleur de l’adversaire; sont dit emprisonnés des pions d’une même couleur faciale tournée vers la heut et enfermés dans une direction donnée (horizontale, verticale ou diagonale) entre deux pions de la couleur adverse, sachant que l’un de pions enfermant doit avoir été posé dans l’instant. Les pions emprisonnés sont alors retournés de sorte que leur couleur change.

La partie se termine si aucun coup n’est plus possible, le gagnant est alors celui qui possède le plus de pions avec la face de sa propre couleur vers le haut.

