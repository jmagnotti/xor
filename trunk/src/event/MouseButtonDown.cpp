#include "MouseButtonDown.h"


namespace XOR {

/*
 * constructor
 */
MouseButtonDown::MouseButtonDown(const int * button, Uint16 * x, Uint16 * y)
{
	_button	= button;

	_xpos	= x;
	_ypos	= y;
}


/*
 *
 */
const int MouseButtonDown::getType()
{
    return MouseEvent::MOUSE_BUTTON_DOWN;
}

}

