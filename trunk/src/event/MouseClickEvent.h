#ifndef MOUSECLICKEVENT_H
#define MOUSECLICKEVENT_H


#include "MouseEvent.h"


namespace XOR {

/**
 * Represents the mouse being clicked
 */
class MouseClickEvent : public MouseEvent
{

public:

	/**
	 * Explicit Constructor
	 */
	MouseClickEvent(int button, int state, int x, int y);

	int getButton();
	int getState();

protected:

	int _button, _state;


};

}

#endif			// MOUSECLICKEVENT_H

