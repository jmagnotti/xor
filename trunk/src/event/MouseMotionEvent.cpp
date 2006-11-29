#include "MouseMotionEvent.h"

namespace XOR {

/*
 * default constructor
 */
MouseMotionEvent::MouseMotionEvent()
{}


/*
 * explicit constructor
 */
MouseMotionEvent::MouseMotionEvent(int x, int y)
{ 
	_xpos = x;
	_ypos = y;
	_type = 1;
}

}

