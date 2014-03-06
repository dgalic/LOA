#Compilation de jeux de plateau
###par Nicolas CAILLOUX et David GALICHET.

##Utilisation : 
- compilez avec *make*
- lancez avec *make start* /!\ OBLIGATOIRE, sous peine de ne rien voir d'intéressant /!\
- lisez le petit message d'instructions
- c'est parti !

##Présentation :
Nous avons développé un environnement de développement de jeux de plateau en essayant d're le plus générique, extensible possible. 6 jeux sont actuellement disponibles, plus 2 variantes : Othello, Five or more, Puissance 4 étaient imposés. Il y a, en plus, le morpion, et deux autres jeux.

###Isola
Chaque joueur déplace son pion d'une case orthogonale ou vertical (comme un roi d'échecs), puis détruit un case du plateau. Un pion ne peut plus aller sur un case détruite. Puis l'autre joueur joue à son tour : il se déplace et détruit une case.   
Le premier joueur qui se retrouve bloqué (qui ne peut plus bouger son pion) a perdu.  

###Chomp
Dans Chomp, les joueurs choisissent à tour de rôle une case d'un plateau. Toutes les cases au dessus et à droite de celle-ci sont détruites, de la même manière qu'on brise une tablette de chocolat.  
Le gourmand (celui qui mange le dernier bout de chocolat, tout en bas à gauche) perd.


## Détails d'implémentation

### States et gestion des phases d'application
Une application interactive peut se présenter comme un automate, par exemple :   
Menu ----> A ----> C  
\---->B  
Via l'interface utilisateur, l'automate et les transitions sont données implicitement.  
Toutefois, on peut vouloir se souvenir du chemin parcouru vers l'état courant, afin de revenir en arrière (Imaginons un état "pause", qui une fois quitté, ramènerait à l'état antérieur). C'est pourquoi nous avons implémenté ceci sous forme de pile dans la classe StateHandler.  
Tout est déjà géré, ainsi on rajoute un état au programme très simplement :  
Il doit hériter de State (et définir les méthodes *update* - gestion des la logique, calculs - et *render* - représentation de la logique).  
Pour ajouter une transition vers un état :  
Si on ne veut pas garder la trace :  
Game::getInstance()->getHandler().change(new Etat() )
Si on veut garder la trace :  
Game::getInstance()->getHandler().push(new Etat() )

Notez d'ailleurs que Game est un singleton accessible depuis tout le programme : a priori, une seule instance du jeu peut être lancée en même temps sur un terminal (c'est pourquoi le terminal est lui aussi un singleton). 

### BoardGames, les vrais jeux
Nous disposons d'une classe extensible BoardGame, qui par défaut représente un jeu de plateau pour deux joueurs. Le bagage contient deux couleurs (pour identifier les joueurs 1 et 2), un plateau, deux scores, et une fonction de succession. 
Vu que BoardGame hérite de State, cela colle parfaitement avec la définition d'un jeu :  
- un état initial (donné par le constructeur)
- un état final (géré par update)
- une représentation (render)
- une fonction de succession (membre mSuccessors, mais gérée par update).
La fonction de succession permet de calculer les coups possibles à une position donnée. C'est commode pour certains jeux où on doit connaitre les coups possibles (voir Othello, où si un joueur ne peut pas jouer, il passe), mais c'est indispensable pour l'extensibilité. Ainsi, une IA basée sur la recherche ou MinMax/alpha-beta pourrait facilement être implémentée, car on connait déjà la manière d'obtenir les coups possibles.  

Donc, pour créer un jeu, c'est très facile : 
Le jeu Jeu hérite de BoardGame. Si ce n'est pas un jeu de plateau, on peut très bien s'en passer. La seule contrainte est qu'il hérite d'au moins State.  
On l'implémente en redéfinissant *update* (logique de jeu), *handle* (gestion des touches, à séparer de la logique en cas d'IA), *render* (représentation de la configuration courante).  
BoardGame dispose de quelques méthodes commodes, comme le calcul ou la vérification des coups possibles, l'obtention immédiate du joueur adverse, ou l'affichage standardisé du score, du joueur courant, du résultat.  

Malheureusement, un jeu créé n'est pas ajouté automatiquement a notre programme (on sait faire du data-driven en XML, pas en c++). 
Un jeu qui redéfinit les trois méthodes citées est parfaitement fonctionnel avec tout moteur utilisant les boucles d ejeu type “eval-print", ou (au pire des cas) cela peut être fait directement dans le jeu. 
Mais si on souhaite l'ajouter à notre programme de collection, c'est dans MainMenuState.cpp :  
ajouter une description (mGameDesc.push_back("blabla"); )  
ajouter un lien (dans le grand "case" de la fonction *handle*, Game::getInstance()->getHandler().change( new Jeu() );  )  
montrer le lien (dans *render*)  

Trois choses à faire + 1 héritage, représentent peu de travail, ce qui fait que l'ajout de nouveaux jeux de plateau est très facile et rapide. On peut ainsi se concentrer sur le développement du jeu, et pas sur les étapes ennuyeuses d'intégration. 


### Les configs

Toujours dans un soucis d’extensibilité, vous pouvez vouloir configurer votre jeu. Une classe à étendre est déjà présente pour ceci : Config.  
Elle permet de régler par défaut les couleurs des deux joueurs ainsi que les dimensions du plateau de jeu.  
C'est un état comme les autres. Il faut donc en hériter et ajouter un lien pour y accéder.  
Cette classe est bien sûr extensible avec d'autres options, la seule chose obligatoire est de redéfinir *launchgame*, qui permet de lancer le jeu correspondant. 



### La console

La classe Console donne quelques méthodes pour dessiner dans un terminal. Nous avons choisi de tout séparer de la gestion des calculs, par soucis de réutilisabilité : si on désire utiliser une librairie graphique, moins de choses seront à changer (et, en principe, uniquement dans la méthode *render*).   
Certaines choses sont faites pouvant rendre le terminal instable, c’est une des raisons pour lesquelles il faut bien lancer le programme avec *make start* (une sécurité supplémentaire est faire).