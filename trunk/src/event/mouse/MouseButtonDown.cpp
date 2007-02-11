#include "MouseButtonDown.h"


namespace XOR {

/*
 * constructor
 */
MouseButtonDown::MouseButtonDown(int x, int y, const int button)
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

