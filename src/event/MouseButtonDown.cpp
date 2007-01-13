#include "MouseButtonDown.h"


namespace XOR {

/*
 * constructor
 */
MouseButtonDown::MouseButtonDown(const int button, int x, int y)
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

