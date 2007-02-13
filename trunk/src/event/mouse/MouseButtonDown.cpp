#include "MouseButtonDown.h"


namespace XOR {

/*
 * constructor
 */
MouseButtonDown::MouseButtonDown(int x, int y, const int button)
{
	_xpos	= x;
	_ypos	= y;

	_button	= button;
}


/*
 *
 */
const int MouseButtonDown::getType()
{
    return MouseEvent::MOUSE_BUTTON_DOWN;
}

}

