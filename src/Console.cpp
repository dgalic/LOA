#include "Console.hpp"
#include "ANSI.hpp"
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
  framerate = 40;
  currentBG = ANSI::Color::BLACK;
  currentFG = ANSI::Color::WHITE;
  //  showCursor(false);
  setBlocking(false);
}

char Console::getInput() const{
  /**
   * @brief Lit un caractère sur l'entrée standard.
   * @details Si @e setBlocking() n'a pas été rappelée, la lecture ne nécessite 
   * pas de retour chariot.
   * @return le caractère entrée au clavier.
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

ANSI::Color Console::getBackground() const{
  return this->currentBG;
}

ANSI::Color Console::getForeground() const{
  return this->currentFG;
}

/* changes the background color */
void Console::setBackground(const ANSI::Color& bc){
  this->currentBG = bc;
  //    std::cout<<CSI<<bc<<"m";
  std::cout<<CSI<<"48;5;"<<bc<<"m";
}

/* changes the foreground color */
void Console::setForeground(const ANSI::Color& fc){
  this->currentFG = fc;
  //    std::cout<<CSI<<fc<<"m";
  std::cout<<CSI<<"38;5;"<<fc<<"m";
}

unsigned short Console::getCursorX() const{
  return this->mCursorX;
}

unsigned short Console::getCursorY() const{
  return this->mCursorY;
}

/** changes the cursor's position to the given coordinates */    
void Console::setCursor(const unsigned short& x, const unsigned short& y){
  this->cursorX = min(x, getWidth() );
  this->cursorY = min(y, getHeigth() );
  std::cout<<CSI<<this->mCursorY<<";"<<this->mCursorX<<"H";
}

/** changes the cursor's X */
void Console::setCursorX(const unsigned short& x){
  this->mCursorX = min(x, getWidth() );
  std::cout<<CSI<<this->mCursorY<<";"<<this->mCursorX<<"H";
}

/** changes the cursor's Y */
void Console::setCursorY(const unsigned short& y){
  this->mCursorY = min(y, getHeigth() );
  std::cout<<CSI<<this->mCursorY<<";"<<this->mCursorX<<"H";
}

void Console::setFramerate(const double& f){
  this->framerate = f;
}

double Console::getFramerate() const{
  return this->framerate;
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
      and y <= this->getHeigth() ){
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
      and y <= this->getHeigth() ){
    unsigned short previousX = Console::getInstance()->getCursorX();
    unsigned short previousY = Console::getInstance()->getCursorY();
    unsigned short cx = x, cy = y;
    for(unsigned int i = 0; i < s.size(); i++){
      //      std::cerr<<"string : "<<s.at(i)<<" : "<<cx<<","<<cy <<std::endl;
      draw(cx, cy, s.at(i) );
      cx++;
      if(cx > 80){
	cx = 1;
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

/* move the cursor by the given vector */
void Console::moveCursor(const int& vx, const int& vy){
  setCursor(mCursorX + vx, mCursorY += vy);
}

/* move the cursor on its line of the given amount */
void Console::moveCursorX(const int& vx){
  setCursorX(mCursorX + vx);
  std::cout<<CSI<<this->mCursorY<<";"<<this->mCursorX<<"H";
}

/* move the cursor on its column of the given amount */
void Console::moveCursorY(const int& vy){
  setCursorY(mCursorY+ vy);
  std::cout<<CSI<<this->mCursorY<<";"<<this->mCursorX<<"H";
}


ANSI::Arrow checkArrow(const char & c){
  /**
   * 
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
