#include "Console.hpp"
#include "ANSI.hpp"
#include "Color.hpp"
#include "Helpers.hpp"

#include <string>
#include <iostream>

Console::Console(){
  /**
   * @brief Constructeur.
   * @details A la création, la console a comme dimensions 80x24, le curseur est
   * placé en haut à gauche, la couleur de fond est noire, la couleur d'écriture
   * est blanche. Le terminal est aussi mis en mode @e raw, afin que l'appui 
   * d'une touche n'ai pas besoin d'être validé avec un retour chariot.
   */
  mWidth = 80;
  mHeight = 24;
  mCursorX = 0;
  mCursorY = 0;
  mFramerate = 40;
  mCurrentBG = Color::BLACK;
  mCurrentFG = Color::WHITE;
  setBlocking(false);
}

char Console::getInput() const{
  /**
   * @brief Lit un caractère sur l'entrée standard.
   * @details Si @e setBlocking() n'a pas été rappelée, la lecture ne nécessite 
   * pas de retour chariot.
   * @return le caractère entré au clavier.
   */
  char c;
  std::cin >> c;
  return c;
}

void Console::exit(){
  /**
   * @brief Quitte propremet la console
   * @details Le terminal est nettoyé ("clear"), le curseur est réaffiché, et 
   * le mode bloquant est réactivé.
   */
  clear();
  showCursor(true); 
  setBlocking(true);
}

void Console::setBlocking(const bool& b){
  /** 
   * @brief Change l'état bloquant (ou non) de l'entrée du terminal.
   * @details Le terminal est mis en mode "raw" (canonique), permettant de lire
   * des caractères sans avoir à appuyer sur "Entree".
   * @param b Dit si on bloque ou pas.
   */
  if(b){
    // met le terminal en mode "validant"
    system("stty -cbreak");   
    system("stty icanon"); 
    system("stty echo");
  }else{
        // met le terminal en mode "non-validant"
    system("stty cbreak");   
    system("stty -icanon"); 
    system("stty -echo");
  }
}

unsigned short Console::getWidth() const{
  return mWidth;
}

unsigned short Console::getHeight() const{
  return mHeight;
}

void Console::setWidth(const unsigned short& w){
  mWidth = w;
}

void Console::setHeight(const unsigned short& h){
  mHeight = h;
}

Color Console::getBackground() const{
  return this->mCurrentBG;
}

Color Console::getForeground() const{
  return this->mCurrentFG;
}

void Console::setBackground(const Color& bc){
  this->mCurrentBG = bc;
  std::cout<<CSI<<"48;5;"<<bc<<"m";
}

void Console::setForeground(const Color& fc){
  this->mCurrentFG = fc;
  std::cout<<CSI<<"38;5;"<<fc<<"m";
}

unsigned short Console::getCursorX() const{
  return this->mCursorX;
}

unsigned short Console::getCursorY() const{
  return this->mCursorY;
}

void Console::setCursor(const unsigned short& x, const unsigned short& y){
  this->mCursorX = min(x, getWidth() );
  this->mCursorY = min(y, getHeight() );
  std::cout<<CSI<<this->mCursorY<<";"<<this->mCursorX<<"H";
}

void Console::setCursorX(const unsigned short& x){
  this->mCursorX = min(x, getWidth() );
  std::cout<<CSI<<this->mCursorY<<";"<<this->mCursorX<<"H";
}

void Console::setCursorY(const unsigned short& y){
  this->mCursorY = min(y, getHeight() );
  std::cout<<CSI<<this->mCursorY<<";"<<this->mCursorX<<"H";
}

void Console::setFramerate(const double& f){
  this->mFramerate = f;
}

double Console::getFramerate() const{
  return this->mFramerate;
}


void Console::draw(const unsigned short& x, const unsigned short& y, const char& c = ' ') {
  /**
   * @brief Dessine un caractère dans le terminal.
   * @details Le caractère est dessiné à la position (@a x, @a y ) avec les
   * couleurs courantes de @e background et @e foreground.
   * @param x Colonne du terminal où on veut afficher le caractère.
   * @param y Ligne du terminal où on veut afficher le caractère.
   * @param c Caractère à dessiner. Par défaut ' ', pour afficher juste le fond.
   */
  if( x > 0 
      and y > 0
      and x <= getWidth()
      and y <= getHeight() ){
    unsigned short previousX = Console::getInstance()->getCursorX();
    unsigned short previousY = Console::getInstance()->getCursorY();
    Console::getInstance()->setCursor(x, y);
    std::cout<<c;
    Console::getInstance()->setCursor(previousX, previousY);
  }
}

