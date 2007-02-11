#include "MouseMotionEvent.h"

namespace XOR {

int MouseMotionEvent::getRelativeXPosition()
{
    return _xrel;    
}


int MouseMotionEvent::getRelativeYPosition()
{
    return _yrel;
}

const int MouseMotionEvent::getType()
{
    return MouseEvent::MOUSE_MOTION;
}


/*
 * string representation
 */
char * MouseMotionEvent::toString()
{
	_eventString = new char[30];
	memset(_eventString, 0, sizeof(_eventString));
	sprintf(_eventString, "%d %d %d %d %d", getType(), getXPosition(), getYPosition(), getRelativeXPosition(), getRelativeYPosition());

	return _eventString;
}


/*
 * Explicit constructor
 */
MouseMotionEvent::MouseMotionEvent(int xpos, int ypos, int xrel, int yrel)
{ 
	_xpos = xpos;
	_ypos = ypos;

    _xrel = xrel;
    _yrel = yrel;
}

}

