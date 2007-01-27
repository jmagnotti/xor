#include "MouseClickEvent.h"

namespace XOR {

// mouse button constants
const int MouseClickEvent::LEFT_MOUSE_BUTTON     = 1;
const int MouseClickEvent::RIGHT_MOUSE_BUTTON    = 2;
const int MouseClickEvent::MIDDLE_MOUSE_BUTTON   = 3;
const int MouseClickEvent::MOUSE_WHEEL_UP        = 4;
const int MouseClickEvent::MOUSE_WHEEL_DOWN      = 5;


/*
 * getters
 */
const int MouseClickEvent::getButton()	
{
	return _button;	
}


const int MouseClickEvent::getState()
{
    return _state;
}

}