void Console::draw(const char& c = ' ') {
    /**
   * @brief Dessine un caractère dans le terminal.
   * @details Le caractère est dessiné à la position courante donnée par le 
   * curseur avec les couleurs courantes de @e background et @e foreground.
   * @param c Caractère à afficher. Par défaut ' ', pour afficher juste le fond.
   */
  draw(this->mCursorX ,this->mCursorY, c);  
}

void Console::draw(const unsigned short& x, const unsigned short& y, const std::string& s){
    /**
   * @brief Dessine une chaine dans le terminal, pouvant être tronquée.
   * @details La chaine est dessiné à la position (@a x, @a y ) avec les
   * couleurs courantes de @e background et @e foreground. Si la chaine est trop
   * longue pour être affichée, elle sera tronquée.
   * @param x Colonne du terminal où on veut commencer à afficher.
   * @param y Ligne du terminal où on veut commencer à afficher.
   * @param s Chaine à afficher.
   */
  if( x > 0 
      and y > 0
      and x <= this->getWidth() 
      and y <= this->getHeight() ){
    unsigned short previousX = Console::getInstance()->getCursorX();
    unsigned short previousY = Console::getInstance()->getCursorY();
    Console::getInstance()->setCursor(x, y);
    std::cout<<s.substr(0, this->getWidth()  - this->mCursorX+1 );
    Console::getInstance()->setCursor(previousX, previousY);
  }
  
}

void Console::drawString(const unsigned short& x, const unsigned short& y, const std::string& s){
  /**
   * @brief Dessine une chaine dans le terminal, ne pouvant pas être tronquée.
   * @details La chaine est dessiné à la position (@a x, @a y ) avec les
   * couleurs courantes de @e background et @e foreground. Si la chaine est trop
   * longue pour être affichée, on fera un retour à la ligne. On ne peut 
   * toutefois pas dépasser du terminal en hauteur.
   * @param x Colonne du terminal où on veut commencer à afficher.
   * @param y Ligne du terminal où on veut commencer à afficher.
   * @param s Chaine à afficher.
   */
  if( x > 0 
      and y > 0
      and x <= this->getWidth() 
      and y <= this->getHeight() ){
    unsigned short previousX = Console::getInstance()->getCursorX();
    unsigned short previousY = Console::getInstance()->getCursorY();
    unsigned short cx = x, cy = y;
    for(unsigned int i = 0; i < s.size(); i++){
      draw(cx, cy, s.at(i) );
      cx++;
      if(cx > 80){
	cx = x;
	cy += 1;
      }
      
    }
    Console::getInstance()->setCursor(previousX, previousY);
  }
  
}

void Console::draw(const std::string& s){
  /**
   * @brief Dessine une chaine dans le terminal, pouvant être tronquée.
   * @details La chaine est dessiné à la position courante avec les couleurs 
   * courantes de @e background et @e foreground. Si la chaine est trop longue 
   * pour être affichée, elle sera tronquée.
   * @param s Chaine à afficher.
   */
  draw(mCursorX, mCursorY, s);
}

void Console::drawString(const std::string& s){
  /**
   * @brief Dessine une chaine dans le terminal, ne pouvant pas être tronquée.
   * @details La chaine est dessiné à la position courante du curseur avec les
   * couleurs courantes de @e background et @e foreground. Si la chaine est trop
   * longue pour être affichée, on fera un retour à la ligne. On ne peut 
   * toutefois pas dépasser du terminal en hauteur.
   * @param s Chaine à afficher.
   */
  drawString(mCursorX, mCursorY, s);
}

