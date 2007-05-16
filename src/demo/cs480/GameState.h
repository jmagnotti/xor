#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Game.h"
#include "../../xor.h"

using namespace XOR;

class Game;

/*
 * Parent class for all state objects used in Game. Each abstract method represents
 * functionality that can be turned on and of by the child implementations. Implementations
 * of the in() method should turn on the necessary functionality that each state needs.
 * It can also contain code for flashy transitions between states such as a warp or
 * fade in. The out() method should be implemented to clean up after the state, ie,
 * turn off what you turned on so that the states can function in ignorance of each
 * other. Like the in() method, the out() method can also be used for cool transition
 * effects. The set*Listen() methods turn on/off listening for the respective events
 * when passed true for on, or false for off.
 *
 * It would be a good idea to implement child states as Singletons so there is no need 
 * to create an arbitrary number of State objects as the game goes on. Using a singleton
 * allows the previously created states to be recycled and cuts down on the ammount of 
 * memory management.
 *
 * A better encapsulation of the set*Listen() system would handle
 * each type of listener specifically, but, again, for simplicity's sake, has been
 * omitted for this version. It's also not the best idea that we have to keep track
 * of additional state information with the _*Listen attributes. A better implementation
 * would move that information to be attributes of each state that needed them.
 */
class GameState : public MouseListener, public KeyboardListener, public TimerListener
{

public:

	/**
	 * Handles user key events using the XOR framework
	 *
	 * @param ke - the keyboard event
	 */
	virtual void handleKeyEvent(KeyEvent * ke)=0;


	/**
	 * Handles timer tick events using the XOR framework
	 */
	virtual void handleTick()=0;


	/**
	 * Handles mouse motion and mouse click events using
	 * the XOR framework
	 *
	 * @param me - the mouse event
	 */
	virtual void handleMouseEvent(MouseEvent * me)=0;


	/**
	 * Any setup tasks that a state needs to perform should go here.
	 * There is no reason that cool transition effects couldn't go here
	 * as well. All setup tasks should be performed here. This behavior 
	 * is not enforceable, but you will find your life to be much easier
	 * if you follow this behavior. 
	 */
	virtual void in()=0;


	/**
	 * Contexts clean up after themselves here, that is turn OFF what
	 * what you turned on. This behavior is not enforceable, but this
	 * implementation is designed with this behavior in mind and will
	 * work much more smoothly if it is followed. Like the in() method
	 * cool transition code can go here as well as anything else you
	 * think should happen during a transition.
	 */
	virtual void out()=0;


protected:

	/**
	 * Acts as a switch to turn timer listening on or off
	 *
	 * @param listen - true for on, false for off
	 */
	void setTimerListen(bool listen);

	/**
	 * Acts as a switch to turn mouse listening on or off
	 *
	 * @param listen - true for on, false for off
	 */
	void setMouseListen(bool listen);

	/**
	 * Acts as a switch to turn keyboard listening on or off
	 *
	 * @param listen - true for on, false for off
	 */
	void setKeyListen(bool listen);

	/**
	 * refactor to better encapsulated event handling
		MouseListener * _mouseListener;
		TimerListener * _timerListener;
		KeyListener *   _keyListener;
	 */

	GameState();
	

	Game * _game;

private:

	// not great that we have to keep track of additional state
	// information
	bool _timerListen, _mouseListen, _keyListen;
};


#endif			// GAMESTATE_H
