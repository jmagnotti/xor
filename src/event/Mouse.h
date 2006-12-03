#ifndef MOUSE_H
#define MOUSE_H

#include "../../include/SDL.h"

#include <stdlib.h>
#include <list>

#include "MouseListener.h"
#include "MouseEvent.h"
#include "MouseEventFactory.h"
#include "MouseClickEvent.h"
#include "MouseMotionEvent.h"


using namespace std;



namespace XOR {

class MouseListener;

/**
 * A place for all the mouse events. Maintains state information.
 * Justification: you can easily swap MouseListeners during program execution
 * to get different behavior. Only one mouse can be used though, to simply event handling
 *
 * I want to make portions of the mouse static, specifically for getX and getY.
 * this would allow for classes to have access to the mouse without having to be 
 * listeners or containers
 */
class Mouse
{

public:


    /**
	 * Add a listener to the pool
	 */
    void addListener(MouseListener*);


    /**
     * Handles mouse clicks from SDL
     */
    void click(SDL_Event * event);


    /**
     * Handles mouse motions from SDL
     */
    void move(SDL_Event * event);


	/**
	 * Fires an event to listeners
	 */
	void fireEvent(MouseEvent * me);


	/**
	 * Singleton Constructor
	 */
	static Mouse * GetInstance(void);


	/**
	 * Singleton constructor that allows for 
	 * one pass adding of yourself to the listener pool
	 */
	static Mouse * GetInstance(MouseListener*);


	/**
	 * Removes a listener from the pool
	 */
    void removeListener(MouseListener*);


    /**
     * Show/hide the cursor.
     */
    void setCursorVisibility(bool show);


protected:
	
    Mouse();


private:

	list <MouseListener*> listeners;
    bool    _cursorVisible;

	static Mouse * _mouse;

};

}

#endif			//MOUSE_H