void Console::drawRectangle(const unsigned short& x, 
                            const unsigned short& y, 
			    const unsigned short& w, 
                            const unsigned short& h,
			    const char& c = ' ')
{
  /**
   * @brief Dessine un rectangle dans le terminal, tronqué.
   * @details Le rectangle de largeur @a w x @a y est dessiné à la position 
   * donnée, avec les couleurs courantes. Il peut avoir un éventuel caractère
   * à dessiner. Si le rectangle est trop grand, il est tronqué.
   * @param x Abscisse du point supérieur gauche.
   * @param y Ordonnée du point supérieur gauche.
   * @param w Largeur du rectangle.
   * @param h Hauteur du rectangle.
   * @param c Caractère a dessiner dans le rectangle (défaut ' ').
   */
  unsigned short previousX = Console::getInstance()->getCursorX();
  unsigned short previousY = Console::getInstance()->getCursorY();
  unsigned short x1 = x, y1 = y;
  unsigned short x2 = x1+w, y2 = y1+h;
  for(unsigned short y = y1; y < y2; y++){
    for(unsigned short x = x1; x < x2; x++){
      Console::getInstance()->setCursor(x, y);
      Console::getInstance()->draw(c);
    }
  }
  Console::getInstance()->setCursor(previousX, previousY);
}

void Console::drawRectangle(const unsigned short& w, const unsigned short& h, const char& c = ' ')
{
  /**
   * @brief Dessine un rectangle dans le terminal, tronqué.
   * @details Le rectangle de largeur @a w x @a y est dessiné à la position 
   * courante, avec les couleurs courantes. Il peut avoir un éventuel caractère
   * à dessiner. Si le rectangle est trop grand, il est tronqué. 
   * @param w Largeur du rectangle.
   * @param h Hauteur du rectangle.
   * @param c Caractère a dessiner dans le rectangle (défaut ' ').
   */
  drawRectangle(mCursorX, mCursorY, w, h, c);
}

void Console::drawHeader(const std::string& txt){
  setForeground(Color::WHITE);
  draw(1, 1, txt);
  setForeground(Color::GRAY);
  drawRectangle(1, 2, Console::getInstance()->getWidth(), 1, '#');
  drawRectangle(1, 4, Console::getInstance()->getWidth(), 1, '#');
}

void Console::showCursor(const bool& b) const{
  /**
   * @brief Contrôle l'affichage du curseur.
   * @param b Dit si on affiche le curseur ou non.
   * @bug Ne fonctionne pas.
   */
  if(b)
    std::cout<<CSI<<"?25h";
  else
    std::cout<<CSI<<"?25l";  
}


void Console::clear(){
  /**
   * @brief Efface tout le terminal
   */
  std::cout<<ESC<<"c";
}

void Console::moveCursor(const int& vx, const int& vy){
  /**
     @brief Déplace le curseur du vecteur donné.
     @param vx Déplacement horizontal.
     @param vy Déplacement vertical.
   */
  setCursor(mCursorX + vx, mCursorY += vy);
}

void Console::moveCursorX(const int& vx){
  /**
     @brief Déplace le curseur sur sa ligne.
     @param vx Déplacement horizontal.
   */
  setCursorX(mCursorX + vx);
  std::cout<<CSI<<this->mCursorY<<";"<<this->mCursorX<<"H";
}

void Console::moveCursorY(const int& vy){
  /**
     @brief Déplace le curseur sur sa colonne.
     @param vy Déplacement vertical.
   */
  setCursorY(mCursorY+ vy);
  std::cout<<CSI<<this->mCursorY<<";"<<this->mCursorX<<"H";
}


ANSI::Arrow checkArrow(const char & c){
  /**
   * @brief Vérifie l'appui d'une touche.
   * @details Une flèche consiste à une caractère ESC[ suivi d'une lettre. 
   * @param c Touche entrée.
   * @return La direction entrée, ou NOARROW si ce n'est pas une flèche.
   */
  if(c != ESC)
    return ANSI::NOARROW;
  char d;
  std::cin >> d;
  if(d != '[')
    return ANSI::NOARROW;
  std::cin >> d;
  if(d == 'A' )
    return ANSI::UP;
  if(d == 'B' )
    return ANSI::DOWN;
  if(d == 'C' )
    return ANSI::RIGHT;
  if(d == 'D' )
    return ANSI::LEFT;
  return ANSI::NOARROW;
  
}
