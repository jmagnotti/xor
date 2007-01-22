#ifndef MOUSE_H
#define MOUSE_H


#include "../../../include/SDL.h"

#include <stdlib.h>
#include <list>

#include "MouseListener.h"
#include "MouseEvent.h"
#include "MouseEventFactory.h"
#include "MouseClickEvent.h"
#include "MouseMotionEvent.h"


using namespace std;

namespace XOR {


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
	 * Removes a listener from the pool
	 */
    void removeListener(MouseListener * listener);


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
	virtual void fireEvent(MouseEvent * me)=0;


    /**
     * Show/hide the cursor.
     */
    void setCursorVisibility(bool show);


	/**
	 * Get current x-coordinate
	 */
	int getCurrentX();


	/**
	 * Get current y-coordinate
	 */
	int getCurrentY();


	/**
	 * Get previously registered x-coordinate
	 */
	int getPreviousX();


	/**
	 * Get previously registered y-coordinate
	 */
	int getPreviousY();

	
	/**
	 * Get current left button status
	 */
	bool isLeftButtonDown();


	/**
	 * Get current right button status
	 */
	bool isRightButtonDown();


	/**
	 * Get current middle button status
	 */
	bool isMiddleButtonDown();


protected:
	
    /**
     * Needed for subclasses
     */
    Mouse();


    /**
     * Notify the listeners of the specific mouse event
     */
    void notifyListeners(MouseEvent *me);

    /**
     * Easy way to store the values from the latest mouse event
     */
    void updateFromEvent(MouseMotionEvent * mme);
    void updateFromEvent(MouseClickEvent * mce);


private:

	list <MouseListener*> listeners;

    bool    _cursorVisible;

	int		_currentX;
	int		_currentY;
	int		_previousX;
	int		_previousY;

	bool	_leftButtonDown;
	bool	_rightButtonDown;
	bool	_middleButtonDown;
};

}

#endif			//MOUSE_H

