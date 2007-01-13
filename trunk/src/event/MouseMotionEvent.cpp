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

