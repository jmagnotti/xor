#ifndef MOUSEMOTIONEVENT_H
#define MOUSEMOTIONEVENT_H


#include "MouseEvent.h"


namespace XOR {

/**
 * A way to encapsulate the data for a mouse moving to a new onscreen position
 */
class MouseMotionEvent : public MouseEvent
{

public:


	/**
	 * Default Constructor
	 */
	MouseMotionEvent();
	

	/**
	 * Explicit Constructor
	 */
	MouseMotionEvent(int x, int y);


};

}

#endif			// MOUSEMOTIONEVENT_H

