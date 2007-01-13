#include "MouseEvent.h"

namespace XOR {

const int MouseEvent::MOUSE_MOTION          = 0;
const int MouseEvent::MOUSE_BUTTON_DOWN     = 1; 
const int MouseEvent::MOUSE_BUTTON_UP       = 2;

//-- GETTERS --//

int MouseEvent::getXPosition()		{	return _xpos;	}
int MouseEvent::getYPosition()		{	return _ypos;	}

}

