#include "MouseEvent.h"

namespace XOR {

/*
 * constructor
 */
MouseEvent::MouseEvent()
{
	_type = 0;
}


//-- GETTERS --//
int MouseEvent::getType()			{	return _type;	}
int MouseEvent::getXPosition()		{	return _xpos;	}
int MouseEvent::getYPosition()		{	return _ypos;	}

}

