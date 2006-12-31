#ifndef MOUSEMOTIONEVENT_H
#define MOUSEMOTIONEVENT_H


#include "MouseEvent.h"
#include "../../include/SDL.h"


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
	MouseMotionEvent(Uint16 * xpos, Uint16 * ypos, Sint16 * xrel, Sint16 * yrel);


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


protected:


    // relative positions
    Sint16  * _xrel, * _yrel;


};

}

#endif			// MOUSEMOTIONEVENT_H

