#ifndef MOUSE_H
#define MOUSE_H


#include <stdlib.h>
#include <list>

#include "../../../include/SDL.h"

#include "MouseListener.h"
#include "MouseEvent.h"
#include "MouseEventFactory.h"
#include "MouseClickEvent.h"
#include "MouseMotionEvent.h"


using namespace std;

namespace XOR {

/**
 * The generator of all the mouse events. Maintains state information. You can
 * easily swap MouseListeners during program execution to get different
 * behavior. 
 *
 * @author John Magnotti, Michael Lam
 * @version 1.0
 */
class Mouse
{

public:

	/**
	 * Upon construction, a default listener should be set up for the mouse.
	 * This will typically be a DefaultMouseListener or a custom child class of
	 * DefaultMouseListener.
	 *
	 * @param defaultListener A default handler for the mouse events.  
	 *
	 * @returns The previously set DefaultMouseListener or NULL if there was no
	 * previous handler (unlikely) or if defaultListener is equal to NULL (more
	 * likely). The caller should delete the returned instance if it is not
	 * needed.
	 */
	MouseListener * setDefaultMouseListener(MouseListener * defaultListener);


    /**
     * Forces the mouse cursor to the given position. This generates a mouse
     * event in the process.
     *
     * @param xpos  The new x position of the mouse cursor in absolute (screen) coordinates.
     * @param ypos  The new y position of the mouse cursor in absolute (screen) coordinates.
     */
    static void ForceMove(int xpos, int ypos);

	/**
	 * Fires an event to listeners. Delegated to implementing classes.
	 */
	virtual void fireEvent(MouseEvent * me)=0;

    /**
     * Easier way to access mouse motion. Also fires a mouse move event.
     */
    static void SetMousePosition(int xpos, int ypos);

    /**
     * Push the event onto the SDL Event queue
     * @param event The SDL mouse event to fire.
     */
    static void FireSDLEvent(SDL_Event * event);

    /**
	 * Add a listener to the pool
	 */
    void addListener(MouseListener * listener);

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
     * Needed for subclasses.
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

	list <MouseListener*>  _listeners;
	MouseListener * _defaultMouseListener;

    bool    _cursorVisible;

	int		_currentX;
	int		_currentY;
	int		_previousX;
	int		_previousY;

	bool	_leftButtonDown;
	bool	_rightButtonDown;
	bool	_middleButtonDown;

    static SDL_Event * _sdlCLickEvent;
    static SDL_Event * _sdlMoveEvent;

};

}

#endif			//MOUSE_H

