#include "MouseMotionEvent.h"

namespace XOR {

/*
 * default constructor
 */
MouseMotionEvent::MouseMotionEvent()
{}

int MouseMotionEvent::getRelativeXPosition()
{
    return (int) (*_xrel);    
}


int MouseMotionEvent::getRelativeYPosition()
{
    return (int) (*_yrel);
}

const int * MouseMotionEvent::getType()
{
    return &(MouseEvent::MOUSE_MOTION);
}


/*
 * Explicit constructor
 */
MouseMotionEvent::MouseMotionEvent(Uint16 * xpos, Uint16 * ypos, Sint16 * xrel, Sint16 * yrel)
{ 
	_xpos = xpos;
	_ypos = ypos;

    _xrel = xrel;
    _yrel = yrel;
}

}

