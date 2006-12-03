#include "MouseButtonUp.h"


namespace XOR {

/*
 * constructor
 */
MouseButtonUp::MouseButtonUp(const int * button, Uint16 * x, Uint16 * y)
{
	_button	= button;

	_xpos	= x;
	_ypos	= y;
}


/**
 *
 */
const int * MouseButtonUp::getType()
{
    return &(MouseEvent::MOUSE_BUTTON_UP);
}


/*
 * protected constructor
 */
MouseButtonUp::MouseButtonUp()
{}

}

