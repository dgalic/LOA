
#ifndef GAMESTATEHANDLER_H
#define GAMESTATEHANDLER_H

#include <string>
#include vector



/**
  * class GameStateHandler
  * 
  */

class GameStateHandler
{
public:

  // Constructors/Destructors
  //  


  /**
   * Empty Constructor
   */
  GameStateHandler ( );

  /**
   * Empty Destructor
   */
  virtual ~GameStateHandler ( );

  // Static Public attributes
  //  

  // Public attributes
  //  


  // Public attribute accessor methods
  //  


  // Public attribute accessor methods
  //  



  /**
   * @param  gs
   */
  void push (GameState * gs )
  {
  }


  /**
   * @return GameState *
   */
  GameState * pop ( )
  {
  }


  /**
   * @return bool
   */
  bool isEmpty ( )
  {
  }


  /**
   * @return GameState *
   * @param  gs
   */
  GameState * change (GameState * gs )
  {
  }


  /**
   */
  void clear ( )
  {
  }


  /**
   * @return bool
   */
  bool update ( )
  {
  }


  /**
   * @return bool
   */
  bool render ( )
  {
  }

protected:

  // Static Protected attributes
  //  

  // Protected attributes
  //  

public:


  // Protected attribute accessor methods
  //  

protected:

public:


  // Protected attribute accessor methods
  //  

protected:


private:

  // Static Private attributes
  //  

  // Private attributes
  //  

  std::stack<GameState *> states;
public:


  // Private attribute accessor methods
  //  

private:

public:


  // Private attribute accessor methods
  //  


  /**
   * Set the value of states
   * @param new_var the new value of states
   */
  void setStates ( std::stack<GameState *> new_var )   {
      states = new_var;
  }

  /**
   * Get the value of states
   * @return the value of states
   */
  std::stack<GameState *> getStates ( )   {
    return states;
  }
private:


  void initAttributes ( ) ;

};

#endif // GAMESTATEHANDLER_H
