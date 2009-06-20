#ifndef MOUSECLICKEVENT_H
#define MOUSECLICKEVENT_H


#include <cstring>
#include <string>
#include <SDL/SDL.h>

#include "MouseEvent.h"


namespace XOR {

/**
 * Represents the mouse being clicked
 */
class MouseClickEvent : public MouseEvent
{

public:

    static const int LEFT_MOUSE_BUTTON;
    static const int RIGHT_MOUSE_BUTTON;
    static const int MIDDLE_MOUSE_BUTTON;
    static const int MOUSE_WHEEL_UP;
    static const int MOUSE_WHEEL_DOWN;
    

    /**
     * Returns a button value, LEFT_MOUSE_BUTTON, RIGHT_MOUSE_BUTTON, MIDDLE_MOUSE_BUTTON
     */
	const int getButton();


    /**
     * Returns a state value, MOUSE_BUTTON_UP, MOUSE_BUTTON_DOWN
     */
	const int getState();

	/**
	 * String representation of the event
	 */
	char * toString();

	virtual const int getType()=0;

protected:


	int _button;
    int _state;


};

}

#endif			// MOUSECLICKEVENT_H

