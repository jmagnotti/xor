#ifndef MOUSEMOTIONEVENT_H
#define MOUSEMOTIONEVENT_H


#include <cstring>
#include <string>
#include <SDL/SDL.h>

#include "MouseEvent.h"


namespace XOR {

/**
 * A way to encapsulate the data for a mouse moving to a new onscreen position
 */
class MouseMotionEvent : public MouseEvent
{

public:


	/**
	 * Explicit Constructor
	 */
	MouseMotionEvent(int xpos, int ypos, int xrel, int yrel);


    /**
     * Returns MouseEvent::MOUSE_MOTION
     */
    const int getType();


    /**
     * returns the amount moved during the last interval in the x dimension
     */
    int getRelativeXPosition();


    /**
     * returns the amount moved during the last interval in the y dimension
     */
    int getRelativeYPosition();


	/**
	 * Returns a string representation of the object.
	 */
	char * toString();


protected:

    // relative positions
    int _xrel, _yrel;

};

}

#endif			// MOUSEMOTIONEVENT_H

