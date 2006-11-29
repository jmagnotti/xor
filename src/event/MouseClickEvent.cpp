#include "MouseClickEvent.h"

namespace XOR {

/*
 * constructor
 */
MouseClickEvent::MouseClickEvent(int button, int state, int x, int y)
{
	_button	= button;
	_state	= state;
	_xpos	= x;
	_ypos	= y;
	_type   = 2;
}

/*
 * accessors
 */
int MouseClickEvent::getButton()		{	return _button;	}
int MouseClickEvent::getState()			{	return _state;	}

}

