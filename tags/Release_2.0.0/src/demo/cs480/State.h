#ifndef STATE_H
#define STATE_H

/*
 * The State class serves as an interface to all state objects. The
 * child class implementations of the methods reflect the current
 * state of the game.
 */
class State
{
	/*
	 *  Turns collision detection on or off in the child state classes
	 */
	virtual bool doCollision() = 0;
	
	/*
	 * Performs the necessary tasks when the player wins the game.
	 * Implemented by the child classes.
	 */
	virtual void win() = 0;
	
	/*
	 * Performs the necessary tasks when the player loses the game.
	 * Implemented by the child classes.
	 */
	virtual void lose() = 0;
	
	/*
	 * Used to confirm that the player wishes to reset to the ReadyState.
	 * Implemented in the child classes.
	 */
	virtual bool ok() = 0;
};
#endif //STATE_H
