#include "MouseButtonUp.h"


namespace XOR {

/*
 * constructor
 */
MouseButtonUp::MouseButtonUp(const int button, int x, int y)
{
	_button	= button;

	_xpos	= x;
	_ypos	= y;
}


/**
 *
 */
const int MouseButtonUp::getType()
{
    return MouseEvent::MOUSE_BUTTON_UP;
}

}

