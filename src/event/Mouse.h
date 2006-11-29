#ifndef MOUSE_H
#define MOUSE_H

#include "../../include/SDL.h"

#include <stdlib.h>
#include <vector>

#include "MouseListener.h"
#include "MouseEvent.h"
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
	 * Handles mouse click events -- UP & DOWN events
	 */
	void click(int, int, int, int);


    /**
     * Handles mouse clicks from SDL
     */
    void click(SDL_Event event);


	/**
	 * Fires an event to listeners
	 */
	void fireEvent(MouseEvent *);


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
	 * Stores the values of the latest move
	 */
	void motion(int, int);


    /**
     * Handles mouse motion events from SDL
     */
	void motion(SDL_Event event);


	/**
	 * Removes a listener from the pool
	 */
    void removeListener(MouseListener*);


    /**
     * Show/hide the cursor.
     */
    void setCursorVisibility(bool show);


	//---GETTERS---//
	int	getLeftDown();
	int	getStartX();
	int	getStartY();
	int	getPreviousX();
	int	getPreviousY();
	int getCurrentX();
	int getCurrentY();


protected:
	
    Mouse();


private:

	vector <MouseListener*> listeners;

    bool _cursorVisible;

	int _leftDown;
	int _startX,	_startY;
	int _previousX, _previousY;
	int _currentX,	_currentY;

	static Mouse * _mouse;
};

}

#endif			//MOUSE_H

