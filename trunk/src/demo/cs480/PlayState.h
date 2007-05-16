#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "GameState.h"

/**
 * In the PlayState, collision detection is off and the ball is "bound" to the 
 * paddle until the user clicks the mouse to release it. See GameState.h for
 * method information.
 */
class PlayState : public GameState
{
public:
	
	/**
	 * Returns a pointer to the PlayState singleton. This method
	 * will instantiate the singleton on the initial method call 
	 * and returns a pointer to the object. If the singleton has 
	 * already been instantiated, the method returns a pointer to
	 * the current instance of the state.
	 */
	static PlayState * GetInstance(Game * game);
	
	/*
	 * Destructor
	 */
	~PlayState();
	
	/**
	 * Handles user key events using the XOR framework
	 *
	 * @param ke - the keyboard event
	 */
	 void handleKey(KeyEvent * ke);
	
	
	/**
	 * Handles user key events using the XOR framework
	 * Not implemented because the handleKey method
	 * handles the keypresses.
	 *
	 * @param ke - the keyboard event
	 */
	 void handleKeyEvent(KeyEvent * ke);


	/**
	 * Handles timer tick events using the XOR framework
	 */
	 void handleTick();


	/**
	 * Handles mouse motion and mouse click events using
	 * the XOR framework
	 *
	 * @param me - the mouse event
	 */
	 void handleMouseEvent(MouseEvent * me);


	/**
	 * This method turns collision detection off, sets
	 * the key and mouse listeners to ON
	 */
	 void in();


	/**
	 * Contexts clean up after themselves here, that is turn OFF what
	 * what you turned on. This behavior is not enforceable, but this
	 * implementation is designed with this behavior in mind and will
	 * work much more smoothly if it is followed. Like the in() method
	 * cool transition code can go here as well as anything else you
	 * think should happen during a transition.
	 */
	 void out();
	
	

	
private:
	/*
	 * Default singleton constructor. If there is no PlayState already
	 * created, it instantiates one and returns a pointer to that instance.
	 * If a PlayState is already instantiated, it returns a pointer to the
	 * current instance. The constructor is ONLY called by the getInstance method
	 */
	PlayState();


	static PlayState * _state;
};
#endif //PLAYSTATE_H
